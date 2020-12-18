#include <iostream>

class I_Bicycle {
public:
  void virtual twist_the_wheels(void) const = 0;
  void virtual ride(void) const = 0;
};

class Simple_bicycle : public I_Bicycle {
public:
  void twist_the_wheels(void) const override {
    std::cout << "Simple_bicycle -> twist_the_wheels" << std::endl;
  }
  void ride(void) const override {
    std::cout << "Simple_bicycle -> ride" << std::endl;
  }
};

class Human {
public:
  void ride_on(I_Bicycle* some_erunda) {
    std::cout << "turn the steering wheel: " << std::endl;
    some_erunda->twist_the_wheels();
    std::cout << "go!: " << std::endl;
    some_erunda->ride();
  }
};

int main(int, char const**) {
  Human h;
  Simple_bicycle sm;
  h.ride_on(&sm);
  return 0;
}
