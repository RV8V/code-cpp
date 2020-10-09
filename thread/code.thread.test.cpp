#include <iostream>
#include <thread>
#include <chrono>
#include <unistd.h>

using namespace std;

void func_to_test(int, int, int);
void test_code_a(void);

int main(int, const char**) {
  test_code_a();
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
