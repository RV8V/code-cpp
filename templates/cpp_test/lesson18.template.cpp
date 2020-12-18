#include <iostream>

#define template_max(name, type) type max_##name(type a, type b) { return a > b ? a : b; }

template_max(int, int);
template_max(float, float);

template<typename T> T max(T a, T b) { return a > b ? a : b; }

int main(int argc, char const *argv[]) {
  const float f = max_float(1., 3.);
  const int i = max_int(1, 3);
  const char ch = (char)max<double>(i, f);
  std::cout << f << " " << i << ch << std::endl;
  return 0;
}
