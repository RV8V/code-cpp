#ifndef _ASYNC_FUTURE_PROMISE_
#define _ASYNC_FUTURE_PROMISE_c

#include <iostream>
#include <thread>
#include <future>
#include <ctime>
#include <memory>
#include <queue>
#include <limits>
#include <chrono>
#include <exception>

using namespace std;

int32_t generate_value(int32_t&, int32_t&, int32_t);
void value_proccessing(shared_future<int32_t>&);
void test_future(int32_t, int32_t, int32_t);
void save_to_file(shared_future<int32_t>&);
void throw_exception(void);
void generate_value_promise(int32_t&, int32_t&, int32_t, promise<int32_t>&);

#endif
