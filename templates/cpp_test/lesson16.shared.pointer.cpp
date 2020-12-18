#include <iostream>
#include <memory>

void shared_ptr_example_a(void);
void shared_ptr_example_a(int);
void shared_ptr_example_test1(std::shared_ptr<int>);
void shared_ptr_example_test2(std::shared_ptr<int> &);
void shared_ptr_example_test_test(void);
void shared_ptr_example_arr(void);
void shared_ptr_example_last(void);

int main(int argc, char const *argv[]) {
  shared_ptr_example_a(1);
  shared_ptr_example_test_test();
  shared_ptr_example_arr();
  return 0;
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
