#include <iostream>

class A {
private:
  std::string message{"no message"};
public:
  A() { std::cout << "A()" << '\n'; }
  A(std::string mes) { this->message = mes; }
  ~A() { std::cout << "~A()" << '\n'; }
  void print_message() {
    std::cout << "message: " << this->message << '\n';
  }
};

class B : public A {
public:
  B(std::string message): A(message) { std::cout << "B()" << '\n'; }
  ~B() { std::cout << "~B()" << '\n'; }
};

int main(int, char const**) {
  B b("123");
  b.print_message();
  return 0;
}
