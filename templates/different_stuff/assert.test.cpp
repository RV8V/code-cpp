#include <iostream>
#include <cassert>
#include <cstdlib>
#include <assert.h>

#define NDEBUG

using namespace std;

static_assert(sizeof(long) == 8, "long must be 8 bytes");
static_assert(sizeof(int) == 4, "int must be 4 bytes");

int get_value(int*, const int);

int main(int, const char**) {
  int* arr = (int*)malloc(sizeof(int)* 2);
  int i = 1;
  do {
    *(arr + i) = i;
  } while(i-- > 0);

  i = 1;
  do {
    cout << "value: " << *(arr + i) << endl;
  } while(i-- > 0);

  get_value(arr, i = 1);
  return EXIT_SUCCESS;
}

int get_value(int* arr, const int index) {
  assert(index > 0 && "index is not valid here");
  return *(arr + index);
}
