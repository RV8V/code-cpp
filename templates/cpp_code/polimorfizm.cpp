#include <iostream>

class Weapon {
public:
  virtual void shot(void) const = 0;
  void print_method(void) const {
    std::cout << __FUNCTION__ << std::endl;
  }
};

class Knife : public Weapon {
public:
  void shot(void) const override {
    std::cout << "knife" << std::endl;
  }
};

class Gun : public Weapon {
public:
  virtual void shot(void) const override {
    std::cout << "bang" << std::endl;
  }
};

class SubmachineGun : public Gun {
public:
  void shot(void) const override {
    std::cout << "bang bang bang" << std::endl;
  }
};

class Player {
public:
  void shot(Weapon* weapon) {
    weapon->shot();
  }
};

int main(int, char const**) {
  Gun gun;
  SubmachineGun submachine;
  Knife knife;
  knife.print_method();
  Weapon* p_weapon = (Weapon*)&submachine;
  p_weapon->shot();
  p_weapon = (Weapon*)&gun;
  p_weapon->shot();
  Player pl;
  pl.shot((Weapon*)&knife);
  pl.shot((Weapon*)&gun);
  return 0;
}
