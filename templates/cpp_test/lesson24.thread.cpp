#include <iostream>
#include <chrono>
#include <thread>
#include <mutex>

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
  return 0;
}
