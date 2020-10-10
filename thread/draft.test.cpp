#include <iostream>
#include <stdarg.h>

using namespace std;

int function_to_test(int, ...);

int main(void) {
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
