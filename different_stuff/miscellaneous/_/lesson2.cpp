#include <iostream>
#include <ctime>
#include <cstdlib>
#include <clocale>

struct Test { float f; };
enum name { ONE, TWO, END };

int main(int argc, char const *argv[]) {
  struct Test test = { 2. };
  enum name n = TWO;
  std::cout << sizeof(n) << '\n';

  const char* s = "hello world";
  try {
    throw s;
  } catch(const char* elem) {
    std::cout << "error: " << *elem << '\n';
  }
  unsigned char i = 0;
  const int &ref = (const int)i;
  std::cout << "ref: " << ref << '\n' \
  << "value: " << i << '\n';

  const int d = 0;
  const int &r = (const int)d;

  int *val = new int(7);
  int *next = new int; *next = 7;
  std::cerr << "value: " << *val << std::endl \
  << "next: " << *next << std::endl;
  delete val; delete next;

  float *p_arr = new float[10];
  short int o = 0; srand(time(NULL));
  do *(p_arr + o) = (rand() % 10) + 1;
  while(o++ < 10);
  o = 0;
  do std::cout << *(p_arr + o) << std::endl;
  while(o++ < 10);
  delete[] p_arr;

  char string[100];
  std::cout << "enter value: ";
  std::cout << "your value: " << string << '\n';

  return 0;
}
