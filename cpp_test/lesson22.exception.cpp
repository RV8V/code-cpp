#include <iostream>
#include <ctime>
#include <cstdlib>

#define TEST_A 10
#define TEST_B 5
#define RANDOM 4
#define CH_LENGTH 100

void test_example_a(void);
void test_example_b(void);
void test_example_c(void);
bool open(bool);
void close(void);
bool write(bool);
bool read(bool);

namespace test_example_1 {
  std::vector<int> v;
  void test_example_a(void) { v[0] = RANDOM; }
  void test_example_b(void) try { v[0] = RANDOM; } catch(..) { std::cout << "..." << std::endl; }
  void test_example_c(void) { try { v.at(RANDOM) = RANDOM; } catch(std::out_of_range &ex) { std::cout << ex.what() << std::endl; } }

  enum class err_code { NOERROR = 0, OPEN, CLOSE, READ, WRITE, APPEND, END };
  bool open(bool v) { return v };
  void close(void) {};
  bool write(bool v) { return v };
  bool read(bool v) { return v };
  enum err_code get_data(void) { if (!open(true)) { close(); return err_code::OPEN; } if (!write(true)) { close(); return err_code::WRITE; } if (!read(true)) { close(); return err_code::READ; } return err_code::NOERROR; }
  void test(void) { enum err_code res; res = get_data(); if (res != err_code::NOERROR) /*logging*/ }
};

namespace test_example_2 {
  enum class err_code { OPEN, CLOSE, READ, WRITE, APPEND, END };
  bool open(bool v) { if (!v) throw err_code::OPEN; };
  void close(void) {};
  bool write(bool v) { if (!v) throw err_code::WRITE; };
  bool read(bool v) { if (!v) throw err_code::READ; };
  void append(void) {};
  bool get_data(void) try { open(true); write(true); read(true); append(false); close(); return 0; } catch(err_code &ex) { close(); if (ex == err_code::APPEND) return err_code::APPEND; } catch(...) { std::cout << "..." << std::endl; }
  void test(void) { bool get; get = get_data(); if (!get) /*logging*/ return 1; }
};

namespace test_example_3 {
  enum class do_not_forget { DEADLOC };
  void test(void) { char* p_ch = new char[CH_LENGTH]; if(1) { delete[] p_ch; return; } /*...*/ if(1) { delete[] p_ch; return; } delete[] p_ch; }
  void test_a(void) { char* p_ch = new char[CH_LENGTH]; try { if(1) throw do_not_forget::DEADLOC; /*...*/ if(1) throw do_not_forget::DEADLOC; } throw do_not_forget::DEADLOC; } catch(do_not_forget::DEADLOC &ex) { if(ex == do_not_forget::DEADLOC) delete[] p_ch } catch(...) { std::cout << "unexpected behavior" << std::endl; } }
};

namespace test_example_4 {
  void test_a(void) { std::cout << "enter test_a" << std::endl; throw test_example_3::DEADLOC; std::cout << "out of test_a" << std::endl; }
  void test_b(void) { std::cout << "enter test_b" << std::endl; test_a(); std::cout << "out of test_b" << std::endl; }
  void test_c(void) { std::cout << "enter test_c" << std::endl; test_b(); std::cout << "out of test_c" << std::endl; }
  void test_d(void) { std::cout << "enter test_d" << std::endl; test_c(); std::cout << "out of test_d" << std::endl; }
  void try_to_catch_err(void) try { test_d(); } catch(...) { std::cout << "catched!" << std::endl; }
};

int main(int argc, char const **argv) {
  try {
    srand(time(NULL)); char i = 10;
    do {
      if (rand() % TEST_B % TEST_A == TEST_B) {
        test_example_1::test_example_b();
        test_example_1::test_example_a();
        test_example_2::get_data();
      };
      if (rand() % TEST_A - TEST_B == RANDOM) throw (const char*)"1";
      else throw "hello world";
      if (rand() % TEST_B - TEST_A == RANDOM + RANDOM) test_example_4::try_to_catch_err();
      else test_example_3::test_a();
    } while(i-- > 0);
  } catch(int &ex) { std::cout << "int -> " << ex << std::endl; }
  catch(const char* &ex) { std::cout << "char* -> " << ex << std::endl; }
  catch(...) { std::cout << "<- unknown -> " << std::endl; }
  return 0;
}
