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

class video_buffer {
private:
  int* pixels;
public:
  video_buffer(int buffer_size) {
    this->pixels = new int[buffer_size];
  }
  ~video_buffer(void) {
    delete[] this->pixels;
  }

  void make_frame(void) {
  }

  int game(void) {
    video_buffer screen(10);
    screen.make_frame();
  }
};

template<typename Y>
class smart_pointer_test {
private:
  Y* m_data;
public:
  smart_pointer_test(Y* data): m_data(data) {
  }
  ~smart_pointer_test() {
    delete this->m_data;
  }

  Y& operator*() const {
    return *this->m_data;
  }
  Y* operator->() const {
    return this->m_data;
  }
};

struct my_struct {
private:
  int a, b;
public:
  my_struct(int a, int b) {
    this->a = a;
    this->b = b;
  }

  void do_smth(void) {
    cout << "hello world" << endl;
  }
};

template<typename T>
class auto_ptr_t {
private:
  T* m_ptr;
public:
  auto_ptr_t(T* ptr = nullptr): m_ptr(ptr) {
  }

  auto_ptr_t(auto_ptr_t& a) {
    m_ptr = a.m_ptr;
    a.m_ptr = nullptr;
  }

  auto_ptr_t& operator=(auto_ptr_t& a) {
    if (&a == this)
      return *this;
    delete m_ptr;
    m_ptr = a.m_ptr;
    a.m_ptr = nullptr;
    return *this;
  }

  T& operator*() { return *m_ptr; }
  T* operator->() { return m_ptr; }
  bool isNull() const { return m_ptr == nullptr; }

  ~auto_ptr_t() {
    delete m_ptr;
  }
};

class Item {
public:
  Item() { cout << "item acquired\n"; }
  ~Item() { cout << "Iten destroyed\n"; }
};

int test(void) {
  smart_pointer_test<my_struct> p_struct(new my_struct(1, 2));
  p_struct->do_smth();
}

int main(int, const char**) {
#ifdef value_auto
  auto_ptr_t<Item> item1(new Item);
  auto_ptr_t<Item> item2;

  cout << "item 1 " << (item1.isNull() ? "null\n" : "not null\n");
  cout << "item 2 " << (item2.isNull() ? "null\n" : "not null\n");

  item2 = item1;
  cout << "ownership transferred\n";

  cout << "item 1 " << (item1.isNull() ? "null\n" : "not null\n");
  cout << "item 2 " << (item2.isNull() ? "null\n" : "not null\n");
#endif

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

#ifdef segmentation_falt
  int* p;
  cout << *p << endl;
#endif

#ifdef auto_testing
  auto_ptr<my_struct> p1(new my_struct);
  auto_ptr<my_struct> p2;
  p2 = p1;
#endif

#ifdef shared
  shared_ptr<my_struct> p1(new my_struct(1, 2));
  shared_ptr<my_struct> p2;
  p2 = p1;
  if (p2) {
    p2->do_smth();
    p1->do_smth();
  }

  p2->do_smth();
#endif
  return EXIT_SUCCESS;
}
