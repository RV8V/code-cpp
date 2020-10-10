#include <iostream>
#include <thread>
#include <future>
#include <unistd.h>

using namespace std;

bool task(int);
void task_f(future<int>&);

void test_a(void);
void test_b(void);
void test_c(void);

int main(int, const char**) {
  test_c();
  return 0;
}

bool task(int n) {
  usleep(n);
  cout << n << ": ";
  return true;
}

void task_f(future<int>& f) {
  int n = f.get();
  usleep(n);
  cout << n << ": " << "end" << endl;
  return;
}

void test_a(void) {
  future<bool> ft = async(task, 3000000);
  if (ft.get()) cout << "got value from future" << endl;
  cout << "after getting value from future" << endl;
  return;
}

void test_b(void) {
  packaged_task<bool(int)> pt(task);
  future<bool> ret = pt.get_future();
  thread th(move(pt), 2);
  if (ret.get()) cout << "got value from future in packaged_task" << endl;
  th.join();
  return;
}

void test_c(void) {
  promise<int> pr;
  future<int> ft = pr.get_future();
  thread th(task_f, ref(ft));
  pr.set_value(1);
  th.join();
  return;
}
