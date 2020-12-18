#include <iostream>
#include <fstream>

int main(int argc, char const *argv[]) {
  std::ofstream w_file;
  w_file.open("test.txt", std::ios_base::out);
  if (w_file.is_open()) {
    w_file << "hello word" << std::endl;
    w_file.close();
  } else std::cout << "err while opening file" << '\n';

  char text[50];
  std::ifstream r_file;
  r_file.open("test.txt", std::ios_base::in);
  if (r_file.is_open())
    std::cout << "file is not found" << '\n';
  else {
    r_file >> text;
    std::cout << text << '\n';
    r_file.getline(text, 50);
    std::cout << text << '\n';
    r_file.close();
  }
  return 0;
}
