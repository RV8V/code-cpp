#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <cstring>
#include <ctime>

namespace example_a {
  struct data {
    data() { std::cout << "data()" << std::endl; }
    data(const data&) { std::cout << "data(const data&)" << std::endl; }
    data &operator=(const data&) { std::cout << "data &operator=(const data&)" << std::endl; }
    data(data&&) { std::cout << "data(data&&)" << std::endl; }
    data &operator=(data&&) { std::cout << "data &operator=(data&&)" << std::endl; }
    ~data() { std::cout << "~data()" << std::endl; }
  };
  template<class T>
  void swap_a(T &a, T &b) {
    std::cout << "swap is started" << std::endl;
    T temp{a};
    a = b;
    b = temp;
    std::cout << "swap is ended" << std::endl;
  }
  template<class T>
  void swap_move(T &a, T &b) {
    std::cout << "swap is started" << std::endl;
    T temp{std::move(a)};
    a = b;
    b = temp;
    std::cout << "swap is ended" << std::endl;
  }
  void test(void) {
    std::vector<data> v1{data()};
    std::vector<data> v2{data()};
    swap_a(v1, v2);
    std::cout << std::endl;
    swap_move(v1, v2);
  }
};

namespace example_b {
  void test(void) {
    std::vector<int> a{1, 2, 3, 4, 5};
    std::vector<int> b;
    std::cout << "a size -> " << a.size() << std::endl;
    std::cout << "b size -> " << b.size() << std::endl;

    b = std::move(a);
    std::cout << "a size -> " << a.size() << std::endl;
    std::cout << "b size -> " << b.size() << std::endl;
  }
};

namespace example_c {
  void foo_a(int&& obj) {
    int copy_obj{obj}; /*copy constructor*/
    int move_obj(std::move(obj)); /*move constructor*/
  }
  void test(void) {
    foo_a(int());
    int obj{4};
    // foo_a(obj); -> error, needs rvalue but passed lvalue reference
    foo_a(std::move(obj));
    foo_a(1);
  }
};

namespace example_d {
  struct data {
    int* p_data{nullptr};
    int size{100};
    data() { p_data = new int[size]; }
    data(data &&obj) {
      (*this).p_data = obj.p_data;
      (*this).size = obj.size;
      obj.p_data = nullptr;
      obj.size = 0;
    }
  };
  void test(void) {
    data a;
    // data b(a); -> error
    data b(std::move(a));
    std::cout << std::endl;
  }
};

const int obj_count = 30000;
namespace example_e {
  struct str {
    std::string m_str;
    str(int size) { m_str.resize(size); }
    str(const str& obj): m_str(obj.m_str) {}
    str& operator=(const str& obj) {
      this->m_str = obj.m_str;
      return *this;
    }
    ~str() {}
  };
  struct data {
    std::vector<str> m_data;
    data(string) {
      for(int i = 0; i < obj_count; ++i)
        m_data.push_back(str(i));
    };
    data(const data& obj): m_data(obj.m_data) {};
    data& operator=(const data& obj) {
      this->m_data = obj.m_data;
      return *this;
    };
    ~data() {};
  };
  void test(void) {
    std::vector<data> v;
    v.reserve(3);
    auto start = chrono::steady_clock::now();
    v.push_back(data("test_1"));
    v.push_back(data("test_2"));
    auto end = chrono::steady_clock::end();
    std::cout << chrono::duration_cast<chrono::milliseconds>(end - start).count() << "ms" << std::endl;
  }
};

template<class T>
typename remove_reference<T>::type&&
move(T&& a) { return a; }

int main(int argc, char const *argv[]) {
  example_a::test();
  example_b::test();
  example_c::test();
  example_c::data d1;
  example_c::data d2(d1);
  example_c::data d3 = d2;
  example_c::data d4;
  d4 = d3;
  example_c::data d5(std::move(d1));
  example_c::data d6 = std::move(d2);
  example_c::data d7;
  d7 = move(d3);
  return 0;
}
