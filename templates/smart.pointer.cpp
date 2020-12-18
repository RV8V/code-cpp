#include <iostream>
#include <memory>

int foo_a(int);
void unique_ptr_a(void);
void unique_ptr_a(int);
void unique_ptr_a(char);
void unique_ptr_a(unsigned);
void unique_ptr_b(int);
void unique_ptr_b(char);
void unique_ptr_example_a(std::unique_ptr<int>);
void unique_ptr_example_b(std::unique_ptr<int> &);
void unique_ptr_example_ab(void);

void shared_ptr_example_a(void);
void shared_ptr_example_a(int);
void shared_ptr_example_test1(std::shared_ptr<int>);
void shared_ptr_example_test2(std::shared_ptr<int> &);
void shared_ptr_example_test_test(void);
void shared_ptr_example_arr(void);
void shared_ptr_example_last(void);

void weak_ptr_example_a(void);
void weak_ptr_example_b(void);
void weak_ptr_example_c(void);
void weak_ptr_example_d(void);

int main(int argc, char const *argv[]) {
  unique_ptr_b(1);
  unique_ptr_example_ab();
  shared_ptr_example_a(1);
  shared_ptr_example_test_test();
  shared_ptr_example_arr();
  weak_ptr_example_a()
  weak_ptr_example_b()
  weak_ptr_example_c()
  weak_ptr_example_d()
  return 0;
}

int foo_a(int i) {
  int res = 0;
  int* p = new int{i};
  if (i > 100) return res;
  for (int j = 0; j < i; j++)
    if (1) return res;
  delete p;
  return res;
}

void unique_ptr_a(void) {
  auto* p_i = new int{20};
  std::cout << "size: " << sizeof(p_i) << std::endl << "address: " << p_i << std::endl << "value: " << *p_i << std::endl;
  auto u_p_i = std::unique_ptr<int>(new int{20});
  std::cout << "size: " << sizeof(u_p_i) << std::endl << "address: " << u_p_i.get() << std::endl << "value: " << *(u_p_i.get()) << std::endl;
}

void unique_ptr_a(int) {
  struct cls {
    int a, b, c;
    cls() { std::cout << "cls()" << std::endl; };
    ~cls() { std::cout << "~cls(), no need to free memory via pointer" << std::endl; };
  };
  auto p_ucls = std::unique_ptr<cls>(new cls);
  std::cout << "size: " << sizeof(p_ucls) << std::endl << "address: " << p_ucls.get() << std::endl << "value a: " << (*p_ucls).a << std::endl;
}

void unique_ptr_a(char) {
  struct cls {
    int a{10}, b{1}, c{2};
    cls() { std::cout << "cls() -> crash here" << std::endl; };
    ~cls() { std::cout << "~cls(), no need to free memory via pointer" << std::endl; };
  };
  auto p_ucls = std::make_unique<cls>();
  std::cout << "size: " << sizeof(p_ucls) << std::endl << "address: " << p_ucls.get() << std::endl << "value a: " << p_ucls->a << std::endl;
}

void unique_ptr_a(unsigned) {
  auto* p_ch = new char{10};
  {
    auto ch_u = std::unique_ptr<char>{p_ch};
  }
  delete p_ch;
}

void unique_ptr_a(double) {
  auto* p_ch = new short{10};
  {
    auto u_i = std::unique_ptr<int>{new int(*(int*)(p_ch))};
  }
  delete p_ch;
}

void unique_ptr_b(int) {
  auto up_a = std::unique_ptr<int>{new int{20}};
  // auto up_i = std::unique_ptr<int>{up_a}; -> compilation error
  auto up_b = std::unique_ptr<int>{up_a.release()};
  std::cout << (up_a ? "pointer in not null" : "pointer is null (nullptr)") << std::endl;
  std::cout << (up_b ? "pointer in not null" : "pointer is null (nullptr)") << std::endl;
  char* ch_p = (char*)up_b.release();
  std::cout << (up_b ? "pointer in not null" : "pointer is null (nullptr)") << std::endl;
  delete ch_p;
}

void unique_ptr_b(char) {
  struct cls {
    int a{10}, b{1}, c{2};
    cls() { std::cout << "cls() -> crash here" << std::endl; };
    ~cls() { std::cout << "~cls(), no need to free memory via pointer" << std::endl; };
  };
  auto p_a = std::make_unique<cls>();
  p_a.reset();
  std::unique_ptr<cls> p_b = std::make_unique<cls>();
  std::unique_ptr<cls> p_c;
  // p_c.reset(p_b.get()); -> compilation error
  p_c.reset(p_b.release());

  std::unique_ptr<cls> p_d_call_dest = std::make_unique<cls>();
  p_d_call_dest = nullptr;
}

void unique_ptr_example_a(std::unique_ptr<int> u_i) {
  (*u_i) = 100;
}

void unique_ptr_example_b(std::unique_ptr<int> &u_i) {
  (*u_i) = 100;
}

void unique_ptr_example_ab(void) {
  std::unique_ptr<int> ap(new int(1));
  std::cout << ap.get() << std::endl;
  // unique_ptr_example_a(ap); -> copy constructor is called
  unique_ptr_example_b(move(ap));
  unique_ptr_example_b(&ap);
}

void shared_ptr_example_a(void) {
  std::shared_ptr<int> sp_a(new int{1});
  {
    std::shared_ptr<int> sp_b;
    sp_b = sp_a;
  }
  std::shared_ptr<int> sp_c = sp_a;
}

void shared_ptr_example_a(int) {
  struct cls {
    cls() { std::cout << "cls() constructor is called" << std::endl; };
    ~cls() { std::cout << "~cls() destructor is called" << std::endl; };
  };
  std::shared_ptr<cls> a{new cls};
  std::shared_ptr<cls> b{new cls};
  std::shared_ptr<cls> c{b};
  std::cout << "a.get() -> " << a.get() << ": " << a.use_count() << std::endl;
  std::cout << "b.get() -> " << b.get() << ": " << b.use_count() << std::endl;
  std::cout << "c.get() -> " << c.get() << ": " << c.use_count() << std::endl;
  a = b; b = c;
  std::cout << "a.get() -> " << a.get() << ": " << a.use_count() << std::endl;
  std::cout << "b.get() -> " << b.get() << ": " << b.use_count() << std::endl;
  std::cout << "c.get() -> " << c.get() << ": " << c.use_count() << std::endl;
}

void shared_ptr_example_test_test(void) {
  auto sp = std::make_shared<int>(1);
  shared_ptr_example_test1(sp);
  shared_ptr_example_test2(sp);
  std::cout << "shared_ptr_example_test_test (owners) = " << sp.use_count() << std::endl;
}

void shared_ptr_example_test1(std::shared_ptr<int> ptr) {
  std::cout << "shared_ptr_example_test (value -> copy constructor) = " << ptr.use_count() << std::endl;
}

void shared_ptr_example_test2(std::shared_ptr<int> &ptr) {
  std::cout << "shared_ptr_example_test (address) = " << ptr.use_count() << std::endl;
}

void shared_ptr_example_arr(void) {
  {
    auto spa = std::shared_ptr<int>{new int[3]}; /*delete but not delete[] -> memory leak*/
    // auto spa_v = std::shared_ptr<std::vector<int>>{};
  }
  auto spa_a = std::shared_ptr<int>{new int[3], std::default_delete<int[]>()};
  int i = 0;
  do *(spa_a.get() + i) = i; while(i++ < 3); i = 3;
  do std::cout << "currect value -> " << *(spa_a.get() + i) << std::endl; while(i-- > 0);
  {
    auto spa = std::shared_ptr<int>{new int[3], [](int* p) {delete[] p;}};
  }
  {
    struct IntArrayDeleter {
      void operator()(int* ap) {
        std::cout << "deleted is ok" << std::endl;
        delete[] ap;
      }
    };
    auto spa = std::shared_ptr<int>{new int[3], IntArrayDeleter()};
  }
}

void shared_ptr_example_last(void) {
  struct cls {
    cls() { std::cout << "cls() constructor is called" << std::endl; };
    ~cls() { std::cout << "~cls() destructor is called" << std::endl; };
    static std::shared_ptr<cls> make_shared_array(unsigned size) {
      return std::shared_ptr<cls>{new cls[size], std::default_delete<cls[]>()};
    }
  };
  {
    auto spa = cls::make_shared_array(3);
  }
  {
    auto spa_b = std::shared_ptr<cls>{new cls[5]}; /*crash because of attempt to free memory*/
  }
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
