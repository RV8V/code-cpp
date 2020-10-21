#include <iostream>
#include <memory>

using namespace std;

template<typename T>
class smart_pointer {
public:
  smart_pointer(T*);
  ~smart_pointer(void);
  T& operator*(void);
private:
  T* ptr;
};

template<typename T>
smart_pointer<T>::smart_pointer(T* p_value) {
  this->ptr = p_value;
  cout << __FUNCTION__ << endl;
}

template<typename T>
smart_pointer<T>::~smart_pointer(void) {
  delete this->ptr;
  this->ptr = nullptr;
  cout << __FUNCTION__ << endl;
}

template<typename T>
T& smart_pointer<T>::operator*(void) {
  return *this->ptr;
}

int main(int, const char**) {
#ifdef value
  int* ptr = new int(4);
  int value = 4;
  ptr = &value;
  cout << "value: " << *ptr << "\naddress " << ptr << endl;

  smart_pointer<int> poiter((int*)new int(5));
  cout << "value for smart pointer: " << *poiter << endl;

  int* p = (int*)malloc(sizeof(int) * 1);
  int v = 8;
  p = &v;
  cout << "p: " << *p << endl;
  smart_pointer<int> test((int*)p);
#endif

#ifdef test_ptr_test
  smart_pointer<int> p1 = new int(2);
  smart_pointer<int> p2 = p1;
  cout << "p1 -> " << *p1 << "\np2 -> " << *p2 << endl;
#endif

#ifdef auto_ptr_test
  auto_ptr<int> ap1(new int(3));
  auto_ptr<int> ap2(ap1);
#endif

  return EXIT_SUCCESS;
}
