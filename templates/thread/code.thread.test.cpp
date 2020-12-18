#include <iostream>
#include <thread>
#include <chrono>
#include <unistd.h>
#include <memory>
#include <mutex>

using namespace std;

void func_to_test(int, int, int);
void test_code_a(void);
void test_code_b(void);
void test_mutex(int&, mutex&);

int main(int, const char**) {
  test_code_b();
}

void func_to_test(int n, int limit, int time) {
  for (int i = 0; i < limit; i++) {
    cout << "count: " << i << " " << __FUNCTION__ << " -> " << n << " = "
      << this_thread::get_id() << endl;
    usleep(time * limit * n * n);
  }
  return;
}

void test_code_a(void) {
  cout << "hardware concurrency: " << thread::hardware_concurrency() << endl;

  thread t1(func_to_test, 10, 10, 700);
  thread t2(func_to_test, 10, 10, 700);

  if (t1.joinable()) t1.join();
  t2.detach();

  cout << __FUNCTION__ << " () -> " << this_thread::get_id() << endl;
  return;
}

void test_mutex(int& number, mutex& mtx) {
  while("mutex& mtx") {
    mtx.lock();
    number += 2;
    cout << this_thread::get_id() << " number: " << number << endl;
    mtx.unlock();
    usleep(500000);
  }
  return;
}

void test_code_b(void) {
  int number = 10;
  mutex mtx;

  thread t1(test_mutex, ref(number), ref(mtx));
  thread t2(test_mutex, ref(number), ref(mtx));

  t1.join();
  t2.join();

  return;
}
