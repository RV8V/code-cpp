#include "overload.test.h"

/*
 * overload of 49 operators
*/

int main(int, const char**) {
  vector_ov v1(10, 20, 30), v2;
  v2.operator=(v1);
  v2.operator--().operator++();

  return EXIT_SUCCESS;
}

vector_ov::vector_ov(void) {};
vector_ov::vector_ov(int x, int y, int z): x(x), y(y), z(z) {};

vector_ov vector_ov::operator=(const vector_ov& v1) {
  return vector_ov(this->x = v1.x, this->y = v1.y, this->z = v1.z);
};

vector_ov vector_ov::operator++(void) {
  return vector_ov(++this->x, ++this->y, ++this->z);
};

vector_ov vector_ov::operator++(int) {
  return vector_ov(this->x++, this->y++, this->z++);
};

vector_ov operator+(const vector_ov& v1, const vector_ov& v2) {
  return vector_ov(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
};

vector_ov vector_ov::operator--(void) {
  return vector_ov(--this->x, --this->y, --this->z);
};

vector_ov vector_ov::operator--(int) {
  return vector_ov(this->x--, this->y--, this->z--);
};

vector_ov operator-(const vector_ov& v1, const vector_ov& v2) {
  return vector_ov(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
};

vector_ov operator*(const vector_ov& v1, const vector_ov& v2) {
  return vector_ov(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z);
};

vector_ov operator/(const vector_ov& v1, const vector_ov& v2) {
  return vector_ov(v1.x / v2.x, v1.y / v2.y, v1.z / v2.z);
};

vector_ov operator*(vector_ov& v1, int i) {
  return vector_ov(v1.x * i, v1.y * i, v1.z * i);
};

vector_ov operator/(vector_ov& v1, int i) {
  return vector_ov(v1.x / i, v1.y / i, v1.z / i);
};

vector_ov operator%(vector_ov& v1, int i) {
  return vector_ov(v1.x % i, v1.y % i, v1.z % i);
};

vector_ov operator%(const vector_ov& v1, const vector_ov& v2) {
  return vector_ov(v1.x % v2.x, v1.y % v2.y, v1.z % v2.z);
};

vector_ov operator+=(vector_ov& v1, vector_ov& v2) {
  return vector_ov(v1 = v1 + v2);
};

vector_ov operator-=(vector_ov& v1, vector_ov& v2) {
  return vector_ov(v1 = v1 - v2);
};

vector_ov operator*=(vector_ov& v1, vector_ov& v2) {
  return vector_ov(v1 = v1 * v2);
};

vector_ov operator/=(vector_ov& v1, vector_ov& v2) {
  return vector_ov(v1 = v1 / v2);
};

vector_ov operator%=(vector_ov& v1, vector_ov& v2) {
  return vector_ov(v1 = v1 % v2);
};

const bool operator==(const vector_ov& v1, const vector_ov& v2) {
  return v1.x == v2.x && v1.y == v2.y && v1.z == v2.z;
};

const bool operator!=(const vector_ov& v1, const vector_ov& v2) {
  return !operator==(v1, v2);
};

vector_ov::operator bool() {
  if (*this != vector_ov(0, 0, 0))
    return true;
  return false;
}

/*...*/
