#include <iostream>
#include <string>

class Apple;
class Human {
public:
  void take_apple(Apple& apple);
};

class Apple {
public:
  Apple(int weight, std::string color) {
    this->weight = weight;
    this->color = color;
    this->id = this->count++;
  };
  static int get_count() {
    return Apple::count;
  }
  static void change_color(Apple* apple, std::string color) {
    apple->color = color;
  }
  friend void Human::take_apple(Apple&);
private:
  static int count;
  int weight, id;
  std::string color;
};

int Apple::count = 0;

int main(int, char const**) {
  Apple apple_a(100, "red");
  Apple apple_b(120, "green");
  std::cout << "count: " << Apple::get_count() << std::endl;
  std::cout << "count: " << apple_a.get_count() << std::endl;
  Apple::change_color(&apple_a, "green");
  apple_a.change_color(&apple_a, "red");
  return 0;
}

void Human::take_apple(Apple& apple) {
  std::cout << __FUNCTION__ << std::endl << "weight: " << apple.weight << std::endl << "color: " << apple.color << std::endl;
}
