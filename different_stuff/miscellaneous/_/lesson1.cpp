#include <iostream>
#include <cstdlib>
#include <ctime>

int main(int argc, char const *argv[]) {
  srand(time(NULL));
  const char ch = std::cin.get();
  std::cout << "takes only first symbol: " << ch \
   << (rand() % 10) + 1 << std::endl;
  const std::string hello = "hello";
  std::string v_test;
  std::cout << "enter test string: ";
  std::getline(std::cin, v_test); std::cout << v_test << '\n';
  const char *st = "hello world"; char s[15];
  unsigned short int i = 0;
  while(*(s + i) = (char)*st++)
    std::cout << "test: " << i++ << '\n';
  std::cout << s << '\n';
  char v[10]; std::cin >> v;
  std::string _v; std::cin >> _v;
  std::string string_value;
  std::getline(std::cin, string_value);
  std::cout << "v: " << v << " " << "_v: " << _v << std::endl;
  std::cout << "string value: " << string_value << std::endl;

  srand(static_cast <unsigned int>(time(0)));
  std::cout << "rand() % 30 -> " << rand() % 30 << '\n';
  unsigned int t = (unsigned int)time(0);
  std::cout << "time: " << t << '\n';
  int h = 0;
  // unsigned int g = (unsigned int)time(h);
  return 0;
}
