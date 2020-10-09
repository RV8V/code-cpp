#include <iostream>

enum { ARR_LENGTH = 20, ARR_TEST_COUNT = 2, ARR_TEST_COUNT_NEXT };

void f_a(void);
void f_a(int);
void f_a(const char*);
void f_a(unsigned);

void f_test(int);
void f_test(bool);
void f_test(void*);

int main(int argc, char const *argv[]) {
  f_a("hello");
  f_test(0);
  f_test(NULL);
  f_test(nullptr);
  return 0;
}

void f_a(void) {
  char* p_ch = nullptr;
  double* p_d = nullptr;

  p_ch = (char*)malloc(sizeof(char));
  p_ch = new char;
  delete p_ch;
  free(p_ch);

  p_ch = new char[ARR_LENGTH];
  p_ch = (char*)malloc(ARR_LENGTH * sizeof(char));
  delete[] p_ch;
  free(p_ch);

  p_d = (double*)malloc(sizeof(double));
  p_d = new double;
  delete p_d;
  free(p_d);

  p_d = (double*)malloc(ARR_LENGTH * sizeof(double));
  p_d = new double[ARR_LENGTH];
  delete[] p_d;
  free(p_d);

  /*delete[] p_d; -> crash*/
  p_d = nullptr;
  delete[] p_d;
}

void f_a(int) {
  struct A {
    A() { std::cout << __FUNCTION__ << std::endl; };
    ~A() { std::cout << __FUNCTION__ << std::endl; };
  };
  A *p_a = new A; delete p_a;
  p_a = new A[ARR_TEST_COUNT]; delete[] p_a;
  p_a = new A[ARR_TEST_COUNT_NEXT]; /*delete p_a; -> crash; delete p_a + (i = 0) -> free first element*/
  p_a = new A; /*delete[] p_a; -> crash*/
}

void f_a(char) {
  struct A {
    A() { std::cout << __FUNCTION__ << std::endl; };
    ~A() { delete (*this).p_i; std::cout << __FUNCTION__ << std::endl; };
    int *p_i;
  };
  A* p_a = (A*)malloc(sizeof(A)); free(p_a);
  p_a = (A*)malloc(sizeof(A)); delete p_a;
}

void f_a(const char*) {
  struct A {
  private:
    int ma = 20;
    int mb = 30;
  public:
    A() { std::cout << __FUNCTION__ << std::endl; };
    ~A() { std::cout << __FUNCTION__ << std::endl; };
    void set_a(int a) { (*this).ma = a; };
    void set_b(int b) { (*this).mb = b; };
  };
  A* p_a = (A*)malloc(sizeof(A));
  *((int*)(p_a)) = 100;
  (*p_a).set_a(300);
  (*p_a).set_b(200);
  delete p_a;
}

void f_test(int) { std::cout << __FUNCTION__ << "-> f_test(int)" << std::endl; };
void f_test(bool) { std::cout << __FUNCTION__ << "-> f_test(bool)" << std::endl; };
void f_test(void*) { std::cout << __FUNCTION__ << "-> f_test(void*)" << std::endl; };
