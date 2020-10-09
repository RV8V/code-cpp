#include "timer.h"

Timer::Timer() {
  this->start = chrono::high_resolution_clock::now();
}

Timer::~Timer() {
  this->end = chrono::high_resolution_clock::now();
  this->duration = this->end - this->start;
  float result = this->duration.count();
  cout << "time passed -> " << result << " seconds" << endl;
}
