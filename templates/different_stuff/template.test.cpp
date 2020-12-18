#include <iostream>
#include <string>
#include <cstring>
#include <memory>
#include <vector>

enum { O = 1, T, TH };
enum { ARR_LENGTH = 3 };

void print_i_arr(const int *);
void print_ch_arr(const char *);

template <typename T, typename O>
O print_arr(const T *arr, const O o) {
  char i = sizeof(arr)/sizeof(T);
  do std::cout << *(arr + i) << std::endl;
  while(i-- > 0);
  return o;
}

template<class Typename>
class Arr {
private:
  Typename arr[ARR_LENGTH];
public:
  Arr(Typename *a) {
    for (unsigned i = 0; i < ARR_LENGTH; i++)
      std::cout << "current element: " << *(a + i) << std::endl;
  }
  Typename get_element(int i) {
    return *(this->arr + i);
  }
};

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
  unsigned arr_u[] = { 10, 12, 15 };
  Arr<unsigned> obj_u(arr_u);
  std::cout << obj_u.get_element(1) << std::endl << std::endl;

  int arr_i[] = { 10, 12, 15 };
  Arr<int> obj_i(arr_i);
  std::cout << obj_i.get_element(1) << std::endl << std::endl;

  const int i_arr[TH] = { O, T, TH };
  const char ch_arr[TH] = { 'a', 'b', 'c' };
  print_i_arr(i_arr);
  print_ch_arr(ch_arr);
  const int o_1 = print_arr<int, int>(i_arr, TH);
  const char o_2 = print_arr<char, char>(ch_arr, *ch_arr);
  return 0;
}

void print_i_arr(const int *i_arr) {
  for (int i = 0; i < sizeof(i_arr)/sizeof(int); i++)
    std::cout << "value (int): " << *(i_arr + i) << '\n';
}

void print_ch_arr(const char *ch_arr) {
  for (int i = 0; i < sizeof(ch_arr)/sizeof(char); i++)
    std::cout << "value (char): " << *(ch_arr + i) << '\n';
}
