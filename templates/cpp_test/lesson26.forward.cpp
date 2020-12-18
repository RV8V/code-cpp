#include <iostream>

namespace test_a {
  void f_a(int& a) { std::cout << "lvalue" << std::endl; }
  void f_a(int&& a) { std::cout << "rvalue" << std::endl; }
  void f_b(const int& a) { std::cout << "const lvalue" << std::endl; }
  template<typename T>
  void wrapper(T&& r_value) {
    f_a(r_value);
    f_a(std::forward<T>(r_value));
    std::cout << std::endl;
  }
  void test_a(void) { int i = 0; f_a(i); f_a(int(0)); }
  void test_b(void) { int i = 0; wrapper(i); wrapper(0); }
};

namespace test_for {
  void f_f(const std::string& str) {
    std::string c_str{str};
    std::cout << c_str << std::endl;
  }
  void f_f(std::string&& str) {
    std::string m_str{std::move(str)};
    std::cout << m_str << std::endl;
  }
  template<typename T>
  void wrapper_a(T&& r_value) {
    std::cout << "enter rvalue ref, get lvalue inside and was called copy constructor" << std::endl;
    f_f(r_value);
  }
  template<typename T>
  void wrapper_b(T&& r_value) {
    std::cout << "enter rvalue ref, do not converted to lvalue, &&" << std::endl;
    f_f(std::forward<T>(r_value));
  }
  void test(void) {
    std::string str{"hello world"}; std::cout << std::endl;
    wrapper_b(std::move(str));
    wrapper_a(std::move(str));
    wrapper_b(std::move(str));
  }
};


int main(int argc, char const *argv[]) {
  // test_a::test_a();
  // test_a::test_b();
  test_for::test();
  return 0;
}
