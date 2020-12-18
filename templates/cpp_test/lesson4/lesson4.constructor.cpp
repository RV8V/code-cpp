#include <iostream>
#include <string.h>
#include "lesson4.constructor.h"

namespace cpp_ns {
  string::string(): mp_str(nullptr), m_length(0) {
    std::cout << __FUNCTION__ << std::endl;
  };
  string::string(const char* p_str): mp_str(nullptr), m_length(0) {
    if (p_str != nullptr) {
      (*this).m_length = strlen(p_str);
      (*this).mp_str = new char[m_length + 1];
      memcpy((*this).mp_str, p_str, m_length + 1);
    }
  };
  string::~string() {
    if ((*this).mp_str != nullptr) {
      delete[]((*this).mp_str);
      (*this).m_length = 0;
    }
  };
  string &string::operator=(const string &r_obj) {
    if (this == &r_obj) return *this;
    if ((*this).mp_str != nullptr) {
      delete[]((*this).mp_str);
      (*this).m_length = 0;
    }
    (*this).m_length = r_obj.m_length;
    (*this).mp_str = new char[m_length + 1];
    memcpy((*this).mp_str, r_obj.mp_str, m_length + 1);
    return *this;
  }
  string &string::operator=(const double d) const {
    std::cout << "double: " << d << std::endl;
  }
  const char* string::c_str() const {
    /*(*this).m_length = 0*/
    return (*this).mp_str;
  };
};
