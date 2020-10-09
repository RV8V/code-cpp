#include <iostream>

class my_class {
private:
  int *data;
  int size;
public:
  my_class(int size) {
    this->size = size;
    this->data = new int[size];
    for (int i = 0; i < size; i++)
      *(this->data + i) = i;
    std::cout << "my_class() constructor: " << this << std::endl;
  }
  ~my_class() {
    delete[] this->data;
    std::cout << "~my_class() destructor: " << this << std::endl;
  }
  my_class(const my_class &other) {
    //if (this->data != nullptr) delete[] this->data;
    this->size = other.size;
    this->data = new int[other.size];
    for (int i = 0; i < other.size; i++)
      *(this->data + i) = *(other.data + i);
    std::cout << "constructor copy: " << this << std::endl;
  }
  my_class(my_class &&other) {
    this->size = other.size;
    this->data = other.data;
    other.data = nullptr;
  }
  my_class& operator=(const my_class &other) {
    if (this == &other) return *this;
    delete[] this->data;
    this->size = other.size;
    this->data = new int[other.size];
    for (int i = 0; i < other.size; i++)
      *(this->data + i) = *(other.data + i);
    std::cout << "operator=" << '\n';
    return *this;
  }
  /*bool operator==(const my_class &other) {
    return this->size == other.size;
  }*/
  /*bool operator!=(const my_class &other) {
    return !this->operator==(other);
  }*/
  int& operator[](int i) {
    return *(this->data + i);
  }
  bool operator==(const my_class &other) {
    std::cout << "operator==" << std::endl;
    if (this->size != other.size) return false;
    for (int i = 0; i < this->size; i++)
      if (*(this->data + i) != *(other.data + i))
        return false;
    else return true;
  }
  bool operator!=(const my_class &other) {
    return !this->operator==(other);
  }
};

void cpy(my_class value) {
  std::cout << "call: " << __FUNCTION__ << std::endl;
}

my_class foo_a(void) {
  my_class tmp(10);
  std::cout << "call: " << __FUNCTION__ << std::endl;
  return tmp;
}

int main(int argc, char const **argv) {
  my_class a = {10};
  const int val = a.operator[](1);
  std::cout << "val: " << val << '\n';
  my_class b = a;
  const bool flag = b.operator!=(a);
  std::cout << flag << '\n';
  //cpy(obj);
  //foo_a();
  //my_class a(1);
  //my_class b(2);
  /*my_class c(3);
  a = b = c;
  a.operator=(b).operator=(c);
  a.operator=(b);*/
  //bool result = a.operator!=(b);
  //bool res = a == b;
  //std::cout << "result: " << result << '\n';
  return 0;
}
