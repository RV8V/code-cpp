#include <iostream>
#include <stdarg.h>
#include <thread>
#include <future>
#include <cmath>
#include <functional>
#include <limits>

using namespace std;

int function_to_test(int, ...);

int f(int, int);
void task_lambda_error(void);
void task_thread(void);
void test_bind(void);
void test_promise(void);

int main(void) {
  //task_lambda_error();
  //task_thread();
  //test_bind();
  //int sum = function_to_test(5, 1, 2);
  //cout << "sum: " << sum << endl;
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
  thread future_thread(ref(functor), value_a, value_b);
  future_thread.join();
  cout << "result is -> " << ft.get() << endl;
}

void test_bind(void) {
  int value = 0;
  packaged_task<int(int)> functor(bind([](int a) {
    return a * a;
  }, value = 3));
  future<int> ft = functor.get_future();
  functor(value = 2);
  cout << "bind -> " << ft.get() << endl;
}

void test_promise(void) {
  shared_ptr<promise<void>> p_promise = make_shared<promise<void>>();
  future<void> waiter = p_promise->get_future();
  auto call = [p_promise](size_t value) {
    size_t i = numeric_limits<size_t>::max();
    while(true) {
      if (value == i--) {
        p_promise->set_value();
        cout << "value has been getted" << endl;
        break;
      }
    }
  };
  thread promise_thread(ref(call), numeric_limits<size_t>::max() - 5000);
  promise_thread.detach();
  waiter.get();
}
