#include <iostream>
#include <string>
#include <cstring>
#include <memory>
#include <vector>

namespace tmp_object {
  const char* f_a(std::string& s1, std::string& s2) {
    return (s1 + s2).c_str();
  }
  void f_b(std::string& s1, std::string& s2, std::string& s3) {
    const char* cs = (s1 + s2).c_str();
    std::cout << "address cs -> " << cs << std::endl;
    const char* pcs {(s1 + s2).c_str()};
    std::cout << "address pcs -> " << pcs << std::endl;
    if (*(cs + 0) == '1') std::cout << "found" << std::endl;
    if (strlen(cs = (s2 + s3).c_str()) < 8 && *(cs + 0) == '1') std::cout << "ok" << std::endl;
  }
  void test(void) {
    std::string s1{"1"}; std::string s2{"2"}; std::string s3{"3"};
    std::cout << f_a(s1, s2) << std::endl;
    f_b(s1, s2, s3);
  }
};

int main(int argc, char const *argv[]) {
  tmp_object::test();
  return 0;
}
