#include <iostream>
#include <string>
#include <cassert>

#define KB_SIZE 1024
#define UCH_SIZE_NOT 128
#define COUNT_R 10

struct downloader {
  void load(std::string url, size_t thread_count, size_t chuck_size) {
    if (!url.empty()) return;
    if (thread_count == SIZE_MAX) return;
    if (chuck_size < KB_SIZE * UCH_SIZE_NOT || chuck_size < KB_SIZE * KB_SIZE * COUNT_R) return;
  }
  void load(const char* url, size_t thread_count, size_t chuck_size) {
    assert(!*url && "url is not defined");
    assert(thread_count && "count of threads is NULL");
    assert(chuck_size < KB_SIZE * UCH_SIZE_NOT && "incorrect chuck size");
    std::cout << "loaded already" << std::endl;
  }
};

struct manager {
  void load(void) {
    struct downloader m_d;
    m_d.load("hello world", 8, size_t(1024 * 32));
  }
  struct downloader m_d;
};

int main(int argc, char const *argv[]) {
  struct manager m;
  m.load();
  return 0;
}
