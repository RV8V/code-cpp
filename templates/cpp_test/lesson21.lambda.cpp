#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <queue>
#include <functional>

#define CONS_TEST_A 100
#define CONS_TEST_B 50
#define CONS_TEST_A_I 0
#define CONS_TEST_B_I 5

void example_a(void);
void example_b(void);

int main(int argc, char const *argv[]) {
  example_a();
  example_b();
  return 0;
}

void example_a(void) {
  auto v_print_a = [](std::vector<int> &vi) {
    for(auto &i : vi)
      std::cout << i << ", ";
    std::cout << std::endl;
  };

  srand(time(NULL));
  constexpr unsigned size = 20;
  std::vector<int> vi;
  vi.reserve(size);
  auto v_print_b = [&, size]() {
    for(auto &i : vi)
     std::cout << i << ", ";
    std::cout << std::endl;
  };
  auto v_print_c = [=, &size]() {
    for(auto &i : vi)
     std::cout << i << ", ";
    std::cout << std::endl;
  };

  std::cout << "capacity: " << vi.capacity() << std::endl;
  for(unsigned i = 0; i < size; ++i)
    vi.push_back(rand() % 100 - 50);
  v_print_a(vi);
  std::sort(vi.begin(), vi.end()); v_print_a(vi);
  std::sort(vi.begin(), vi.end(), [](auto _, auto __) { return std::abs(_) < std::abs(__); }); v_print_c();
}

namespace cpp_ns {
  enum class actions { START = 0, STOP, MOVE, END };
  struct notifier {
    void clb_start(void) const { std::cout << "start is ok" << std::endl; }
    void clb_stop(void) const { std::cout << "stop is ok" << std::endl; }
    void clb_move(void) const { std::cout << "move is ok" << std::endl; }
  };
  void test(void) {}
};

void example_b(void) {
  std::queue<std::pair<cpp_ns::actions, std::function<void(void)>>> q;
  struct cpp_ns::notifier n;
  q.push({cpp_ns::actions::MOVE, /*cpp_ns::test*//*n.clb_move()*/[&](){ n.clb_move(); }});
  q.push({cpp_ns::actions::START, [&]{ n.clb_start(); }});
  q.push({cpp_ns::actions::STOP, [&]{ n.clb_stop(); }});
  char i = 100;
  do {
    if (rand() % CONS_TEST_A - CONS_TEST_B == CONS_TEST_B_I \
     || rand() % CONS_TEST_A - CONS_TEST_B == CONS_TEST_A_I) {
      auto a = q.front();
      a.second(); q.pop();
      return;
    }
    if (q.empty()) return;
  } while(i-- > 0);
}
