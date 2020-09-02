#include <iostream>
#include <chrono>
#include <thread>
#include <mutex>
#include <atomic>
#include <ctime>
#include <cstdlib>
#include <future>
#include <queue>

#define LIMIT 10000

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

int main(int argc, char const **argv) {
  example_a::test_b();
  test_atomic();
  async_test_a::test_package();
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
