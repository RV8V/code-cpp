#include <iostream>

class Anonymous {
  enum class tag { number, text };
  union { int i{0}; std::string str; };
  tag m_type{tag::number};
public:
  Anonymous() {}
  ~Anonymous() {
    if ((*this).m_type == tag::text)
      str.~basic_string();
  }
  Anonymous &operator=(const Anonymous &obj) {
    if ((*this).m_type == tag::text && obj.m_type == tag::text) {
      str = obj.str;
      return *this;
    }
    if ((*this).m_type == tag::text)
      str.~basic_string();
    if (obj.m_type == tag::number) (*this).i = obj.i;
    if (obj.m_type == tag::text) new(&str)std::string(obj.str);
    (*this).m_type == obj.m_type;
    return *this;
  }
  int get_number() const {
    if ((*this).m_type == tag::number) return (*this).i;
    return 0;
  }
  std::string get_text() const {
    if ((*this).m_type == tag::text) return str;
    return "";
  }
  void set_number(int value) {
    if ((*this).m_type == tag::text) {
      str.~basic_string();
      (*this).m_type = tag::number;
    }
    (*this).i = value;
  }
  void set_text(const std::string &value) {
    if ((*this).m_type == tag::text) str = value;
    else {
      new(&str)std::string{value};
      (*this).m_type = tag::text;
    }
  }
};

int main(int argc, char const **argv) {
  struct Anonymous a;
  a.set_text("test value");
  a.set_number(1);
  return 0;
}
