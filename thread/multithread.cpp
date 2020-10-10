#include <iostream>
#include <thread>
#include <functional>
#include <atomic>
#include <chrono>
#include <mutex>

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

bool lock = false;
atomic<int> lock_i(0);

int main(int, const char**) {
  int counter = 0;

  auto f = [&]() -> void {
    this_thread::sleep_for(chrono::seconds(1 / 100));
    while(lock_i) {
    }

    lock_i = lock_i + 1;
    ++counter;
    lock_i = lock_i - 1;
  };

  auto y = [&]() -> void {
    while(lock) {
    }

    lock = true;
    ++counter;
    lock = false;
  };

  auto u = [&]() -> void {
    mutex mtx;
    safe_mutex<mutex> safe_lock(mtx);
    ++counter;
  };

  chrono::time_point<chrono::high_resolution_clock> start;
  chrono::time_point<chrono::high_resolution_clock> end;
  chrono::duration<float> duration;

  start = chrono::high_resolution_clock::now();

  thread t1(u); t1.detach();
  thread t2(u); t2.detach();
  thread t3(u); t3.detach();

  end = chrono::high_resolution_clock::now();
  duration = end - start;

  this_thread::sleep_for(chrono::milliseconds(2));
  cout << "counter: " << counter << " duration: " << duration.count() << endl;

  return 0;
}
