#include <iostream>
#include <ctime>
#include <cstdlib>

#define NEW_LINE '\n'
#define begin {
#define end }
#define AND &&
#define OR ||
#define templ_type(name, type) type type_##name(type a, type b) begin return a * b; end
#define test_mac(x, y) x * y
#define gen_rand(x) rand() % x
#define DEBAG

void print_debug_line(const char* &str)
begin
  #ifdef DEBAG
  std::cerr << str << std::endl;
  #endif
end

templ_type(int, int);

#if NULL
using std::string;
using std::cout;
using std::endl;
#endif

template<typename T1, typename T2> inline const int sum(T1, T2);

inline const int sum(int& a, int& b)
begin
  return a + b;
end

inline void test_stack(int& i)
begin
  std::cout << i++ << std::endl;
  test_stack(i);
end

void print_arr(int* p_arr, const int size)
begin
  int* move;
  for(move = p_arr; move < p_arr + size; move++)
    std::cout << "value is: " << *move << NEW_LINE;
end

void fill_arr(int* p_arr, const int size)
begin
  int* move;
  std::cout << "move : " << move << " p_arr : " << p_arr << std::endl;
  for(move = p_arr; move != p_arr + size; move++)
    *move = rand() % 10 - 2;
end

void push_back(int* &p_arr, int &size, const int value)
begin
  int* new_arr = new int[size + 1];
  int* move;
  for(move = p_arr; move != p_arr + size; move++)
    *new_arr = *move;
  *(new_arr + size) = value;
  size++;
  delete[] p_arr;
  p_arr = new_arr;
end

void push_back_c(int* &p_arr, int &size, const int value)
begin
  size++;
  p_arr = (int*)realloc(p_arr, size * sizeof(int));
  p_arr[size - 1] = value;
end

void pop_back(int* &p_arr, int &size)
begin
  size--;
  int* new_arr = new int[size];
  int* move;
  for(move = p_arr; move != p_arr + size; move++)
    *new_arr = *move;
  delete[] p_arr;
  p_arr = new_arr;
end

void add_first(int* &p_arr, int &size, const int value)
begin
  int* new_arr = new int[size + 1];
  int* move;
  *move = value;
  move++;
  for(move = p_arr; move != p_arr + size; move++)
    *new_arr = *move;
  size++;
  delete[] p_arr;
  p_arr = new_arr;
end

void delete_first(int* &p_arr, int &size)
begin
  size--;
  int* new_arr = new int[size];
  int* move;
  for(move = p_arr; move < p_arr + size; move++)
    *new_arr = *++move;
  delete[] p_arr;
  p_arr = new_arr;
end

int strlen_c(const char* str)
begin
  int i = 0;
  while((int)*(str + i)) i++;
  return i;
end

template<typename T>
void show_data(T (*data_get)(T), T value = 0)
begin
  std::cout << "data: " << data_get(value) << std::endl;
end

void test_a(void) begin std::cout << __FUNCTION__ << std::endl; end
const char* param_f(const char* str) begin return str; end
void print_data(const char*(*get_data)(const char*), const char* str) begin std::cout << (*get_data)(str) << std::endl; end

class my_class
begin
private:
  int* data;
  int size;
public:
  my_class(int);
  my_class(const my_class &);
  ~my_class(void);
  my_class& operator=(const my_class &);
  bool operator==(const my_class &);
  bool operator!=(const my_class &);
  int& operator[](int)
end

my_class::my_class(int size)
begin
  this->size = size;
  this->data = new int[size];
  for (int i = 0; i < size; i++)
    *(this->data + i) = i;
  std::cout << "my_class() constructor: " << this << std::endl;
end

my_class::~my_class()
begin
  delete[] this->data;
  std::cout << "~my_class() destructor: " << this << std::endl;
end

my_class::my_class(const my_class &other)
begin
  if (this->data != nullptr) delete[] this->data;
  this->size = other.size;
  this->data = new int[other.size];
  for (int i = 0; i < other.size; i++)
    *(this->data + i) = *(other.data + i);
  std::cout << "constructor copy: " << this << std::endl;
end

my_class& my_class::operator=(const my_class &other)
begin
  if (this == &other) return *this;
  delete[] this->data;
  this->size = other.size;
  this->data = new int[other.size];
  for (int i = 0; i < other.size; i++)
    *(this->data + i) = *(other.data + i);
  std::cout << "operator=" << '\n';
  return *this;
end

bool my_class::operator==(const my_class &other)
begin
  return this->size == other.size;
end

bool my_class::operator!=(const my_class &other)
begin
  return !this->operator==(other);
end

int& my_class::operator[](int i)
begin
  return *(this->data + i);
end

void cpy(my_class value)
begin
  std::cout << "call: " << __FUNCTION__ << std::endl;
end

my_class foo_a(void)
begin
  my_class tmp(10);
  std::cout << "call: " << __FUNCTION__ << std::endl;
  return tmp;
end

struct Test;

struct Point
begin
private: int m_x, m_y;
public:
  Point(): m_x{0}, m_y{0} begin std::cout << "Point() constructor by default" << std::endl; end;
  Point(int x, int y): m_x{x}, m_y{y} begin std::cout << "Point() constructor" << std::endl; end
  Point(const Point &point)
  begin
    std::cout << "copy constructor" << std::endl;
    this->m_x = point.m_x;
    this->m_y = point.m_y;
  end
  ~Point(void) begin std::cout << "~Point() destructor" << std::endl; end
  Point& operator=(const Point &point)
  begin
    if (this == &point) return *this;
    std::cout << "operator=" << std::endl;
    this->m_x = point.m_x;
    this->m_y = point.m_y;
    return *this;
  end
  Point operator+(const Point &point)
  begin
    std::cout << "operator+" << std::endl;
    Point tmp{this->m_x + point.m_x, this->m_y + point.m_y};
    return tmp;
  end
  Point& operator++(void)
  begin
    std::cout << "operator++ pre" << std::endl;
    this->m_y++; this->m_x++;
    return *this;
  end
  Point operator++(int)
  begin
    std::cout << "operator++ post" << std::endl;
    Point tmp{*this};
    this->m_x++; this->m_y++;
    return tmp;
  end
  Point& operator--(void) {
    std::cout << "operator-- pre" << std::endl;
    this->m_y -= 1; this->m_x -= 1;
    return *this;
  end
  Point operator--(int)
  begin
    std::cout << "operator-- post" << std::endl;
    Point tmp{*this};
    this->m_x -= 1; this->m_y -= 1;
    return tmp;
  end
  friend void change_state(Point&, Test&);
end

struct Test
begin
private:
  int data = 0;
  friend void change_state(Point&, Test&);
end;

void change_state(Point& point, Test& test)
begin
  std::cout << "friend function: " << __FUNCTION__ << std::endl;
  point.m_x = rand() % 10;
  point.m_y = rand() % 10;
  test.data = 1;
end

class Apple;
class Human
begin
public:
  void take_apple(Apple& apple);
end;

class Apple
begin
public:
  Apple(int weight, std::string color)
  begin
    this->weight = weight;
    this->color = color;
  end;
  friend void Human::take_apple(Apple&);
private:
  int weight;
  std::string color;
end;

int main(int argc, char const** argv)
begin
  const char* test_line = "err";
  print_debug_line(test_line);
  for(char i = 0; i < argc; i++)
  begin
    std::cout << "current element: " << *(argv + i) << std::endl;
    for(char j = 0; j < sizeof(*(argv + i)); j++)
      std::cout << "element: " << (char)*(*(argv + i) + j) << std::endl;
  end
#ifdef DEBAG_TEST
  const int res = test_mac(20, 30);
  char g = 10;
  do
    begin
      std::cout << g << std::endl;
    end
  while(g-- > 0);
  void (*test_ptr)(void);
  test_ptr = &test_a; (*test_ptr)();
  print_data(&param_f, "hello world");
  std::cout << "len: " << strlen_c("test") << std::endl;
  int size = 2;
  int* p_arr = new int[size];
  fill_arr(p_arr, size);
  print_arr(p_arr, size);
  push_back(p_arr, size, 10);
  print_arr(p_arr, size);
  pop_back(p_arr, size);
  print_arr(p_arr, size);

  int size = 4;
  int* p_start = new int[size];
  int* move;
  for (move = p_start; move != p_start + size; move++)
  begin
    *move = 10 + rand() % 10;
    std::cout << "value: " << *move << '\n';
  end

  int four = 4;
  int six = 6;
  int** arr = new int*[four];
  std::cout << "arr address: " << arr << NEW_LINE;
  for (int i = 0; i < four; i++)
  begin
    std::cout << "arr inside: " << arr + i << NEW_LINE;
    *(arr + i) = new int[six];
    delete[] *(arr + i);
  end
  delete[] arr;

  int *arr = new int[10];
  for(int i = 0; i < 10; i++)
  begin
    i[arr] = rand() % 10;
    std::cout << "current value is: " << i[arr] << NEW_LINE;
  end
  delete[] arr;

  int value = 10, change_v = 20;
  const int& ref = value;
  ref = change_v;
  std::cout << "first value: " << ref << "address: " << &ref << " " << &value << std::endl;

  int a = 5;
  int* pa = &a;
  int** ppa = &pa;

  &ref = &ref + &value;

  int* ptr;
  srand((int)*ptr);

  const int value_int = abs(-10);
  const long value_long = labs(-242344241412);
  const double value_double = labs(-1.412);

  const int result = sum<int, unsigned char>(256, 233);

  std::string str{"hello world"};
  std::cout << "hello world" << NEW_LINE;
  int a = 10, b = 20;
  const int res = sum(a, b);

  unsigned char i = 0;
  do std::cout << "i = " << (int)i << "  " << (char)i << NEW_LINE; while(i++ < 255);
#endif
  my_class a = {10};
  my_class b = a;
  cpy(obj);
  foo_a();
  a.operator[](1);
  my_class a(1);
  my_class b(2);
  my_class c(3);
  a = b = c;
  a.operator=(b).operator=(c);
  a.operator=(b);
  bool result = a.operator!=(b);
  bool res = a == b;
  std::cout << "result: " << result << '\n';

  Point a = {1, 2};
  Point b = {3, 4};
  a.operator=(b);
  Point c = b;
  Point c = a.operator+(b);
  a.operator++(); ++a;
  b.operator++(); b++;
  a.operator--(); --a;
  b.operator--(); b--;
  return 0;
end

template<typename T1, typename T2> inline const int sum(T1 v1, T2 v2) begin return v1 + v2; end

void Human::take_apple(Apple& apple)
begin
  std::cout << __FUNCTION__ << std::endl << "weight: " << apple.weight << std::endl << "color: " << apple.color << std::endl;
end
