#include <iostream>
#include <string>
#include <vector>

using namespace std;

void print_str(string);
void print_str(float, float);
void try_catch(const char *);

class T {
private:
  short int t_s;
  unsigned int t_u_i;
protected:
  float t_f;
public:
  char t_c;
  T(void) {};
  T(short int i, float f) {
    this->t_s = i;
    this->t_f = f;
  };
  void set_v(short int i, float f) {
    this->t_s = i;
    this->t_f = f;
  };
  unsigned int print_f() {
    return this->t_s;
  };
  ~T() {
    std::cout << "last appeal was before" << '\n';
  };
};

class R : public T {};

int main() {
  cout << "hello world" << endl;
  const char a = 'a';
  bool const test = false;
  unsigned short int const b = 10;
  float f = .0;
  double d = 0.14124;

  cout << a << endl;
  cout << test;
  cout << std::endl;
  
  short int num1, num2, result;
  float res;

  std::cout << "enter first number ";
  cin >> num1;
  std::cout << "enter second number ";
  cin >> num2;
  std::cout << num1 << '\n';
  std::cout << num2 << std::endl;

  result = num1 + num2;
  cout << num1 << " + " << num2 << " = " << result << endl;

  res = (float)num1 / num2;
  res = num1 / (float)num2;
  res = float(num1 / num2);
  std::cout << "res: " << res << '\n';

  const int array[4] = { 1, 2, 3, 4 };
  cout << array[1] << endl;
  cout << *array << endl;

  char i = 0;
  while((i += 2) < 10)
    cout << "i: " << i << endl;

  i = 10;
  do std::cout << "i = " << i <<'\n';
  while((i-= 2) > 0);

  const char *st = "hello world\0";
  const char str[] = "hello world\0";
  const char s[] = { 'h', '.', '.', '.', '\0' };
  string hello = "hello world";

  string hello_1 = "hello";
  string world_1 = " world";

  cout << "first: "  << st << endl;
  cout << "second: " << str << endl;
  cout << "third: "  << s << endl;
  cout << "fourth: " << hello << endl;

  cout << hello_1 + world_1 << endl;
  //cout << st + str << endl;

  vector <int> vect(10);
  const int arr[3] = { 10, 20, 30 };

  vect.insert(vect.begin(), arr, arr + 2);
  vect.insert(vect.begin() + 2, 23);
  cout << vect.at(0) << endl;
  cout << vect.at(1) << endl;
  cout << vect.at(2) << endl;
  cout << vect.at(3) << endl;

  std::cout << "index 1: " << vect[1] <<'\n';
  //std::cout << "pointer + 1: " << *(vect + 1) <<'\n';

  vect.push_back(40);
  cout << vect.back() << endl;
  cout << vect.front() << endl;

  print_str("print_str");
  print_str(.0, .12);
  const char *err = "error";
  try_catch((const char *)err);

  unsigned short int v = 0xaf23;
  unsigned short int &h = v;
  v = 10;

  std::cout << "ref: " << h <<'\n';
  std::cout << "src: " << v <<'\n';

  T t((short int)v, (float)v);
  std::cout << "intermediator" << '\n';
  t.set_v((short int)v, (float)v);
  std::cout << "v_s: " << t.print_f() << '\n';
  std::cout << "end of listing" << '\n';

  return 0;
}

void print_str(string word) {
  std::cout << "input word: " << word << '\n';
}

void print_str(float v, float g) {
  std::cout << "input value: " << v + g << '\n';
}

void try_catch(const char *err) {
  try {
    throw((const char *)err);
  } catch(int n) {
    std::cout << "err: (really)" << n << '\n';
  }
}
