#include <iostream>

#define template_max(name, type) type max_##name(type a, type b) { return a > b ? a : b; }

template_max(int, int);
template_max(float, float);

template<typename T> T max(T a, T b) { return a > b ? a : b; }

namespace ns_cpp_a {
  template<typename T> T max(T a, T b) { a > b ? a : b; }
  template<> char* max(char* a, char* b) { /*some code for comparison -> return 0;*/ }
  template<typename T, int n> void sort(T (&a)[n]) {
    for (char i = 0; i < n - 1; i++)
      for (char j = 0; j < n - i - 1; j++)
        if (a[j] > a[j + 1])
          std::swap(a[j], a[j + 1]);
  }
  template<int n> void sort(char* (&ar)[n]) {
    char* tmp = ar[0];
    ar[0] = ar[1];
    ar[1] = tmp;
  }

  void print_arr(char** a, int n) {
    int i = 0;
    do std::cout << *(*a + i) << ","; while(i++ < n);
    std::cout << std::endl;
  }

  void test(void) {
    const double d = max<double>(1, 2);
    char* c_a = (char*)"aa";
    char* c_b = (char*)"ab";
    char* c_c = (char*)"ba";

    char* tmp{nullptr};
    tmp = max(c_a, c_b);
    tmp = max(c_a, c_c);

    int i_arr_a[]{4, 3, 2, 1};
    sort(i_arr_a);

    char* c_str_a[] = {(char*)"1", (char*)"4", (char*)"2"};
    char* c_str_b[] = {(char*)"110", (char*)"100"};
    sort(c_str_a); sort(c_str_b);
    print_arr(c_str_a, 3);
    print_arr(c_str_b, 2);

    std::string str_arr[] = {"110", "100"};
    sort(str_arr);
  }
};

namespace ns_cpp_b {
  template<typename T> void f(T) { std::cout << "1" << std::endl; }
//  template<typename T> void f(T&) { std::cout << "2" << std::endl; }
  template<typename T> void f(int, T, double) { std::cout << "3" << std::endl; }
  template<class T> void f(T*) { std::cout << "4" << std::endl; }
  template<> void f<int>(int) { std::cout << "5" << std::endl; }
  void f(double) { std::cout << "6" << std::endl; }

  void test(void) {
    bool b{false}; int i{0}; double d{1.};
    f(b); f(i); f(i, 0, 0.); f(&i); f(i); f(d);
  }
};

namespace ns_cpp_c {
  template<class T> void f(T) { std::cout << "1" << std::endl; }
  template<class T> void f(T*) { std::cout << "2" << std::endl; }
  template<class T> void f(char*, T) { std::cout << "4" << std::endl; }
  template<> void f(int*) { std::cout << "3" << std::endl; }
  void test(void) { int* p{nullptr}; f(p); }
};

namespace ns_cpp_reverse {
  template<class T> void f(T) { std::cout << "1" << std::endl; }
  template<class T> void f(T*) { std::cout << "2" << std::endl; }
  template<> void f(int*) { std::cout << "3" << std::endl; }
  template<class T> void f(char*, T) { std::cout << "4" << std::endl; }
  void test(void) { int* p{nullptr}; f(p); }
};

namespace ns_cpp_order {
  void f(int*) std::cout << "1" << std::endl;
  template<class T> void f(T) std::cout << "2" << std::endl;
  template<> void f(int*) std::cout << "3" << std::endl;
  template<class T> void f(T*) std::cout << "4" << std::endl;
  void test(void) { int* p{nullptr}; f(p); }
};

int main(int argc, char const *argv[]) {
  const float f = max_float(1., 3.);
  const int i = max_int(1, 3);
  const char ch = (char)::max<double>(i, f);
  std::cout << f << " " << i << ch << std::endl;
  ns_cpp_reverse::test();
  ns_cpp_order::test();
  return 0;
}
