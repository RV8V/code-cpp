#ifndef _TIMER_H_
#define _TIMER_H_

#include <chrono>
#include <iostream>

using namespace std;

class Timer {
public:
  Timer();
  ~Timer();
private:
  chrono::time_point<chrono::high_resolution_clock> start;
  chrono::time_point<chrono::high_resolution_clock> end;
  chrono::duration<float> duration;
};

Timer::Timer() {
  this->start = chrono::high_resolution_clock::now();
}

Timer::~Timer() {
  this->end = chrono::high_resolution_clock::now();
  this->duration = this->end - this->start;
  float result = this->duration.count();
  cout << "time passed -> " << result << " seconds" << endl;
}

#endif
