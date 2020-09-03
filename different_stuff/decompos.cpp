#include <iostream>
#include <vector>
#include <tuple>
#include <map>

#define VALUE_T 123.4f
#define ID_T 1
#define TEST_STR "gnusmas z60"
#define FIRST_INDEX 0

struct unit {
  size_t id;
  size_t type;
  size_t power;
  std::string description;
};

void test(void);
void print_info(const std::vector<unit>);

int main(int, char const**) {
  std::vector<unit> tanks{
    {1, 1, 100, "type_a"}
  };
  test();
  print_info(tanks);
  return 0;
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
    {1, "a80"}, {2, "b34"}, {3, "c59"};
  };
  for(const auto &[id, model]: phones) std::cout << "id" << id << " " << "model" << model << std::endl;
}
