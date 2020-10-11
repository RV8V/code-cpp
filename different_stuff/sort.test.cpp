#include <iostream>
#include <stdarg.h>

using namespace std;

void less_sort(int& x, int& y) {
  if (int tmp = 0; x > y) {
    tmp = x;
    x = y;
    y = tmp;
  }
}

void greater_sort(int& x, int& y) {
  if (int tmp = 0; x < y) {
    tmp = x;
    x = y;
    y = tmp;
  }
}

void sort(int* arr, int n, void (*f)(int&, int&)) {
  for (int* p = arr; p != arr + n; p++)
    for (int m = 0; m < n; ++m)
      f(*p, *(arr + m));
}

int main(int, const char**) {
  void (*less_sort_ptr)(int&, int&) = &less_sort;
  void (*greater_sort_ptr)(int&, int&) = &greater_sort;

  int arr[5] = { 12, 42, 52, 52, 59 };

  sort(arr, 5, less_sort_ptr);
  for (int* p = arr; p <= arr + 5; ++p)
    cout << *p << ", ";
  cout << endl;

  cout << "\t-----\t" << '\n';

  sort(arr, 5, greater_sort_ptr);
  for (int *p = arr; p != arr + 5; p++)
    cout << *p << ", ";
  cout << endl;

  return EXIT_SUCCESS;
}
