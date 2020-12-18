#include <iostream>
#include <cstring>

#define VALUE_SIZE 100
#define TEST_ERR_CODE 1
#define SYMBOL_STR 1

namespace const_exc_a {
  class A {
  private:
    char* m_data{nullptr};
  public:
    A() {
      std::cout << "A()" << std::endl;
      (*this).m_data = new char[VALUE_SIZE];
      throw TEST_ERR_CODE;
    }
    ~A() {
      std::cout << "~A()" << std::endl;
      delete[](*this).m_data;
    }
  };
  void test(void) try { A a; } catch(...) { std::cout << "exception was caught" << std::endl; }
};

namespace const_exc_b {
  class Base {
  protected:
    char* m_data{nullptr};
  public:
    Base() {
      std::cout << "Base()" << std::endl;
      (*this).m_data = new char[VALUE_SIZE];
      memset((*this).m_data, 0, VALUE_SIZE);
    }
    ~Base() {
      std::cout << "~Base()" << std::endl;
      delete[](*this).m_data;
    }
  };

  class Child : public Base {
  private:
    char* m_data{nullptr};
  public:
    Child() {
      std::cout << "Child()" << std::endl;
      (*this).m_data = new char[strlen(Base::m_data) + SYMBOL_STR];
      strcpy((*this).m_data, Base::m_data);
      throw TEST_ERR_CODE;
    }
    ~Child() {
      std::cout << "~Child()" << std::endl;
      delete[](*this).m_data;
    }
  };
  void test(void) try { Child c; } catch(...) { std::cout << "exception was caught" << std::endl; }
};

namespace const_exc_c {
  struct A {
    A() { std::cout << "A()" << std::endl; }
    ~A() { std::cout << "~A()" << std::endl; }
  };
  struct B {
    B() { std::cout << "B()" << std::endl; }
    ~B() { std::cout << "~B()" << std::endl; }
  };
  struct C {
    C() { std::cout << "C()" << std::endl; throw TEST_ERR_CODE; }
    ~C() { std::cout << "~C()" << std::endl; }
  };
  struct D {
    D() { std::cout << "D()" << std::endl; }
    ~D() { std::cout << "~D()" << std::endl; }
  };
  struct Unit {
  private: A a; B b; C c; D d;
  public:
    Unit() { std::cout << "Unit()" << std::endl; }
    ~Unit() { std::cout << "~Unit()" << std::endl; }
  };
  void test(void) try { Unit unit; }  catch(...) { std::cout << "exception was caught" << std::endl; }
};

namespace const_exc_d {
  void fn_throw(void) noexcept(false) { std::cout << "exception" << std::endl; throw TEST_ERR_CODE; }
  struct str_destructor {
    ~str_destructor() { std::cout << "~str_destructor" << std::endl; }
  };
  struct Test {
  private: str_destructor d;
  public:
    ~Test() {
      try {
        std::cout << "~Test() called" << std::endl;
        if (std::uncaught_exception()) std::cerr << "~Test() stack unwinding, not throw" << std::endl;
        else {
          std::cerr << "~Test() stack is not unwinding so we can throw here error, normal" << std::endl;
          fn_throw();
        }
      }
      catch(...) { std::cout << "~Test() exception was caught here" << std::endl; }
    }
  };
  void test(void) try { Test test; throw 123; } catch(int i) { std::cout << "int exception" << std::endl; } catch(...) { std::cout << "other" << std::endl; }
};

int main(int, char const**) {
  const_exc_a::test();
  const_exc_b::test();
  const_exc_c::test();
  const_exc_d::test();
  return 0;
}
