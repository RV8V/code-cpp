#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <cmath>

void foo(int) { std::cout << "int" << std::endl; }
void foo(float) { std::cout << "float" << std::endl; }
void foo(double) { std::cout << "double" << std::endl; }
void foo(int i_a = 0xaf12, int i_b = 0xaa13, int i_c = 0xba10) {}
void foo(char) = delete;
void foo(std::string) = delete;
void f_cpp_un(...) {}
void f_cpp(int *p) { srand(time(NULL)); *p = (rand() % 10) + 1; }
void f_cpp(int &a) { srand(time(NULL)); a = (rand() % 10) + 1; }

#define C_PI 3.14138731
constexpr double CPP_PI = 3.14138731;
constexpr double CPP_PI_E = CPP_PI / 2.;
const double e_i = 0.;
constexpr double ext = ((((const double)exp(e_i) / 0.789651) / exp(e_i * 12.21)) * 3.1931636689) / \
         (((exp(e_i / 2914.124) * e_i) / exp(e_i / 56.9137)) * exp(e_i * 139.91470));
constexpr double f_expr() { return exp((CPP_PI * 10.9) / 21.13); }

enum color { RED, GREEN, BLUE, SOME };
enum class tank_direction { UP, DOWN, RIGHT, LEFT };
enum color operator++(enum color &r_o) {
  r_o = r_o == SOME ? RED : color(int(r_o) + 1);
};
enum tank_direction operator++(enum tank_direction &r_t) {
  r_t = r_t == tank_direction::DOWN ? tank_direction::UP : tank_direction(int(r_t) + 1);
};

enum error_file_c { EFE_UNKNOWN = 0, EFE_NO, EFE_OPEN, CLOSE, EFE_CRASH };
enum error_network_c { ENE_UNKNOWN = 0, ENE_NO, OPEN, ENE_CLOSE, ENE_LOST, ENE_CRASH };
namespace f_ns { int flag = 0; enum error_file_c : unsigned short int { UNKNOWN = 0, NO, OPEN, CLOSE, CRASH }; };
namespace n_ns { void ns_test(...) { std::cout << "this file: ns" << std::endl; }; enum error_network_c : unsigned char { UNKNOWN = 0, NO, OPEN, CLOSE, LOST, CRASH }; };
enum class error_file_f_s : unsigned char { UNKNOWN = 0, NO, OPEN, CLOSE, CRASH = 255 };
enum class error_network_n_s : char { UNKNOWN = 0, NO, OPEN, CLOSE, CRASH = 127 };

int input_i_value() {
  int i_value = 0;
  for(;;) {
    std::cin >> i_value;
    if (std::cin.fail() && !(std::cin.eof() || std::cin.bad())) {
      std::cin.clear();
      std::cin.ignore(numeric_limits<std::streamsize>::std::max(), std::endl);
      std::cout << "input error" << std::endl;
    } else break;
  }
  return i_value;
}

int main(int argc, char const **argv) {
  input_i_value();
  auto un = 0; int i = 256;
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

  {
    enum color color_a{RED};
    enum color color_b(RED);
    enum color color_c = RED;
    enum color color_d = color{RED};
    enum color color_e = color(RED);
    unsigned i = color_a; i = RED;
    color_a = (enum color)i;
    color_a = color(i);
    const unsigned h = (unsigned)++color_a;
    const unsigned g = (unsigned)++color_a;
    std::cout << h << " " << g << std::endl;
  }
  {
    tank_direction et_dir_a{tank_direction::UP};
    tank_direction et_dir_b(tank_direction::DOWN);
    tank_direction et_dir_c = tank_direction(tank_direction::RIGHT);
    tank_direction et_dir_d = tank_direction{tank_direction::LEFT};
    unsigned i = 0;
    i = int(tank_direction::UP);
    i = (int)(tank_direction::RIGHT);
    et_dir_a = tank_direction(i);
    const unsigned h = (unsigned)++et_dir_a;
    const unsigned g = (unsigned)++et_dir_a;
    std::cout << h << " " << g << std::endl;
  }

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
