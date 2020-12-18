#include <iostream>

enum color { RED, GREEN, BLUE, SOME };
enum class tank_direction { UP, DOWN, RIGHT, LEFT };
enum color operator++(enum color &r_o) {
  r_o = r_o == SOME ? RED : color(int(r_o) + 1);
};
enum tank_direction operator++(enum tank_direction &r_t) {
  r_t = r_t == tank_direction::DOWN ? tank_direction::UP : tank_direction(int(r_t) + 1);
};

int main(int argc, char const *argv[]) {
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
  return 0;
}
