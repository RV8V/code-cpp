#include <iostream>
#include <cstdlib>

void mp_init(void*);
void free_cpp(void*);

namespace cpp_ns {
  struct string_c {
    char* mp_str;
    size_t m_size;
    void (*mp_init)(void*);
    void init() {
      /*this == 0x*/
      /**((this = 0x) + (offset = 0)) = value*/mp_str = nullptr;
      /**((this = 0x) + (offset = 4)) = value*/m_size = 0;
    }
  };
  struct /*class*/ string_cpp {
    char* mp_str = (char*)malloc(10 * sizeof(char));
    int* mp_i = (int*)malloc(1 * sizeof(int));
    size_t m_size = 10;
    void (*free)(void*);
  };
  struct string_cpp_c {
    char* mp_str;
    int* mp_i;
    size_t m_size;
    string_cpp_c(void) {
      (*this).mp_str = new char[100];
      (*this).mp_i = new int;
      (*this).m_size = 0;
      std::cout << __FUNCTION__ << std::endl;
    };
    string_cpp_c(int): mp_str(nullptr), mp_i(nullptr), m_size(0) {
      (*this).mp_str = new char[100];
      std::cout << __FUNCTION__ << std::endl;
    };
    void str_free() {
      if ((*this).mp_str != nullptr)
        delete[](*this).mp_str;
    }
    ~string_cpp_c(void) {
      if ((*this).mp_str != nullptr)
        delete[](*this).mp_str;
      if ((*this).mp_i != nullptr)
        delete(*this).mp_i;
      std::cout << __FUNCTION__ << std::endl;
    };
  };
  class string_cpp_cl {
  private:
    char* mp_str;
    int* mp_i;
    size_t m_size;
  public:
    string_cpp_cl(void) {
      (*this).mp_str = new char[100];
      (*this).mp_i = new int;
      (*this).m_size = 0;
      std::cout << __FUNCTION__ << std::endl;
    };
    string_cpp_cl(int): mp_str(nullptr), mp_i(nullptr), m_size(0) {
      (*this).mp_str = new char[100];
      std::cout << __FUNCTION__ << std::endl;
    };
  private:
    void str_free() {
      if ((*this).mp_str != nullptr)
        delete[](*this).mp_str;
    }
  public:
    ~string_cpp_cl(void) {
      if ((*this).mp_str != nullptr)
        delete[](*this).mp_str;
      if ((*this).mp_i != nullptr)
        delete(*this).mp_i;
      std::cout << __FUNCTION__ << std::endl;
    };
  };
};

int main(int argc, char const *argv[]) {
  cpp_ns::string_c str_a;
  cpp_ns::string_c str_b;
  str_b.mp_init = &mp_init;
  //(*str_b.mp_init)((void*)str_b);
  str_a.init();
  std::cout << std::hex;
  std::cout << &str_a << ":" << &str_a.mp_str << " next: " << &str_a.m_size << std::endl;
  std::cout << &str_b << ":" << &str_b.mp_str << " next: " << &str_b.m_size << std::endl;
  std::cout << std::dec;

  {
    std::cout << "enter into area of ​​visibility -> constructor" << std::endl;
    cpp_ns::string_cpp_c str();
    std::cout << "exit of area of ​​visibility -> destructor" << std::endl;
  }

  {
    std::cout << "enter into area of ​​visibility -> constructor" << std::endl;
    cpp_ns::string_cpp_cl str(1);
    std::cout << "exit of area of ​​visibility -> destructor" << std::endl;
  }

  return 0;
}

void mp_init(void* str) {
  /**((0x) + (offset = 0)) = value*/(*(cpp_ns::string_c*)str).mp_str = nullptr;
  /**((0x) + (offset = 4)) = value*/(*(cpp_ns::string_c*)str).m_size = 0;
}

void free_cpp(void* inst) {
  free((*((cpp_ns::string_cpp*)inst)).mp_str);
  free((*((cpp_ns::string_cpp*)inst)).mp_i);
}
