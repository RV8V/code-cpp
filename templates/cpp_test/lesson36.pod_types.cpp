#include <iostream>
#include <string>
#include <cstring>
#include <type_traits>
#include <stdlib.h>
#include <vector>
#include <ctime>

#define R_STRING ""
#define VALUE 30
#define TEN 10
enum { RANDOM_VALUE = 0 };

void print_info(void);

struct s0 {};
struct s1 { public: int i; };
struct s2 { public: s2(int a, const char* s): i{a}, ch{s} {} ~s2(void) {} s2(const s2&) {} s2 &operator=(const s2&) {} private: int i; const char* ch; };
struct s3 { public: s3(void) {} s3(int a): i{a} {} s3(s3&&) {} s3 &operator=(s3&&) {} ~s3(void) {} void test(void) { std::vector<int> v{}; for(auto &i : v) {}; } protected: int i; };
struct s4 { s4() = default; s4(int a): i{a}, p_data{nullptr} {} void test(s4&& obj) { (*this).p_data = obj.p_data; } void lambda(void) { auto l = [&](){}; } int i; int* p_data; };
struct s5 { s5(int val): i{RANDOM_VALUE} { srand(time(NULL)); (*this).val = char(rand() % TEN - VALUE); } int i; char val; virtual void f(char* ch) const {}; };
struct s6 { virtual void f(void) const {}; constexpr long double operator"" _deg(long double deg) { return deg * 3.141592 / 180.; } };
struct s7 { int i; protected: int j; };
struct s8 { int i; private: int j; };
struct s9 { int i; protected: static int j; };
struct s10 { protected: int i; void* p_data; };
struct s11 { private: std::string str; };
struct s12 { static std::string str; };
struct s13 : s1 { s13(unsigned): u_ch{(unsigned)RANDOM_VALUE} {} s13(void): str{R_STRING} {}; private: const char* str; unsigned u_ch; };
struct s14 : s0 { int j; static void f(void) {} };
struct s15 : s1 { int j; };
struct s16 : s0, s1 {};

template<class T> const T st_arr[16];
template<typename T, typename R> void copy(const T* from, R* to, int count) {
  if (std::is_pod<T>::value || std::is_pod<R>::value) std::memcpy(to, from, count * sizeof(T));
  else for(char i = 0; i < count; ++i) *(to + i) = *(from + i);
}

int main(int argc, char const **argv) {
  print_info(); const char* world = "world"; char hello[5];
  copy(&hello, &world, 5);
  return 0;
}

void print_info(void) {
  std::cout << "s0 -> " << (std::is_pod<s0>::value ? "is POD" : "not POD") << std::endl;
  std::cout << "s1 -> " << (std::is_pod<s1>::value ? "is POD" : "not POD") << std::endl;
  std::cout << "s2 -> " << (std::is_pod<s2>::value ? "is POD" : "not POD") << std::endl;
  std::cout << "s3 -> " << (std::is_pod<s3>::value ? "is POD" : "not POD") << std::endl;
  std::cout << "s4 -> " << (std::is_pod<s4>::value ? "is POD" : "not POD") << std::endl;
  std::cout << "s5 -> " << (std::is_pod<s5>::value ? "is POD" : "not POD") << std::endl;
  std::cout << "s6 -> " << (std::is_pod<s6>::value ? "is POD" : "not POD") << std::endl;
  std::cout << "s7 -> " << (std::is_pod<s7>::value ? "is POD" : "not POD") << std::endl;
  std::cout << "s8 -> " << (std::is_pod<s8>::value ? "is POD" : "not POD") << std::endl;
  std::cout << "s9 -> " << (std::is_pod<s9>::value ? "is POD" : "not POD") << std::endl;
  std::cout << "s10 -> " << (std::is_pod<s10>::value ? "is POD" : "not POD") << std::endl;
  std::cout << "s11 -> " << (std::is_pod<s11>::value ? "is POD" : "not POD") << std::endl;
  std::cout << "s12 -> " << (std::is_pod<s12>::value ? "is POD" : "not POD") << std::endl;
  std::cout << "s13 -> " << (std::is_pod<s13>::value ? "is POD" : "not POD") << std::endl;
  std::cout << "s14 -> " << (std::is_pod<s14>::value ? "is POD" : "not POD") << std::endl;
  std::cout << "s15 -> " << (std::is_pod<s15>::value ? "is POD" : "not POD") << std::endl;
  std::cout << "s16 -> " << (std::is_pod<s16>::value ? "is POD" : "not POD") << std::endl;
}
