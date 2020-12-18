#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <unistd.h>

using namespace std;

struct Line;

void foo(vector<Line>&, mutex&);
void bar(vector<Line>&, mutex&);
void view(vector<Line>&, mutex&);

struct Line {
  Line(char* name, char* lastname, int year): name((char*)name), lastname((char*)lastname), year(year) {}
  int year;
  char* name;
  char* lastname;
};

int main(int, const char**) {
  vector<Line> db;
  #pragma GCC diagnostic ignored "-Wwrite-strings"
  db.push_back(Line("Nikola", "Tesla", 1856));
  #pragma GCC diagnostic ignored "-Wwrite-strings"
  db.push_back(Line("Albert", "Einstein", 1879));
  #pragma GCC diagnostic ignored "-Wwrite-strings"
  db.push_back(Line("Bill", "Gates", 1955));
  #pragma GCC diagnostic ignored "-Wwrite-strings"
  db.push_back(Line("Stive", "Jobs", 1955));
  #pragma GCC diagnostic ignored "-Wwrite-strings"
  db.push_back(Line("Mark", "Zuckerberg", 1984));

  mutex mtx;

  thread tr1(foo, ref(db), ref(mtx));
  thread tr2(bar, ref(db), ref(mtx));
  thread tr3(view, ref(db), ref(mtx));

  tr1.detach();
  tr2.detach();
  tr2.join();

  return 0;
}

void foo(vector<Line>& db, mutex& mtx) {
  int i = 0;
  while("mutex& mtx and & vector<Line>& db") {
    mtx.lock();
    db.at(i).year = 2000 + i;
    if (i++ == 5) return;
    mtx.unlock();
  }
  return;
}

void bar(vector<Line>& db, mutex& mtx) {
  int i = 0;
  while("mutex& mtx and & vector<Line>& db") {
    mtx.lock();
    db.at(i).year = 1900 + i;
    if (i++ == 5) return;
    mtx.unlock();
  }
  return;
}

void view(vector<Line>& db, mutex& mtx) {
  while("mutex& mtx and & vector<Line>& db") {
    lock_guard<mutex> lock(mtx);
    cout << "view: " << endl;
    for (auto& row : db) cout << row.year << ", ";
    cout << endl;
    usleep(1000000);
  }
  return;
}
