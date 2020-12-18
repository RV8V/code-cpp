#include <iostream>
#include <fstream>

class Point {
private:
  int x, y;
public:
  Point(void) {
    this->x = this->y = 0;
  }
  Point(int x, int y) {
    this->x = x;
    this->y = y;
  }
  friend std::ostream& operator<<(std::ostream &, const Point &);
};

std::ostream& operator<<(std::ostream &os, const Point &p) {
  os << "[" << p.x << ", " << p.y << "]";
  return os;
}

int main(int, char const**) {
  Point p(10, 20);
  operator<<(std::cout, p);
  std::cout << std::endl << p << std::endl;
  return 0;
}
