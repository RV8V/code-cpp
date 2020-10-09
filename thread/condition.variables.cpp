#include <iostream>
#include <thread>
#include <unistd.h>
#include <fstream>
#include <mutex>
#include <condition_variable>

using namespace std;

void write_logs(void);
void get_char(void);
bool ret(void);

mutex mtx;
condition_variable cv;

bool _var = false;

bool ret(void) {
  return _var;
}

int main(int, const char**) {
  thread t1(write_logs);
  thread t2(get_char);

  t1.detach();
  t2.join();
  return 0;
}

void write_logs(void) {
  ofstream log;
  string str;
  static int number = 0;

  while(true) {
    unique_lock<mutex> ul(mtx);
    cv.wait(ul, ret);

    log.open("log.log", ios_base::app);
      str = "is write_logs: " + to_string(++number) + '\n';
      log.write(str.c_str(), str.length());
    log.close();

    usleep(500000);
  }
  return;
}

void get_char(void) {
  while(true) {
    char input;
    cout << "input: "; cin >> input;
    cin.clear();

    if (input == 'y') {
      _var = true;
      cv.notify_one();
    }

    if (input == 'n') _var = false;
  }
  return;
}
