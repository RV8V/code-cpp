#include <iostream>
#include <thread>
#include <chrono>
#include <functional>
#include <memory>

#define SLEEP_TIME 1000
#define CYCLE_VALUE 10
#define FIRST_SLEEP 1000
#define SECOND_SLEEP 2000
#define THIRD_SLEEP 1000

using namespace std;

void do_work_a(void);
void do_work(int&, int&);
int return_same(int);

int main(int, const char** const) {
  int a = 1, b = 2;
  //thread th(do_work, ref(a), ref(b));
  //do_work(a, b);

  int result = 1;
  thread t([&result]() {
    return result = return_same(20);
  });

  function<int()> f = [result]() mutable {
    cout << __FUNCTION__ << endl;
    return result *= 2;
  };

  for (size_t i = 0; i < 10; ++i) {
    cout << "id of thread -> "
      << this_thread::get_id()
      << " " << __FUNCTION__ << " "
      << i << endl;
    this_thread::sleep_for(chrono::milliseconds(SLEEP_TIME / 2));
  }

  t.join();
  cout << "value of a -> " << a
      << " value of b -> " << b << endl
      << "value of result -> " << result << endl;
  return 0;
}

void do_work(void) {
  int i = CYCLE_VALUE;
  do {
    cout << "id of thread -> " << this_thread::get_id() << " " << __FUNCTION__ << " " << i << endl;
    this_thread::sleep_for(chrono::milliseconds(SLEEP_TIME));
  } while (i-- > 0);
  return;
}

void do_work(int& a, int& b) {
  this_thread::sleep_for(chrono::milliseconds(FIRST_SLEEP));
  cout << "id: " << this_thread::get_id() << " " << "======\t" << __FUNCTION__ << " STARTED" << "\t\t======" << endl;
  this_thread::sleep_for(chrono::milliseconds(SECOND_SLEEP));
  a *= FIRST_SLEEP, b *= SECOND_SLEEP;
  this_thread::sleep_for(chrono::milliseconds(THIRD_SLEEP));
  cout << "id: " << this_thread::get_id() << " " << "======\t" << __FUNCTION__ << " STOPPED" << "\t\t======" << endl;
  return;
}

int return_same(int a) {
  this_thread::sleep_for(chrono::milliseconds(200));
  cout << "in thread" << endl;
  return a;
}
