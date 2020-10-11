#include <iostream>
#include <stdarg.h>

using namespace std;

void vars(int, int, ...);
void vars_lib(int, ...);
void test_args(int, ..., int);
void while_args(int, int, ...);

int main(const int, const char**) {
  int count = 3, first = 1, second = 2;
  vars(count, first, second);
  vars(4, 8, 7, 3, 5);
  vars_lib(3, 2, 1, 4);
  while_args(2, 8, 9);
  test_args(2, 3, 4, 5, 4);
  return EXIT_SUCCESS;
}

void while_args(int count, int first, ...) {
  int* ptr = &first;
  while(count--) {
    cout << *ptr << endl;
    ptr++;
  }
}

void test_args(int first, ..., int count) {
  int* ptr = &first;
  for (int i = 0; i < count; ++i)
    cout << "current: " << *(ptr + i) << endl;
}

void vars(int num, int first, ...) {
  int* ptr = &first;
  int i = 0;
  do {
    cout << "number: " << num << " " << "value -> " << *(ptr + i) << endl;
    i++;
  } while(num-- > 1);
}

void vars_lib(int count, ...) {
  va_list args;
  va_start(args, count);
  do {
    cout << "value is: " << va_arg(args, int) << endl;
  } while(count-- > 1);
  va_end(args);
}
