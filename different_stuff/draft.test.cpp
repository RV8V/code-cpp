#include <iostream>
#include <stdarg.h>
#include <memory>
#include <cstdlib>

using namespace std;

void vars(int, int, ...);
void vars_lib(int, ...);
void test_args(int, ..., int);
void while_args(int, int, ...);

void read_data(int*, int n, void(*)(int&));
void fill_arr(int*, int, int, void(*)(int*, int));

void callback_fill(int*, int);
void callback_read(int&);

void print(int, ...);
void print_terminat(int, ...);

template<typename ...Args>
void print_args(Args...);

int main(const int, const char**) {
  int count = 3, first = 1, second = 2;
  vars(count, first, second);
  vars(4, 8, 7, 3, 5);
  vars_lib(3, 2, 1, 4);
  while_args(2, 8, 9);
  test_args(2, 3, 4, 5, 4);

  print_args(20, 1, 2, 3, 4);

  int (*f)(int) = [](int a) -> int {
    return a * a;
  };

  cout << f(2) << " - " << f(f(2)) << endl;

  print(1, 2, 3);
  print_terminat(1, 2, 3, 4, 5, 0);

  int length = 4, value = 3;
  int* arr = (int*)malloc(sizeof(int) * length);

  fill_arr(arr, length, value, callback_fill);
  read_data(arr, length, callback_read);
  return EXIT_SUCCESS;
}

template<typename ...Args>
void print_args(Args ...args) {
  print_args(args...);
}

void print(int first, ...) {
  for (int i = 0; i < 2; ++i)
    cout << *(&first + i) << endl;
}

void print_terminat(int first, ...) {
  int i = 0;
  while(*(&first + i))
    cout << *(&first + i++) << '\n';
}

void read_data(int* arr, int number, void(*callback)(int&)) {
  for (int i = 0; i < number; ++i)
    callback(*(arr + i));
}

void fill_arr(int* arr, int length, int value, void(*callback)(int*, int)) {
  for (int* tmp = arr; tmp != arr + length; tmp++)
    callback(tmp, value);
}

void callback_read(int& n) { cout << n << '\n'; }

void callback_fill(int* pos, int value) {
  *pos = value;
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
