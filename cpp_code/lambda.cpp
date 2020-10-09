#include <iostream>
#include <functional>
#include <vector>

using namespace std;

void test_fn(vector<int> &v, function<void(int)> f) {
  for (auto el : v)
    f(el);
}

int main() {
  /*vector<int> v = { 1, 2, 3 };
  function<void(int)> f;
  f = [](int a) -> void
  {
    cout << "a: " << a << '\n';
  };

  test_fn(v, f);

  test_fn(v, [](int a) -> void {
    cout << "lamble: " << a << '\n';
  });*/

  int a = 0;
  int b = 10;

  auto f = [=]() mutable -> void {
    a = 2;
    b = 3;
  };

  cout << a << " " << b << '\n';

  return 0;
}
