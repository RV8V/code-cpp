#include <iostream>
#include <vector>
#include <functional>

typedef std::vector<int> int_vector;
using ivector = std::vector<int>;

using namespace std;

template<typename T>
void print_v(const std::vector<T> &v) {
  for (auto it = v.begin(); it != v.cend(); ++it)
    cout << "current value is " << *it << '\n';
}

void test_fn(void) { cout << __FUNCTION__ << '\n'; };
void test_int(int el) { cout << "current element is " << el << '\n'; }

void do_smth(vector<int> &v, function<void(int)> f) {
  for (auto el : v)
    f(el);
}

int main() {
  vector<int> v = { 4, 2, 9 };
  do_smth(v, test_int);

  function<void(void)> f = test_fn;
  //f();

  int_vector iv;
  ivector i_v;
  //vector<int> v{1, 2 ,3};
  //vector<int>::iterator it = v.begin();
  //cout << "size: " << v.size() << endl;
  //print_v(v);

  int arr[] = { 1, 2 };
  /*for each (int i in arr) {
    cout << "element: " << i << '\n';
  }*/
  for (const int &el : arr)
    cout << "element: " << el << '\n';
  return 0;
}
