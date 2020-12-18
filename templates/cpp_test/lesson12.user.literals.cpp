#include <iostream>

void integer_literals(void);
void float_literals(void);
void character_literals(void);
void string_literals(void);
void boolean_literals(void);
void pointer_literals(void);

/*
const char*
unsigned long long int
long double
char
wchar_t
char16_t
char32_t
const char* ,     std::size_t
const wchar_t* ,  std::size_t
const char16_t* , std::size_t
const char32_t* , std::size_t
*/

constexpr long double operator"" _deg(long double deg) {
  return deg * 3.141592 / 180.;
}

constexpr long double operator"" _rad(long double rad) {
  return rad * 180. / 3.141592;
}

struct Kilogram {
  explicit constexpr Kilogram(double wgt): weight{wgt} {};
  double weight;
};

struct Pounds {
  explicit constexpr Pounds(double wgt): weight{wgt} {};
  double weight;
};

constexpr Kilogram operator"" _kgkg(long double wgt) {
  return Kilogram{static_cast<double>(wgt)};
}

constexpr Kilogram operator"" _kglbs(long double wgt) {
  return Kilogram{static_cast<double>(wgt * 0.45359237)};
}

constexpr Pounds operator"" _lbkg(long double wgt) {
  return Pounds{static_cast<double>(wgt * 2.2046)};
}

constexpr Pounds operator"" _lblbs(long double wgt) {
  return Pounds{static_cast<double>(wgt)};
}

int main(int argc, char const *argv[]) {
  long double rad = 20.0_deg;
  long double deg = 20.0_rad;

  std::cout << rad << std::endl;
  std::cout << deg << std::endl;

  Kilogram kg_a = 100._kgkg;
  Kilogram kg_b = 100._kglbs;
  Kilogram kg_c = Kilogram{100};
  Kilogram kg_d = Kilogram(100);
  Kilogram kg_e = 100; // not explicit constructor call

  Pounds lb_a = 100._lbkg;
  Pounds lb_b = 100._lblbs;
  return 0;
}

void integer_literals() {
  auto a1 = 1;
  auto a2 = 01;
  auto a3 = 0x0a;
  auto a4 = 0X0A;
  auto a5 = 0b101010;

  auto ai = 0;
  auto aui = 0U;
  auto al = 0l;
  auto all = 0ll;

  auto l1 = 18446744073709550592ull;
  auto l2 = 18'446'744'073'709'550'592llu;
  auto l3 = 1844'6744'0737'0955'0592uLL;
  auto l4 = 184467'440737'0'95505'92LLU;
  auto l5 = 1'440737'1LLU;
}

void float_literals(void) {
  auto f1 = 123.456e-67;
  auto f2 = .1E11f;
  auto f3 = 58.;
  auto f4 = 4e2;
  auto f5 = 1.f;
  auto f6 = 1.l;
  auto f7 = 1.23e+3;
  auto f8 = 1.23e-3;
}

void character_literals(void) {
  auto c1 = 'a';
  auto c2_16 = u'a';
  auto c3_32 = U'a';
  auto c4 = L'a';
  auto c5 = 'abc';

  std::cout << sizeof(c1) << std::endl;
  std::cout << sizeof(c2_16) << std::endl;
  std::cout << sizeof(c3_32) << std::endl;
  std::cout << sizeof(c4) << std::endl;
  std::cout << sizeof(c5) << std::endl;
}

void string_literals(void) {
  auto s1 = "hello";
  auto s2 = "\nhello\\n\n";
  auto s3 = "hello\nworld";
  auto s4 = R"(
            hello\n
            )";
  auto s5 = R"(hello
               world)";
  auto s6 = u8"hello";
  auto s7 = u8R"(hello)";
  auto s8 = u"hello";
  auto s9 = uR"(hello)";
  auto s10= U"hello";
  auto s11= UR"(hello)";
}

void boolean_literals(void) {
  auto b1 = true;
  auto b2 = false;
}

void pointer_literals(void) {
  void* p = nullptr;
}
