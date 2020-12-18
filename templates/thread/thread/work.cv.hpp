#ifndef _WORK_CV_H_
#define _WORK_CV_H_

#include <iostream>
#include <mutex>
#include <thread>
#include <condition_variable>
#include <chrono>

using namespace std;

condition_variable g_bell;
condition_variable_any g_door;

class Manager {
public:
  void come_to_work();
};

class Security {
public:
  static bool m_sector_clear;
  static mutex m_sector_mutex;
public:
  static bool sector_clear();
  void notify_fellows();
  void work_hard();
};

class Programmer {
public:
  void work_hard();
  void play_warkraft();
};

void Manager::come_to_work() {
  cout << "hey security, please open the door!\n";
  g_bell.notify_one();
  mutex mtx;
  mtx.lock();
  g_door.wait(mtx);
  mtx.unlock();
}

bool Security::sector_clear() {
  lock_guard<mutex> lock(m_sector_mutex);
  return m_sector_clear;
}

void Security::notify_fellows() {
  lock_guard<mutex> lock(m_sector_mutex);
  m_sector_clear = false;
}

void Security::work_hard() {
  m_sector_clear = true;
  mutex mtx;
  unique_lock<mutex> lock(mtx);

  while("wait for manager comming -> bell ring") {
    if (g_bell.wait_for(lock, chrono::seconds(5)) == cv_status::timeout)
      this_thread::sleep_for(chrono::seconds(10));
    else {
      this->notify_fellows();
      g_door.notify_one();
      cout << "hello manager, ..." << endl;
    }
  }
}

void Programmer::work_hard() {
  cout << "let's write some govnokod\n";
  int i = 0;
  while("writing...") {
    i++;
    --i;
  }
}

void Programmer::play_warkraft() {
  while(Security::sector_clear()); // play warkraft
  this->work_hard();
}

#endif
