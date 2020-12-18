#include <iostream>
#include <sstream>

using namespace std;
using std::runtime_error;

void save_logs(const int&, const string&, const string&);
class makestring;

int main()
{
  cout << "enter integer value: " << endl;
  int integer;
  cin >> integer;

  stringstream sso;
  sso << integer;
  string result;
  sso >> result;

  string str = "23";
  stringstream sso;
  sso << str;
  int num;
  sso >> num;
  std::cout << "number: " << num + 2 << '\n';

  string str, newstring = "";
  stringstream my_string;
  my_string << "hello world, this is a test string" << endl;
  while(my_string >> str)
  {
    newstring += str + " ";
  }
  cout << "str: " << newstring << endl;

  stringstream test_str;
  test_str.str("hello world!");
  cout << "str: " << test_str.str() << endl;

  stringstream test_string;
  int val = 3350;
  double dob = 123.3;
  test_string << val << " " << dob;

  string first, second;
  test_string >> first >> second;
  cout << "read 1: " << first << " " << "read 2: " << second << endl;

  stringstream test;
  test << "2810 134";
  int v1, v2;
  test >> v1 >> v2;
  cout << "v1: " << v1 << " " << "v2: " << v2 << endl;

  stringstream testing;
  testing << string("hello");
  testing.str("");
  testing << string("world");
  cout << testing.str() << endl;

  testing.str(string());
  testing.str(string("hello world"));
  cout << testing.str() << endl;

  stringstream sso{"test"};
  cout << sso.str() << endl;

  int n(0);
  string str("123");
  stringstream convert(str);
  convert >> n;
  cout << n << endl;

  try
  {
    const string test = string("testing");
    makestring make(&test);
    make << "testing";
    save_logs(10, "test", "value");
  }
  catch(const stringstream &sso)
  {
    cout << sso.str() << endl;
    return 1;
  }
  catch(const runtime_error &re)
  {
    return 2;
  }
  return 0;
}

void save_logs(const int& id, const string& s1, const string& s2)
{
  stringstream sso;
  sso << "operation with id = " << id << " failed, because s1 (" << s1 << ") is incompatible with s2 (" \
      << s2 << ")";
  throw runtime_error(sso.str());
}

class makestring
{
public:
  makestring(const string &str)
  {
    this->m_string << str;
  };
  template<class T>
  makestring& operator<<(const T& arg)
  {
    this->m_string << arg;
    return *this;
  }
  operator string() const {
    return this->m_string.str();
  }
private:
  stringstream m_string{};
};
