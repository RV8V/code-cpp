#include "multithread.h"

bool lock = false;
atomic<int> lock_i(0);

#define MAX_COUNTER 50

int32_t current_value;
condition_variable condition;

void prepare_data(mutex& mtx, queue<int32_t>& collection) {
  /*
   * srand(time(NULL));
  * int32_t value = rand() % 100;
  */
  default_random_engine random_engine(rand() % 10);
  uniform_int_distribution<int32_t> int_distribution(10, 1000);
  int32_t value = int_distribution(random_engine);

  unique_lock<mutex> un_lock(mtx);
  collection.push(value);
  condition.notify_one();
  this_thread::sleep_for(chrono::milliseconds(value));
  un_lock.unlock();

  cout << "value: " << value << endl;

  ++current_value;
  if (current_value == MAX_COUNTER) return;

  prepare_data(mtx, collection);
}

void extract_data(mutex& mtx, queue<int32_t>& collection) {
  /*while(collection.empty()) {
  }*/

  unique_lock<mutex> un_lock(mtx);
  condition.wait(un_lock, [&collection] {
    return !collection.empty();
  });

  cout << "last value: " << collection.back() << endl;
  collection.pop();
  un_lock.unlock();
  if (current_value == MAX_COUNTER) return;
  extract_data(mtx, collection);
}

int prepare_and_extract(void) {
  queue<int32_t> collection;
  mutex mtx;

  thread prepare_thread(prepare_data, ref(mtx), ref(collection));
  thread extract_thread(extract_data, ref(mtx), ref(collection));

  prepare_thread.join();
  extract_thread.join();

  return EXIT_SUCCESS;
}

int main(int, const char**) {
  prepare_and_extract();
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
