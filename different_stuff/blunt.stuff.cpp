#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

void foo(int) { std::cout << "int" << std::endl; }
void foo(float) { std::cout << "float" << std::endl; }
void foo(double) { std::cout << "double" << std::endl; }
void foo(int i_a = 0xaf12, int i_b = 0xaa13, int i_c = 0xba10) {}
void foo(char) = delete;
void foo(std::string) = delete;
void f_cpp_un(...) {}
void f_cpp(int *p) { srand(time(NULL)); *p = (rand() % 10) + 1; }
void f_cpp(int &a) { srand(time(NULL)); a = (rand() % 10) + 1; }

enum error_file_c { EFE_UNKNOWN = 0, EFE_NO, EFE_OPEN, CLOSE, EFE_CRASH };
enum error_network_c { ENE_UNKNOWN = 0, ENE_NO, OPEN, ENE_CLOSE, ENE_LOST, ENE_CRASH };
namespace f_ns { int flag = 0; enum error_file_c : unsigned short int { UNKNOWN = 0, NO, OPEN, CLOSE, CRASH }; };
namespace n_ns { void ns_test(...) { std::cout << "this file: ns" << std::endl; }; enum error_network_c : unsigned char { UNKNOWN = 0, NO, OPEN, CLOSE, LOST, CRASH }; };
enum class error_file_f_s : unsigned char { UNKNOWN = 0, NO, OPEN, CLOSE, CRASH = 255 };
enum class error_network_n_s : char { UNKNOWN = 0, NO, OPEN, CLOSE, CRASH = 127 };

int main(int argc, char const **argv) {
  auto un = 0;
  int i = 256;
  // char ch {i}, ch_i = i;
  // auto un_ch = ch;
  foo(10, 0); foo(.0f); foo(0.12); // foo(ch);
  f_cpp(&i); f_cpp(i);
  int &r_i = i;
  int* p_i = &i;
  r_i = 100; *p_i = 100;
  std::cout << "address &i: " << std::hex << &i << std::endl;
  std::cout << "address &r_i: " << std::hex << &r_i << std::endl;

  enum error_file_c e_f = EFE_UNKNOWN;
  enum error_network_c e_n = ENE_UNKNOWN;
  f_ns::error_file_c n_e_f_a = f_ns::UNKNOWN;
  n_ns::error_network_c n_n_f_a = n_ns::UNKNOWN;
  error_file_f_s n_e_f_b = error_file_f_s::UNKNOWN;
  error_network_n_s n_n_f_b = error_network_n_s::UNKNOWN;

  using namespace f_ns; flag = 1;
  using namespace n_ns; ns_test(&i, r_i);

  std::cout << std::dec;

  unsigned char x = 0, arr_l[5];
  do arr_l[x] = rand() % 10; while(i++ < sizeof(arr_l)/sizeof(unsigned char));
  for (auto x : arr_l) std::cout << "current value is: " << x << std::endl;

  std::vector<int> vi; i = 0;
  do vi.push_back(i); while(i++ < 3);
  for (auto i : vi) std::cout << i << ", "; std::cout << std::endl;
  for (unsigned i = 0; i < vi.size(); i++) std::cout << vi.at(i) << ", "; std::cout << std::endl;

  return 0;
}
