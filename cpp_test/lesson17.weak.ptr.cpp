#include <iostream>
#include <memory>

void weak_ptr_example_a(void);
void weak_ptr_example_b(void);
void weak_ptr_example_c(void);
void weak_ptr_example_d(void);

int main(int argc, char const *argv[]) {
  weak_ptr_example_d();
  return 0;
}

void weak_ptr_example_a(void) {
  struct Unit {
    Unit(std::string name) { std::cout << "Unit() with params is called" << std::endl; }
    Unit() { std::cout << "Unit() constructor is called" << std::endl; };
    ~Unit() { std::cout << "~Unit() destructor is called" << std::endl; };
    std::shared_ptr<Unit> target;
  };
  {
    std::shared_ptr<Unit> archer = std::make_shared<Unit>("archer");
    std::shared_ptr<Unit> pickeman = std::shared_ptr<Unit>{new Unit{"pickeman"}};
    archer->target = pickeman; /*pickeman shot into target for archer*/

    std::cout << "archer.use_count() -> " << archer.use_count() << ": " << archer->target.use_count() << std::endl;
    std::cout << "pickeman.use_count() -> " << pickeman.use_count() << ": " << pickeman->target.use_count() << std::endl;
  }
  std::cout << std::endl << std::endl;
}

void weak_ptr_example_b(void) {
  struct Unit {
    Unit(std::string name) { std::cout << "Unit() with params is called" << std::endl; }
    Unit() { std::cout << "Unit() constructor is called" << std::endl; };
    ~Unit() { std::cout << "~Unit() destructor is called" << std::endl; };
    std::shared_ptr<Unit> target;
  };
  {
    std::shared_ptr<Unit> archer = std::shared_ptr<Unit>{new Unit{"archer"}};
    std::shared_ptr<Unit> pickeman = std::shared_ptr<Unit>{new Unit{"pickeman"}};

    std::cout << "archer.use_count() -> " << archer.use_count() << ": " << archer->target.use_count() << std::endl;
    std::cout << "pickeman.use_count() -> " << pickeman.use_count() << ": " << pickeman->target.use_count() << std::endl;
    archer->target = pickeman; /*pickeman shot into target for archer*/

    std::cout << "archer.use_count() -> " << archer.use_count() << ": " << archer->target.use_count() << std::endl;
    std::cout << "pickeman.use_count() -> " << pickeman.use_count() << ": " << pickeman->target.use_count() << std::endl;
    pickeman->target = archer;

    std::cout << "archer.use_count() -> " << archer.use_count() << ": " << archer->target.use_count() << std::endl;
    std::cout << "pickeman.use_count() -> " << pickeman.use_count() << ": " << pickeman->target.use_count() << std::endl;
  }
  std::cout << std::endl << "1 -> 2 and 2 -> 1 => no call for its destructors" << std::endl;
}

void weak_ptr_example_c(void) {
  struct Unit {
    Unit(std::string name) { std::cout << "Unit() with params is called" << std::endl; }
    Unit() { std::cout << "Unit() constructor is called" << std::endl; };
    ~Unit() { std::cout << "~Unit() destructor is called" << std::endl; };
    std::shared_ptr/*weak_ptr*/<Unit> target;
  };
  {
    std::shared_ptr<Unit> archer = std::make_shared<Unit>("archer");
    std::shared_ptr<Unit> &some = archer;
    archer->target = some;
  }
  std::cout << std::endl << std::endl;
}

void weak_ptr_example_d(void) {
  struct Unit {
    Unit(std::string name) { std::cout << "Unit()" << std::endl; }
    ~Unit() { std::cout << "~Unit()" << std::endl; };

    void attack() {
      if (!this->target.expired())
        if (this->target.lock()->health < 0)
          this->target.reset();
    }

    int health{100};
    std::weak_ptr/*shared_ptr*/<Unit> target;
  };
  {
    std::shared_ptr<Unit> archer = std::make_shared<Unit>("archer");
    std::shared_ptr<Unit> pickeman = std::make_shared<Unit>("pickeman");
    archer->target = pickeman;
    pickeman.reset();
    archer->attack();
  }
  std::cout << std::endl << std::endl;
}
