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
  return 0;
end

template<typename T1, typename T2> inline const int sum(T1 v1, T2 v2) begin return v1 + v2; end
