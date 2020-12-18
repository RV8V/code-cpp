#include <iostream>
#include <atomic>
#include <thread>
#include <mutex>
#include <chrono>
#include <ctime>
#include <cstdlib>
#include <future>
#include <queue>

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

int main(int argc, char const *argv[]) {
  async_test_a::test_package();
  return 0;
}
