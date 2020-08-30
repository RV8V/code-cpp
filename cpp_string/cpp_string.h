#ifndef STRING_TEST_H
#define STRING_TEST_H

namespace cpp_ns {
  class string {
  public:
    string();
    string(const char*);
    ~string();

    // string(const string &) = delete;
    string &operator=(const string &);
    string &operator=(const double) const;
    // string &operator=(const string &) = delete;
    /*
     * mp_str_1 = mp_str_2;
     * m_length_1 = m_length_2;
    */
    // string(string &&) = delete;
    // string(&operator=(const string &&)) = delete;
    bool operator>(const string &) { return true; };
    bool operator<(const string &) { return false; };
    const char* c_str() const;
  private:
    char* mp_str = nullptr;
    size_t m_length = 0;
  };
};

#endif
