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

int main(int argc, char const *argv[]) {
  unique_ptr_b(1);
  unique_ptr_example_ab();
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
