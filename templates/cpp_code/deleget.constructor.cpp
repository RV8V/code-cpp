#include <iostream>

class Human {
private:
  std::string name;
  int age, weight;
public:
  Human(std::string name) {
    this->name = name;
    this->age = 0;
    this->weight = 0;
  }
  Human(std::string name, int age) {
    this->name = name;
    this->age = age;
    this->weight = 0;
  }
  Human(std::string name, int age, int weight) {
    this->name = name;
    this->age = age;
    this->weight = weight;
  }
};

class Human_deleg_constructor {
private:
  std::string name;
  int age, weight;
public:
  Human_deleg_constructor(std::string name) {
    this->name = name;
    this->age = 0;
    this->weight = 0;
  }
  Human_deleg_constructor(std::string name, int age): Human_deleg_constructor(name) {
    this->age = age;
  }
  Human_deleg_constructor(std::string name, int age, int weight): Human_deleg_constructor(name, age) {
    this->weight = weight;
  }
};

int main(int, char const**) {
  Human_deleg_constructor h("hello world", 20, 1);
  return 0;
}
