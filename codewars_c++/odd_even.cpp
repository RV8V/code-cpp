#include <iostream>

#define even_or_odd_m(n) n % 2 == 0 ? "odd" : "even"

const char* even_or_odd(int number)
{
  return number & 0x01 ? "odd" : "even";
}

std::string even_or_odd(char number)
{
  return (std::string[]){"odd", "even"}[number % 2];
}

namespace Kata
{
  const char* const even{"even"};
  const char* const odd{"odd"};
}

const char* const& even_or_odd_n(char const number)
{
  return number & 1 ? Kata::odd : Kata::even;
}

int main()
{
  const char* res_c = even_or_odd(10);
  std::string res_s = even_or_odd(20);
  const char* res_m = even_or_odd_m(10);
  const char* const res_n = even_or_odd_n(20);
  return 0;
}
