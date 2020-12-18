#include <iostream>

template<class T, std::size_t size>
struct array {
  T m_arr[size];
  T& operator[](std::size_t index) { return (*this).m_arr[index]; }
  // const T operator[](std::size index) const { return (*this).m_arr[index]; }
  // T* operator+(T a, T b) { return a + b; }
  T* data() { return (*this).m_arr; }
  const T* data() const { return (*this).m_arr; }
  std::size_t size_arr() { return size; }
};

int main(int argc, char const *argv[]) {
  array<char, 2> ch_a = array<char, 2>{(char)'a', (char)'a'};
  array<int, 2> i_a = {1, 2};
  ch_a[0] = (char)10;
  const int size = (int)ch_a.size_arr();
  std::cout << size << '\n';

  return 0;
}
