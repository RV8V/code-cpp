#include <iostream>
#include <thread>
#include <chrono>

#define SLEEP_TIME 1000
#define CYCLE_VALUE 10
#define FIRST_SLEEP 1000
#define SECOND_SLEEP 2000
#define THIRD_SLEEP 1000

using namespace std;

void do_work_a(void);
void do_work(int&, int&);

int main(int, const char** const) {
  int a = 1, b = 2;
  thread th(do_work, ref(a), ref(b));
  do_work(a, b);

  for (size_t i = 0; true; ++i) {
    cout << "id of thread -> "
      << this_thread::get_id()
      << " " << __FUNCTION__ << " "
      << i << endl;
    this_thread::sleep_for(chrono::milliseconds(SLEEP_TIME / 2));
  }

  th.join();
  cout << a << " " << b << endl;

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
  //this_thread::sleep_for(chrono::milliseconds(THIRD_SLEEP));
  cout << "id: " << this_thread::get_id() << " " << "======\t" << __FUNCTION__ << " STOPPED" << "\t\t======" << endl;
  return;
}
