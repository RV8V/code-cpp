#include <iostream>

class Car {
public:
  Car() {
    std::cout << __FUNCTION__ << std::endl;
  }
  ~Car() {
    std::cout << __FUNCTION__ << std::endl;
  }
  void use(void) {
    std::cout << "\tcar \t-> drive" << std::endl;
  }
};

class Airplane {
public:
  Airplane() {
    std::cout << __FUNCTION__ << std::endl;
  }
  ~Airplane() {
    std::cout << __FUNCTION__ << std::endl;
  }
  void use(void) {
    std::cout << "\tairplane -> fly" << std::endl;
  }
};

class FlyingCar : public Car, public Airplane {
public:
  FlyingCar() {
    std::cout << __FUNCTION__ << std::endl;
  }
  ~FlyingCar() {
    std::cout << __FUNCTION__ << std::endl;
  }
};

int main(int, char const**) {
  FlyingCar fc;

  ((Car)fc).use();
  ((Airplane)fc).use();

  fc.Car::use();
  fc.Airplane::use();

  fc.::Car::use();
  fc.::Airplane::use();

  fc.FlyingCar::Car::use();
  fc.FlyingCar::Airplane::use();

  Car(fc).use();
  Airplane(fc).use();

  Car* p_car = (Car*)&fc;
  Airplane* p_plane = (Airplane*)&fc;
  return 0;
}
