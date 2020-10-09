#include <iostream>
#include <cstdlib>

class Test;

struct Point {
private: int m_x, m_y;
public:
  Point(): m_x{0}, m_y{0} { std::cout << "Point() constructor by default" << std::endl; };
  Point(int x, int y): m_x{x}, m_y{y} { std::cout << "Point() constructor" << std::endl; }
  Point(const Point &point) {
    std::cout << "copy constructor" << std::endl;
    this->m_x = point.m_x;
    this->m_y = point.m_y;
  }
  ~Point(void) { std::cout << "~Point() destructor" << std::endl; }
  Point& operator=(const Point &point) {
    if (this == &point) return *this;
    std::cout << "operator=" << std::endl;
    this->m_x = point.m_x;
    this->m_y = point.m_y;
    return *this;
  }
  Point operator+(const Point &point) {
    std::cout << "operator+" << std::endl;
    Point tmp{this->m_x + point.m_x, this->m_y + point.m_y};
    return tmp;
  }
  Point& operator++(void) {
    std::cout << "operator++ pre" << std::endl;
    this->m_y++; this->m_x++;
    return *this;
  }
  Point operator++(int) {
    std::cout << "operator++ post" << std::endl;
    Point tmp{*this};
    this->m_x++; this->m_y++;
    return tmp;
  }
  Point& operator--(void) {
    std::cout << "operator-- pre" << std::endl;
    this->m_y -= 1; this->m_x -= 1;
    return *this;
  }
  Point operator--(int) {
    std::cout << "operator-- post" << std::endl;
    Point tmp{*this};
    this->m_x -= 1; this->m_y -= 1;
    return tmp;
  }
  friend void change_state(Point &, Test &);
};

struct Test {
private:
  int data = 0;
  friend void change_state(Point&, Test&);
};

void change_state(Point& point, Test& test) {
  std::cout << "friend function: " << __FUNCTION__ << std::endl;
  point.m_x = rand() % 10;
  point.m_y = rand() % 10;
  test.data = 1;
}

int main(int, char const**) {
  Test test;
  Point a = {1, 2};
  change_state(a, test);
  //Point b = {3, 4};
  //a.operator=(b);
  //Point c = b;
  /*Point c = a.operator+(b);
  a.operator++(); ++a;
  b.operator++(); b++;
  a.operator--(); --a;
  b.operator--(); b--;*/
  int value = 10;
  int& ref = value;
  std::cout << "ref: " << &ref << std::endl;
  std::cout << "address: " << &value << std::endl;
  return 0;
}
