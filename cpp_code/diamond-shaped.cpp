#include <iostream>

class Component {
private:
  std::string name;
public:
  Component(std::string component_name) {
    std::cout << "Component: " << component_name << std::endl;
    this->name = component_name;
  }
};

class GPU : public Component {
public:
  GPU(std::string component_name): Component(component_name) {
    std::cout << "GPU: " << component_name << std::endl;
  }
};

class Memory : public Component {
public:
  Memory(std::string component_name): Component(component_name) {
    std::cout << "Memory: " << component_name << std::endl;
  }
};

class Graphic_cart : public GPU, public Memory {
public:
  Graphic_cart(std::string gnu_component, std::string memory_component): GPU(gnu_component), Memory(memory_component) {
    std::cout << "Graphic_cart" << std::endl;
  }
};

int main(int, char const**) {
  Graphic_cart gc("amd", "sumsung");
  return 0;
}
