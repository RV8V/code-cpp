#include <iostream>
#include <vector>

int main(int argc, char const *argv[]) {
  std::vector<int> vi_a;
  std::vector<size_t> vi_b = { 1, 2, 3, 4 };
  for(auto i : vi_b)
    std::cout << i << std::endl;
  std::cout << "capacity: " << vi_b.capacity() << std::endl;
  char i = 0;
  do vi_b.push_back(size_t((size_t)i / 2.)); while(i++ < 10);
  std::cout << "capacity: " << vi_b.capacity() << std::endl;
  i = 10; vi_a.reserve(100);
  std::cout << "value: " << i << std::endl;
  do vi_a.push_back(i / 2.); while(i-- > 0);
  i = 10;
  do std::cout << vi_a.at(i) << std::endl; while(i-- > 0);
  std::cout << "capacity: " << vi_a.capacity() << std::endl;
  return 0;
}
