#ifndef _THREAD_TEST_H_
#define _THREAD_TEST_H_

#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <exception>
#include <ctime>
#include <stdarg.h>

using namespace std;

template<typename T>
class container {
private:
  mutable mutex lock;
  vector<T> v_elements;
public:
  void add(T);
  void add_range(int, ...);
  void dump(void) const;
};

template<typename T>
void container::add(T element) {
  this->lock.lock();
  this->v_elements.push_back(element);
  this->lock.unlock();
}

template<typename T>
void container::add_range(int num, ...) {
  va_list arguments;
  va_start(arguments, num);
  for (int i = 0; i < num; ++i) {
    this_thread::sleep_for(chrono::milliseconds(100));
    this->lock.lock();
    this->add(va_arg(arguments, T));
    this->lock.unlock();
  }
  va_end(arguments);
}

template<typename T>
void container::dump(void) const {
  this->lock.lock();
  for (auto& e : this->v_elements)
    cout << e << endl;
  this->lock.unlock();
}

void thread_function_constainer(container<int>&);
void deadlock_test(void);

mutex mtx;
vector<exception_ptr> v_exceptions;

void throw_function(void);
void thread_function(void);
void test_exception(void);

#endif
