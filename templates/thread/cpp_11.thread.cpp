#include "cpp_11.thread.h"

int32_t main(int32_t, const char**) {
  deadlock_test();
  test_exception();
  return EXIT_SUCCESS;
}

void throw_function(void) {
  throw "something wrong happened";
}

void thread_function_constainer(container<int>& c) {
  c.add_range(3, rand() % 100, rand() % 100, rand() % 100);
}

void thread_function(void) {
  try {
    throw_function();
  } catch(const char* err) {
    lock_guard<mutex> lock(mtx);
    cout << "error was push to vector of pointers to exceptions" << endl;
    v_exceptions.push_back(current_exception());
  }
}

void test_exception(void) {
  v_exceptions.clear();
  thread th(thread_function);
  th.join();

  for (auto& e : v_exceptions) {
    try {
      if (e != nullptr) {
        rethrow_exception(e);
      } else {
      }
    } catch(const char* err) {
      cout << "error: " << err << endl;
    }
  }
}

void deadlock_test(void) {
  srand((unsigned int)time(0));
  container<int> c;

  thread thr1(thread_function_constainer, ref(c));
  thread thr2(thread_function_constainer, ref(c));
  thread thr3(thread_function_constainer, ref(c));

  thr1.join(); thr2.join(); thr3.join();

  c.dump();
}
