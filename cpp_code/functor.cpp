#include <iostream>

using namespace std;

class my_functor {
public:
  void operator()() {
    cout << "I am functor" << '\n';
  }
};

int main() {
  my_functor f;
  f.operator()();
  f();
  return 0;
}
