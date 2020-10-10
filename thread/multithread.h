#ifndef _MULTITHREAD_H
#define _MULTITHREAD_H

#include <iostream>
#include <thread>
#include <functional>
#include <atomic>
#include <chrono>
#include <mutex>
#include <random>
#include <queue>
#include <ctime>
#include <condition_variable>

using namespace std;

template<class MutexTypeDefinition>
class safe_mutex final {
private:
  MutexTypeDefinition& mutex;
public:
  safe_mutex(MutexTypeDefinition& mtx): mutex(mtx) {
    mutex.lock();
  }
  ~safe_mutex() {
    mutex.unlock();
  }
};

#endif
