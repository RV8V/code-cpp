#ifndef _WAREHOUSE_H_
#define _WAREHOUSE_H_

#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <list>
#include <limits>

using namespace std;

unsigned short int special_item = numeric_limits<unsigned short int>::max();

class Ware_house_empty {
};

class Warehouse {
  list<unsigned short int> m_store;
public:
  void accept_item(unsigned short int item);
  unsigned short int handle_last_item();
};

void Warehouse::accept_item(unsigned short int item) {
  m_store.push_back(item);
}

unsigned short int Warehouse::handle_last_item() {
  if (m_store.empty()) throw Ware_house_empty();
  unsigned short int item = m_store.front();
  cout << "front element is " << item << endl << "and special item is " << special_item << endl;

  if (item != special_item) m_store.pop_front();
  return item;
};

#endif
