#include <iostream>
#include <future>
#include <thread>
#include <unistd.h>

using namespace std;

int task_to_test(int);

int main(int, const char**) {
  int delay = 20;
  packaged_task<int(int)> functor(task_to_test);
  future<int> simple_future = functor.get_future();

  thread task_thread(ref(functor), delay);

  /*
   * functor(delay);
  */

  for (size_t i = 0; i < 10; ++i) {
    cout << "& "; usleep(10000);
  }

  int result = simple_future.get();
  cout << "result -> " << result << endl;
  task_thread.join();
  return EXIT_SUCCESS;
}

int task_to_test(int delay) {
  usleep(delay *= delay *= delay);
  cout << "result: " << delay << endl;
  return delay;
}
