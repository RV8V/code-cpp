#ifndef _OVERLOAD_TEST_
#define _OVERLOAD_TEST_

#include <iostream>
#include <istream>
#include <ostream>

using namespace std;

struct vector_ov {
  int x, y, z;
  vector_ov(void);
  vector_ov(int, int, int);

  vector_ov operator=(const vector_ov&);
  friend vector_ov operator+(const vector_ov&, const vector_ov&);
  friend vector_ov operator-(const vector_ov&, const vector_ov&);
  friend vector_ov operator*(const vector_ov&, const vector_ov&);
  friend vector_ov operator/(const vector_ov&, const vector_ov&);
  friend vector_ov operator%(const vector_ov&, const vector_ov&);

  vector_ov operator++(void);
  vector_ov operator++(int);
  vector_ov operator--(void);
  vector_ov operator--(int);

  friend vector_ov operator*(vector_ov&, int);
  friend vector_ov operator/(vector_ov&, int);
  friend vector_ov operator%(vector_ov&, int);

  friend vector_ov operator+(vector_ov&);
  friend vector_ov operator-(vector_ov&);

  friend vector_ov operator+=(vector_ov&, vector_ov&);
  friend vector_ov operator-=(vector_ov&, vector_ov&);
  friend vector_ov operator*=(vector_ov&, vector_ov&);
  friend vector_ov operator/=(vector_ov&, vector_ov&);
  friend vector_ov operator%=(vector_ov&, vector_ov&);

  friend const bool operator<(const vector_ov&, const vector_ov&);
  friend const bool operator>(const vector_ov&, const vector_ov&);
  friend const bool operator<=(const vector_ov&, const vector_ov&);
  friend const bool operator>=(const vector_ov&, const vector_ov&);
  friend const bool operator==(const vector_ov&, const vector_ov&);
  friend const bool operator!=(const vector_ov&, const vector_ov&);

  operator bool();
  operator int();

  friend const bool operator!(vector_ov&);
  friend const bool operator&&(vector_ov&, vector_ov&);
  friend const bool operator||(vector_ov&, vector_ov&);

  friend const vector_ov operator~(vector_ov&);
  friend const vector_ov operator&(vector_ov&, vector_ov&);
  friend const vector_ov operator^(vector_ov&, vector_ov&);
  friend const vector_ov operator|(vector_ov&, vector_ov&);

  friend ostream& operator<<(ostream&, vector_ov&);
  friend istream& operator>>(istream&, vector_ov&);

  friend vector_ov operator&=(vector_ov&, vector_ov&);
  friend vector_ov operator^=(vector_ov&, vector_ov&);
  friend vector_ov operator|=(vector_ov&, vector_ov&);

  friend ostream& operator<<=(ostream&, vector_ov&);
  friend istream& operator>>=(istream&, vector_ov&);

  int operator[](int);

  void* operator new(size_t);
  void* operator new[](size_t);
  void operator delete(void*);
  void operator delete[](void*);

  int operator()(int);
  vector_ov operator()(vector_ov&, vector_ov&);
  friend const vector_ov operator,(vector_ov&, vector_ov&);
};

#endif
