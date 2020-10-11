#include <iostream>
#include <stdarg.h>
#include <thread>
#include <future>
#include <cmath>
#include <functional>

using namespace std;

int function_to_test(int, ...);

int f(int, int);
void task_lambda_error(void);
void task_thread(void);

int main(void) {
  task_lambda_error();
  task_thread();
  int sum = function_to_test(5, 1, 2);
  cout << "sum: " << sum << endl;
  return 0;
}

int function_to_test(int num, ...) {
  int sum = 0;
  va_list arg_pointer;
  va_start(arg_pointer, num);
  cout << "arg_pointer: " << arg_pointer << endl;
  for (int i = 0; i < 2; i++) {
    int current_value = va_arg(arg_pointer, int);
    sum += current_value;
  }
  va_end(arg_pointer);
  return sum;
}

int f(int x, int y) { return pow(x, y); }

void task_lambda_error(void) {
  cout << "entered here" << endl;
  packaged_task<int(int, int)> task([](int a, int b) -> int {
    return pow(a, b);
  });
  future<int> result = task.get_future();
  task(2, 4);
  cout << "result: " << result.get() << endl;
}

void task_thread(void) {
  packaged_task<int(int, int)> functor([](int a, int b) {
    return pow(a, b);
  });
  future<int> ft = functor.get_future();
  int value_a = 2, value_b = 4;
  thread future_thread(functor, value_a, value_b);
  future_thread.join();
  cout << "result is -> " << ft.get() << endl;
}
