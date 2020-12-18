#include "async.future.promise.h"

int32_t main(int32_t, const char**) {
  int32_t value = 0, index = 20, delay = 100;

  promise<int32_t> simple_promise;
  shared_future<int32_t> simple_future_from_promise = reinterpret_cast<shared_future<int32_t>>(simple_promise.get_future());
  thread generate_thread(generate_value_promise, ref(value), ref(index), delay, ref(simple_promise));

  shared_future<int32_t> simple_future = async(launch::async, generate_value, ref(value), ref(index), delay);
  thread proccessing_thread(value_proccessing, ref(simple_future));
  thread save_to_file_thread(save_to_file, ref(simple_future));

  generate_thread.join();
  proccessing_thread.join();
  save_to_file_thread.join();

  test_future(value, index, delay);
  return EXIT_SUCCESS;
}

int32_t generate_value(int32_t& value, int32_t& index, int32_t delay) {
  do cout << '.';
  while(index++ < delay); cout << endl;
  srand(time(NULL));

  throw exception("exception inside thread");
  return value = rand() % numeric_limits<int32_t>::max();
}

void test_future(int32_t value, int32_t index, int32_t delay) {
  future<int32_t> fut_as = async(launch::async, generate_value, ref(value), ref(index), ref(delay));
  future<int32_t> fut_df = async(launch::deferred, generate_value, ref(value), ref(index), ref(delay));

  int i = 80;
  do {
    cout << '*';
    this_thread::sleep_for(chrono::milliseconds(10));
  } while(i-- > 0);

  /*
   * fut.wait();
   * fut.wait_for(chrono::seconds(2));
   * fut.wait_until(chrono::high_resolution_clock::now() + chrono::seconds(2));
   */

  value = fut_as.get();
  cout << "\nvalue is: " << value << endl;
}

void value_proccessing(shared_future<int32_t>& simple_future) {
  cout << "START VALUE PROCCESSING" << endl;
  int value = 0;

  try {
    value = simple_future.get();
  } catch(const exception& exception) {
    cout << "error -> " << exception.what() << endl;
  }
  catch(const char[] ch) {
    cout << "error while generation of value" << endl;
  }

  cout << "gotten value from future is -> " << value << endl;
  cout << "END VALUE PROCCESSING" << endl;
}

void generate_value_promise(int32_t& value, int32_t& index, int32_t delay, promise<int32_t>& simple_promise) {
  do cout << '.';
  while(index++ < delay); cout << endl;
  srand(time(NULL));

  simple_promise.set_value(value = rand() % numeric_limits<int32_t>::max());
  simple_promise.set_exception(make_exception_ptr(exception("exception returned from already future, setted by promise")));
  this_thread::sleep_for(chrono::milliseconds(2));
}

void save_to_file(shared_future<int32_t>& simple_future) {
  int value = 0;
  try {
    value = simple_future.get();
  } catch(const exception& exception) {
    cout << "error -> " << exception.what() << endl;
  }
  catch(const char* ch) {
    cout << "error while generation of value" << endl;
  }
}

void throw_exception(void) {
  throw exception("exception inside thread");
}
