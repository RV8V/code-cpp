#include <iostream>

#define this int
#define function multiply(
#define takes int a
#define two ,
#define numbers int b) {
#define calculates return
#define their a
#define multiplication * b;
#define end };

this function takes two numbers
  calculates their multiplication
end

template<typename T>
inline const T multiply(const T a, const T b)
{
  return a * b;
}

auto multiply_l = [](auto a, auto b)->auto { return static_cast<int>(a * b); };

int main()
{
  return 0;
}
