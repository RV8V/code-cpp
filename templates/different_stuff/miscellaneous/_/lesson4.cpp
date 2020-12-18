#include <iostream>
#include <cmath>

const short int value = 20;
const char ch = -10;

class First {
protected:
  First(int val) {
    this->value = val;
    std::cout << "value is: " << this->value << std::endl;
  };
  int value;
  ~First() {};
};

class Second : public First {
public:
  Second(int val) : First(val) {}
};

class _ {};

class A {
public:
  A(void) {};
  A(char a, char b, char c) {
    this->y = (int)a;
    this->m = (int)b;
    this->d = (int)c;
  };
  void msg() {
    std::cout << this->y << this->m << this->d << std::endl;
  };
  ~A() {
    std::cout << "instance of class A" << '\n';
  }
private:
  int y, m, d;
};

class b;

class a {
  friend int sum(a, b);
private:
  int i;
public:
  a() {
    std::cout << "enter value for i: ";
    std::cin >> this->i;
  }
  ~a() {
    std::cout << "class a" << '\n';
  }
};

class b {
  friend int sum(a, b);
private:
  int g;
public:
  b() {
    std::cout << "enter value for g: ";
    std::cin >> this->g;
  }
  ~b() {
    std::cout << "class b" << '\n';
  }
};

class p;
class d {
  friend class p;
private:
  int h = 100;
};

class p {
public:
  void change_h(d* _d) {
    _d->h += 20;
    std::cout << "h is: " << _d->h << std::endl;
  }
  void print_values(d* _d) {
    std::cout << "value of _d.h is: " << (*_d).h << std::endl;
  }
};

int sum(a first, b second) {
  return first.i + second.g;
}

int main(int argc, char const *argv[]) {
  Second _s(10);

  d _d; p _p;
  _p.change_h(&_d);
  _p.print_values(&_d);

  a first; b second;
  std::cout << "friend value is: " << sum(first, second) << std::endl;
  class _ {}; ::_ __;
  ::A a('a', 'b', 'c'); a.msg();

  const unsigned char value = 10;
  const char ch = 10;
  const char *r = "res: "; const char *s = "sin: "; const char *v = "value: ";
  std::cout << r << abs(::ch) - pow(::ch, ::value) << std::endl \
    << s << sin(::value) << std::endl \
    << v << ::value << std::endl;
  return 0;
}
