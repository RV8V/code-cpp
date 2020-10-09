#include <thread>
#include <functional>
#include <memory>
#include <mutex>

#include "timer.h"

#define SLEEP_TIME 1000
#define CYCLE_VALUE 10
#define FIRST_SLEEP 1000
#define SECOND_SLEEP 2000
#define THIRD_SLEEP 1000
#define INNER_CYCLE 10
#define OUT_CYCLE 5
#define MILISS 20

using namespace std;

class MyClass;

void do_work_a(void);
void do_work(int&, int&);
int return_same(int);

void print(const char);
void print_guard(const char);

void test_deadlock(void);
void print_rect_dead_a(const char ch);
void print_rect_dead_b(const char ch);

/*
 * synchronization primitives
 * shared data protection
 * thread synchronization
 * interlocking of deadlock
 * lock_guard - mutex++
*/

class MyClass {
public:
  MyClass() {}
  ~MyClass() {}
public:
  void do_work(void) {
    this_thread::sleep_for(chrono::milliseconds(1000));
    cout << endl << "|------| " << "(hello world from) " << __FUNCTION__ << " " << "|------|" << endl;
  }
  int do_work_int(int value) {
    this_thread::sleep_for(chrono::milliseconds(1000));
    return value * 10;
  }
  void do_work_test(void) {
    std::cout << "/* message */" << __FUNCTION__ << "/* message */" << endl;
  }
  void print_this(void) {
    cout << (void*)this << endl;
  }
};

mutex mtx, tmp_mtx;

int main(int, const char** const) {
  test_deadlock();
  /*const char ch_a = '&';
  const char ch_u = '*';
  const char arr[] = { ch_a, ch_u };

  Timer timer;

  thread t1(print, ch_a);
  thread t2(print, ch_u);

  int i = 1;
  do {
    print_guard(*(arr + i));
    print(*(arr + i));
  } while (i-- > 0);

  t1.join();
  t2.join();

  timer.~Timer();*/

  /*int a = 1, b = 2;
  //thread th(do_work, ref(a), ref(b));
  //do_work(a, b);

  MyClass test_h;
  test_h.print_this();

  cout << "==================== " << __FUNCTION__ << " ====================" << endl;
  thread class_testing(&MyClass::do_work, &test_h);
  cout << "address: " << (void*)&test_h << endl;

  thread class_testing_copy(&MyClass::do_work, test_h);
  cout << "address: " << (void*)&test_h << endl;

  class_testing.join();
  class_testing_copy.join();
  cout << "==================== " << __FUNCTION__ << " ====================" << endl;

  int result = 1;
  thread t([&result]() {
    return result = return_same(20);
  });

  function<int()> f = [result]() mutable {
    cout << __FUNCTION__ << endl;
    return result *= 2;
  };

  thread test([&result]() {
    this_thread::sleep_for(chrono::milliseconds(1000));
    cout << "=====\tsleep in lambda function for 1000\t====="
         << endl;
    MyClass m;
    result = m.do_work_int(result);
  });

  MyClass m;
  thread m_class(&MyClass::do_work, m);
  thread m_class_int(&MyClass::do_work_int, m, result);

  thread deep([=]() mutable {
    MyClass m;
    function<void(void)> f = [&]() { m.do_work_test(); }; f();
    ([]() { std::cout << "/* message *//*" << endl; })();
    this_thread::sleep_for(chrono::milliseconds(1000));

    thread value_info([&]() {
      cout << '\n' << '\n';
      m.do_work_test();
      cout << '\n' << '\n';

      thread value_info_deeped(([]() { std::cout << "/* message *//*" << '\n'; }));
      value_info_deeped.detach();
    });

    value_info.detach();
  });

  deep.detach();
  m_class.detach();
  m_class_int.detach();

  for (size_t i = 0; i < 10; ++i) {
    cout << "id of thread -> "
      << this_thread::get_id()
      << " " << __FUNCTION__ << " "
      << i << endl;
    this_thread::sleep_for(chrono::milliseconds(SLEEP_TIME / 2));
  }

  t.join();
  test.join();

  cout << "value of a -> " << a
      << " value of b -> " << b << endl
      << "value of result -> " << result << endl;*/
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
  this_thread::sleep_for(chrono::milliseconds(MILISS * 10));
  cout << "in thread" << endl;
  return a;
}

void print(const char ch) {
  this_thread::sleep_for(chrono::milliseconds(MILISS));

  mtx.lock();
  for (int i = 0; i < OUT_CYCLE; ++i) {
    for (int i = 0; i < INNER_CYCLE; ++i) {
      cout << ch;
      this_thread::sleep_for(chrono::milliseconds(MILISS));
    }
    cout << endl;
  }
  cout << endl;
  mtx.unlock();

  this_thread::sleep_for(chrono::milliseconds(MILISS));
  return;
}

void print_guard(const char ch) {
  this_thread::sleep_for(chrono::milliseconds(MILISS));

  lock_guard<mutex> guard(mtx);
  int i = 0;

  {
    lock_guard<mutex> lock(tmp_mtx);
    this_thread::sleep_for(chrono::milliseconds(MILISS));
    cout << "mutex lock via lock_guard" << endl << __FUNCTION__ << endl;
    this_thread::sleep_for(chrono::milliseconds(MILISS));
  }

  {
    this_thread::sleep_for(chrono::milliseconds(MILISS));

    tmp_mtx.lock();
    cout << "mutex lock via lock and unlock" << endl << __FUNCTION__ << endl;
    tmp_mtx.unlock();

    this_thread::sleep_for(chrono::milliseconds(MILISS));
  }

  do {
    do {
      cout << ch;
      this_thread::sleep_for(chrono::milliseconds(MILISS));
    }
    while(i++ < INNER_CYCLE);
    cout << endl;
  }
  while(i++ < OUT_CYCLE);
  cout << endl;

  return;
}

mutex m1;
mutex m2;

void print_rect_dead_b(const char ch) {
  m2.lock();
  cout << "enter to grap second resource" << endl;
  m1.lock();

  for (int i = 0; i < 5; ++i) {
    for (int i = 0; i < 5; ++i) {
      cout << ch;
    }
    cout << endl;
  }
  cout << endl;

  m1.lock();
  m2.lock();

  return;
}

void print_rect_dead_a(const char ch) {
  m1.lock();
  cout << "enter to grap first resource" << endl;
  m2.lock();

  for (int i = 0; i < 5; ++i) {
    for (int i = 0; i < 5; ++i) {
      cout << ch;
    }
    cout << endl;
  }
  cout << endl;

  m1.lock();
  m2.lock();

  return;
}

void test_deadlock(void) {
  Timer timer;

  thread t1(print_rect_dead_a, '*');
  thread t2(print_rect_dead_b, '%');

  t1.join();
  t2.join();

  return;
}
