#include <iostream>
#include <vector>
#include <tuple>
#include <map>
#include <mutex>
#include <ctime>
#include <cstring>

#define VALUE_T 123.4f
#define ID_T 1
#define TEST_STR "gnusmas z60"
#define FIRST_INDEX 0
#define TEN_V 10
#define THREE_V 3
#define VALUE_TO_TEST 1

struct unit {
  size_t id;
  size_t type;
  size_t power;
  std::string description;
};

void test(void);
void print_info(const std::vector<unit>);
bool is_exists(int, const std::map<int, std::string>);
int get_char(bool);
bool lock_mutex(bool);

int main(int, char const**) {
  std::vector<unit> tanks{
    {1, 1, 100, "type_a"}
  };
  test();
  print_info(tanks);
  return 0;
}

bool lock_mutex(bool st = false) {
  std::mutex m;
  bool is_changed{st};
  if (std::lock_guard<std::mutex> l{m}; is_changed) return is_changed;
  return ~is_changed;
}

bool is_exists(int key, const std::map<int, std::string> &data) {
  if (auto it{data.find(key)}; it != data.end()) return true;
  return false;
}

int get_char(bool f = false) {
  srand(time(NULL));
  if (char r{char(rand() % TEN_V - THREE_V)}; r == VALUE_TO_TEST && r) return 0;
  return -1;
}

void print_info(const std::vector<unit> &u) {
  auto [id, type, power, description]{u.at(FIRST_INDEX)};
  for(auto [i, t, p, d]: u) std::cout << i << t << p << d << std::endl;
}

void test(void) {
  auto p{std::make_pair(ID_T, VALUE_T)};
  auto t{std::make_tuple(ID_T, VALUE_T, TEST_STR)};
  auto &_id{std::get<ID_T>(t)};
  auto &_value{std::get<ID_T + 1>(t)};
  std::cout << "id: " << p.first << " " << "value: " << p.second << std::endl;
  std::cout << "current value: " << std::get<(long unsigned int)ID_T>(t) << std::endl << std::endl;
  {
    auto &&[id, value]{std::make_pair(ID_T, VALUE_T)};
    std::cout << id << " " << value << std::endl;
  }
  const auto &&[id, value, model]{std::make_tuple(ID_T, VALUE_T, TEST_STR)};
  std::map<size_t, std::string> phones {
    {1, "a80"}, {2, "b34"}, {3, "c59"}
  };
  for(const auto &[id, model]: phones) std::cout << "id" << id << " " << "model" << model << std::endl;
}
