#include <iostream>

class A {
public:
  A() {
  }
  virtual ~A() = 0;
};

A::~A() {};

class B : public A {
public:
  B() {
  }
  ~B() override {
  }
};

int main(int, char const**) {
  A* p_b = (A*)new B;
  delete p_b;
  return 0;
}
