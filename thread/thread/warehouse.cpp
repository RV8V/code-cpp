#include "warehouse.hpp"

Warehouse g_first_warehouse;
Warehouse g_second_warehouse;

timed_mutex g_first_tmutex;
timed_mutex g_second_tmutex;

auto suplier = []() {
  for (unsigned short i = 0, j = 0; i < 10 || j < 10;) {
    if (i < 10 && g_first_tmutex.try_lock()) {
      g_first_warehouse.accept_item(i);
      i++;
      g_first_tmutex.unlock();
    }

    if (j < 10 && g_second_tmutex.try_lock()) {
      g_second_warehouse.accept_item(j);
      j++;
      g_second_tmutex.unlock();
    }

    this_thread::yield();
  }

  g_first_tmutex.lock();
  g_second_tmutex.lock();
  g_first_warehouse.accept_item(special_item);
  g_second_warehouse.accept_item(special_item);
  g_first_tmutex.unlock();
  g_second_tmutex.unlock();
};

auto consumer = []() {
  while("consumer wants to have an item") {
    g_first_tmutex.lock();
    int i = 0;
    int item;
    try {
      item = g_first_warehouse.handle_last_item();
    }
    catch(const Ware_house_empty&) {
      cout << "warehouse is empty" << endl;
    }

    g_first_tmutex.unlock();
    if (item == special_item) break;
    cout << "got new item: " << item << "!\n";
    this_thread::sleep_for(chrono::seconds(4));
  }
};

auto the_same_consumer = []() {
  while("still wants to have item, angry") {
    int item = 0;
    if (g_first_tmutex.try_lock_for(chrono::seconds(2))) {
      try {
        item = g_first_warehouse.handle_last_item();
        //cout << "got element from 1 warehouse" << endl;
      }
      catch(const Ware_house_empty&) {
        cout << "warehouse is empty, consumer is man" << endl;
      }
      g_first_tmutex.unlock();
    } else {
      cout << "first warehouse is always buzy!!!" << endl;
      g_second_tmutex.lock();

      try {
        item = g_second_warehouse.handle_last_item();
        //cout << "got element from 2 warehouse" << endl;
      }
      catch(const Ware_house_empty&) {
        cout << "second warehouse is empty" << endl;
      }
    }

    if (item == special_item) break;
    cout << "at last consumer got new item: " << item << endl;
    this_thread::sleep_for(chrono::seconds(4));
  }
};

int main(int, const char**) {
  thread supplier_thread(suplier);
  thread consumer_thread(consumer);
  thread the_same_consumer_thread(the_same_consumer);

  supplier_thread.join();
  consumer_thread.join();
  the_same_consumer_thread.join();
  return EXIT_SUCCESS;
}
