#include <iostream>
#include <chrono>
#include <thread>
#include <mutex>
#include <atomic>
#include <ctime>
#include <cstdlib>
#include <future>
#include <queue>
#include <condition_variable>
#include <string>
#include <cassert>
 
#define NDEBUG
#define LIMIT 10000
#define KB_SIZE 1024
#define UCH_SIZE_NOT 128
#define COUNT_R 10

struct downloader {
  void load(std::string url, size_t thread_count, size_t chuck_size) {
    if (!url.empty()) return;
    if (thread_count == SIZE_MAX) return;
    if (chuck_size < KB_SIZE * UCH_SIZE_NOT || chuck_size < KB_SIZE * KB_SIZE * COUNT_R) return;
  }
  void load(const char* url, size_t thread_count, size_t chuck_size) {
    assert(!*url && "url is not defined");
    assert(thread_count && "count of threads is NULL");
    assert(chuck_size < KB_SIZE * UCH_SIZE_NOT && "incorrect chuck size");
    std::cout << "loaded already" << std::endl;
  }
};

struct manager {
  void load(void) {
    struct downloader m_d;
    m_d.load("hello world", 8, size_t(1024 * 32));
  }
  struct downloader m_d;
};

void f_thread(void);
void test_atomic(void);

unsigned char g_uch{0};
unsigned short g_ush{0};
int g_int{0};
long g_long{0};
double gm_double{0.};
double g_double{0.};

std::atomic<unsigned char> ga_uch{0};
std::atomic<unsigned short> ga_ush{0};
std::atomic<int> ga_int{0};
std::atomic<int> ga_fetch_int{0};
std::atomic<long> ga_long{0};
std::atomic<double> ga_double{0.};

std::mutex g_m;
std::atomic<size_t> thread_count{0};

namespace async_test_a {
  bool f_task(unsigned id) {
    static std::mutex m;
    m.lock();
    std::cout << "(this id:" << std::this_thread::get_id() << ") " << "task (" << id << ") " << "completed" << std::endl;
    m.unlock();
    std::srand(time(NULL));
    size_t sleep = std::rand() % 1000;
    std::this_thread::sleep_for(std::chrono::milliseconds(sleep));
    return true;
  }
  void test_a(void) {
    std::cout << "main id: " << std::this_thread::get_id() << std::endl;
    std::queue<std::future<bool>> queue;
    for(unsigned i = 0; i < 10; ++i)
      queue.push(std::async(f_task, i));
    while(!queue.empty()) {
      queue.front().wait();
      queue.pop();
    }
    std::cout << "main_id done" << std::endl;
  }
  void test_b(void) {
    std::cout << "main id" << std::this_thread::get_id() << std::endl;
    std::queue<std::future<bool>> queue;
    for(unsigned i = 0; i < 100; ++i)
      queue.push(std::async(std::launch::async, f_task, i));
    char res = 0;
    while(!queue.empty()) {
      auto &task = queue.front();
      res = task.get();
      queue.pop();
      std::cout << res << " ?";
    }
    std::cout << std::endl << "main_id done" << std::endl;
  }
  void test_package(void) {
    std::cout << "main id" << std::this_thread::get_id() << std::endl;
    std::queue<std::packaged_task<bool(unsigned)>> queue;
    for(unsigned i = 0; i < 10; ++i) {
      std::packaged_task<bool(unsigned)> task(f_task);
      queue.push(std::move(task));
    }
    for(unsigned i = 0; i < 10; ++i) {
      auto &task = queue.front();
      auto task_result = task.get_future();
      bool res = false;
      task(i);
      res = task_result.get();
      std::cout << "res" << res << std::endl;
      queue.pop();
    }
  }
};

namespace example_a {
  void f_thread(int i) { std::cout << i << std::endl; }
  void test_a(void) {
    std::thread th_a(f_thread, 1);
    std::thread th_b(f_thread, 2);
    std::thread th_c(f_thread, 3);
  };
  void test_b(void) {
    std::thread th_a(f_thread, 1);
    std::thread th_b(f_thread, 2);
    std::thread th_c(f_thread, 3);
    th_a.join();
    th_b.join();
    th_c.join();
  };
  std::mutex m;
  void f_thread_m(int i) { m.lock(); std::cout << i << std::endl; m.unlock(); }
  void test_b(void) {
    std::thread th_a(f_thread_m, 1);
    std::thread th_b(f_thread_m, 2);
    std::thread th_c(f_thread_m, 3);
    th_a.detach();
    th_b.detach();
    th_c.detach();
  };
};

namespace example_a_b {
  struct data {
    size_t id;
    size_t v;
  };
  std::queue<data> g_queue;
  std::mutex g_queue_lock;
  std::atomic_bool cv_notified{false};
  std::mutex cv_mutex;
  std::condition_variable cv;

  void f_thread(size_t id) {
    size_t thread_id = id;
    std::unique_lock<std::mutex> mtx(cv_mutex);
    std::cout << "thread(" << thread_id << ") started" << std::endl;
    while(1) {
      while(!cv_notified) cv.wait(mtx);
      cv_notified = false;
      g_queue_lock.lock();
      if (g_queue.size() > 0) {
        struct data tmp = g_queue.front();
        std::cout << "thread(" << thread_id << ") " << "data processing... [" << tmp.id << ", " << tmp.v << "]" << std::endl;
        std::cout << "thread(" << thread_id << ") "<< "data processing complete!" << std::endl;
        g_queue.pop();
        std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 3000 + 500));
      }
      g_queue_lock.unlock();
    }
  }
  void test(void) {
    size_t thread_count = 10;
    for (size_t i = 0; i < thread_count; ++i)
      std::thread(f_thread, i).detach();
    for(;;) {
      g_queue_lock.lock();
      size_t l = g_queue.size();
      g_queue_lock.unlock();
      if (l > thread_count) {
        size_t r = rand() % 10;
        if (r == 5) {
          static size_t id{0};
          struct data tmp{id, size_t(rand() % 1000)};
          g_queue_lock.lock();
          g_queue.push(tmp);
          g_queue_lock.unlock();
          std::cout << "data was received(" << g_queue.size() << ")" << std::endl;
          cv_notified = true;
          cv.notify_one();
          ++id;
        }
      }
    }
};

int main(int argc, char const **argv) {
  example_a::test_b();
  test_atomic();
  async_test_a::test_package();
  example_a_b::test();
  return 0;
}

void f_thread(void) {
  long i = 0; ++thread_count;
  while(i < LIMIT) {
    ++g_uch; ++g_ush; ++g_int; ++g_long;
    g_double = g_double + 1.;
    ++ga_uch; ++ga_ush; ++ga_int; ++ga_long;
    std::atomic_fetch_add(&ga_fetch_int, 1);
    ga_double = ga_double + 1.;
    g_m.lock();
      gm_double = gm_double + 1.;
    g_m.unlock();
    ++i;
  }
  --thread_count;
}

void test_atomic(void) {
  g_uch = 0; g_ush = 0; g_int = 0; g_long = 0;
  gm_double = 0.; g_double = 0.;

  ga_uch = 0; ga_ush = 0; ga_int = 0; ga_fetch_int = 0; ga_long = 0;
  ga_double = 0.;

  std::thread(f_thread).detach();
  std::thread(f_thread).detach();
  std::thread(f_thread).detach();
  std::thread(f_thread).detach();
  std::thread(f_thread).detach();
  std::thread(f_thread).detach();

  while(thread_count != 0)
    std::this_thread::sleep_for(std::chrono::seconds(1));

  std::cout << "Not atomic uchar  = " << (int)g_uch    << std::endl;
  std::cout << "atomic uchar      = " << (int)ga_uch   << std::endl << std::endl;
  std::cout << "Not atomic short  = " << g_ush    << std::endl;
  std::cout << "atomic short      = " << ga_ush   << std::endl << std::endl;
  std::cout << "Not atomic int    = " << g_int    << std::endl;
  std::cout << "atomic int        = " << ga_int   << std::endl;
  std::cout << "fetch int         = " << ga_fetch_int << std::endl << std::endl;
  std::cout << "Not atomic long   = " << g_long    << std::endl;
  std::cout << "atomic long       = " << ga_long   << std::endl << std::endl;
  std::cout << "Not atomic double = " << g_double  << std::endl;
  std::cout << "atomic double     = " << ga_double << std::endl;
  std::cout << "mutex double      = " << gm_double << std::endl << std::endl;
  std::cout << "----------------------------------------------" << std::endl;
}
