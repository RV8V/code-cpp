#include <iostream>
#include <condition_variable>
#include <mutex>
#include <thread>
#include <chrono>
#include <vector>
#include <queue>
#include <atomic>

namespace example_a {
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

int main(int argc, char const *argv[]) {
  example_a::test();
  return 0;
}
