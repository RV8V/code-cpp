#include <iostream>

void example_a(void) {
  struct A {
    virtual void f1(void) const { std::cout  << __FUNCTION__ << "-> A::f1() -> void" << std::endl; }
    virtual char const f1(int) { std::cout  << __FUNCTION__ << "-> A::f1() -> char const int" << std::endl; return 0; }
    virtual const char* f1(const char*) { const char* s = ""; std::cout  << __FUNCTION__ << "-> A::f1() -> char*" << std::endl; return s; }
    virtual void f2(int) { std::cout  << __FUNCTION__ << "-> A::f2() -> int" << std::endl; }
    virtual void f2(short int) { std::cout  << __FUNCTION__ << "-> A::f2() -> short int" << std::endl; }
    void f3(void) { std::cout  << __FUNCTION__ << "-> A::f3()" << std::endl; }
    void f3(void) const { std::cout  << __FUNCTION__ << "-> A::f3()" << std::endl; }
  };
  struct B : A {
    virtual void f1(void) const override { std::cout  << __FUNCTION__ << "-> B::b1() -> void" << std::endl; }
    virtual void f1(long, long) { std::cout  << __FUNCTION__ << "-> B::b1() -> long, long" << std::endl; }
    virtual void f2(unsigned) { std::cout  << __FUNCTION__ << "-> B::b2() -> unsigned" << std::endl; }
    virtual void f3(char) { std::cout  << __FUNCTION__ << "-> B::b3() -> char" << std::endl; }
    void f3(void) const { std::cout  << __FUNCTION__ << "-> B::b3() -> void, const" << std::endl; }
  };

  A a; B b;
  a.f1(); a.f2(1); a.f3();
  b.f1(); b.f2(1); b.f3();

  A* p_a = new B;
  (*p_a).f1(); (*p_a).f2(1); (*p_a).f3();
};

void example_a(int) {
  struct A {
    virtual void f1(void) const { std::cout  << __FUNCTION__ << "-> A::f1() -> void" << std::endl; }
    virtual char const f1(int) { std::cout  << __FUNCTION__ << "-> A::f1() -> char const int" << std::endl; return 0; }
    virtual void f1(long, long) { std::cout  << __FUNCTION__ << "-> A::b1() -> long, long" << std::endl; }
    virtual const char* f1(const char*) { const char* s = ""; std::cout  << __FUNCTION__ << "-> A::f1() -> char*" << std::endl; return s; }
    virtual void f2(int) { std::cout  << __FUNCTION__ << "-> A::f2() -> int" << std::endl; }
    virtual void f2(unsigned) { std::cout  << __FUNCTION__ << "-> A::b2() -> unsigned" << std::endl; }
    virtual void f2(short int) { std::cout  << __FUNCTION__ << "-> A::f2() -> short int" << std::endl; }
    void f3(void) { std::cout  << __FUNCTION__ << "-> A::f3()" << std::endl; }
    virtual void f3(char) { std::cout  << __FUNCTION__ << "-> A::b3() -> char" << std::endl; }
    // void f3(void) const { std::cout  << __FUNCTION__ << "-> A::f3()" << std::endl; }
    virtual void f3(void) const { std::cout  << __FUNCTION__ << "-> A::f3()" << std::endl; }
  };
  struct B : A {
    virtual void f1(void) const override { std::cout  << __FUNCTION__ << "-> B::b1() -> void" << std::endl; }
    virtual void f1(long, long) override { std::cout  << __FUNCTION__ << "-> B::b1() -> long, long" << std::endl; }
    virtual void f2(unsigned) override { std::cout  << __FUNCTION__ << "-> B::b2() -> unsigned" << std::endl; }
    virtual void f3(char) override { std::cout  << __FUNCTION__ << "-> B::b3() -> char" << std::endl; }
    virtual void f3(void) const override { std::cout  << __FUNCTION__ << "-> B::b3() -> void, const" << std::endl; }
  };

  A a; B b;
  a.f1(); a.f2(1); a.f3();
  b.f1(); b.f2(1); b.f3();

  A* p_a = new B;
  (*p_a).f1(); (*p_a).f2(1); (*p_a).f3();
};

void example_a(char) {
  struct A {
    virtual void f_a(void) final {};
    virtual const char* f_b(const char*) { const int i = 0; const int* p_i = &i; std::cout << __FUNCTION__ << std::endl; return (const char*)p_i; };
  };
  struct B : A {
    void f_a_o(void) {};
    void f_a(int) const final { std::cout << __FUNCTION__ << "can be overriden because of not equal parameter types (int)" << std::endl; };
    virtual void f_a(void) const override final { std::cout << __FUNCTION__ << "can be overriden because of not equal parameter types (const)" << std::endl; };
    const char* f_b(const char*) { const int i = 0; const int* p_i = &i; std::cout << __FUNCTION__ << std::endl; return (const char*)p_i; };
  };
  struct C : B {
    void f_a(int) const { std::cout << __FUNCTION__ << "can not be overriden because of equal parameter types (int) and so on" << std::endl; };
    void f_a(void) const override { std::cout << __FUNCTION__ << "can not be overriden because of equal parameter types (const) and so on" << std::endl; };
  };
}

void example_a(unsigned) {
  struct A final { A(int) { std::cout << "can not be extended because of final key word" << std::endl; } ~A() {} };
  struct B : A { B(int) {} B(void) {} ~B(void) { std::cout << "can be extended" << std::endl; } };
  struct C final : B { C(unsigned) { std::cout << "class C is final one" << std::endl; } };
  struct D : C { D(char) { std::cout << "can not be anyway" << '\n'; } };
}

int main(int argc, char const *argv[]) {
  example_a('a');
  example_a(-1);
  return 0;
}
