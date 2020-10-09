#include <iostream>
#include "lesson4.constructor.h"

int main(int argc, char const *argv[]) {
  cpp_ns::string a("hello world");
  std::cout << a.c_str() << std::endl;

  char* ch_a = new char[5]; char* ch_b;
  ch_b = ch_a;
  delete[] ch_a; delete[] ch_b;

  char* ch_a_s = new char[5];
  char* ch_b_s = new char[5];
  delete[] ch_a_s; delete[] ch_b_s;

  cpp_ns::string b;
  {
    cpp_ns::string tmp("test example");
    cpp_ns::string tmp_a(tmp);
    b = tmp; /*copy address*/
    b = 1.2; tmp = tmp;
    bool f_a = b > tmp; bool f_b = tmp > b;
    std::cout << f_a << f_b << std::endl;
  }
  std::cout << b.c_str() << std::endl;
  return 0;
}
