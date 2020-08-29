#include <iostream>

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
