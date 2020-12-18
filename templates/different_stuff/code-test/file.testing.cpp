#include <iostream>
#include <cassert>

using namespace std;

template<typename T>
class my_list {
public:
  my_list();
  ~my_list();

  void push_back(T data);
  void pop_front();
  int get_size();
  void clear();

  void push_front(T);
  void pop_back();
  void insert(T, const int);
  void remove_at(const int);

  T& operator[](const int);
  T& operator+(const int);
private:
  template<typename V>
  class node {
  public:
    node* p_next;
    V data;

    node(V data = V(), node* p_next = nullptr) {
      this->data = data;
      this->p_next = p_next;
    }
  };

  node<T>* head = nullptr;
  int size;
};

template<typename T>
my_list<T>::my_list() {
  this->size = 0;
  this->head = nullptr;
}

template<typename T>
void my_list<T>::pop_front() {
  node<T>* temp = this->head;
  this->head = this->head->p_next;
  delete temp;
  --this->size;
}

template<typename T>
void my_list<T>::clear() {
  while(this->size)
    this->pop_front();
}

template<typename T>
void my_list<T>::push_back(T data) {
  if (this->head == nullptr)
    this->head = new node<T>(data);
  else {
    node<T>* current = this->head;
    while(current->p_next != nullptr)
      current = current->p_next;
    current->p_next = new node<T>(data);
  }
  ++this->size;
}

template<typename T>
T& my_list<T>::operator+(const int index) {
  int counter = 0;
  node<T>* current = this->head;
  assert(index < this->size && "no such index in current list");
  while(current != nullptr) {
    if (counter == index)
      return current->data;
    else
      current = current->p_next;
    ++counter;
  }
}

template<typename T>
int my_list<T>::get_size() {
  return this->size;
}

template<typename T>
T& my_list<T>::operator[](const int index) {
  int counter = 0;
  node<T>* current = this->head;
  assert(index < this->size && "no such index in current list");
  while(current != nullptr) {
    if (counter == index)
      return current->data;
    else
      current = current->p_next;
    ++counter;
  }
}

template<typename T>
void my_list<T>::push_front(T data) {
  this->head = new node<T>(data, this->head);
  ++this->size;
}

template<typename T>
void my_list<T>::insert(T data, const int index) {
  if (index == 0)
    this->push_front(data);
  else {
    node<T>* previous = this->head;
    for (int i = 0; i < index - 1; ++i) {
      cout << "fails here, why" << endl;
      previous = previous->p_next;
    }

    node<T>* new_node = new node<T>(data, previous->p_next);
    previous->p_next = new_node;
    ++this->size;
  }
}

template<typename T>
void my_list<T>::remove_at(const int index) {
  if (index == 0)
    this->pop_front();
  else {
    node<T>* previous = this->head;
    for (int i = 0; i < index - 1; ++i) {
      previous = previous->p_next;
    }

    node<T>* node_to_delete = previous->p_next;
    previous->p_next = node_to_delete->p_next;
    delete node_to_delete;
    --this->size;
  }
}

template<typename T>
void my_list<T>::pop_back() {
  this->remove_at(this->size - 1);
}

template<typename T>
my_list<T>::~my_list() {
  this->clear();
}

int main(int, const char**) {
  my_list<int> list;
  int first = 10, second = 20;
  list.push_back(first);
  list.push_back(second);

  list.push_front(9);

  cout << "size: " << list.get_size() << "\nvalue: " << list[1] << endl;

  int i = list.get_size() - 1;
  do {
    cout << "current value in list -> " << list + i << endl;
  } while(i-- > 0);

  list.pop_front();
  for (int i = 0; i < list.get_size(); ++i)
    cout << "data: " << list + i << endl;

  cout << "list size: " << list.get_size() << endl;
  list.clear();
  cout << "list size: " << list.get_size() << endl;

#ifdef insert_testing
  cout << "insert\n";
  list.insert(80, 2);
  list.insert(34, 1);

  for (int i = 0; i < list.get_size(); ++i)
    cout << "current value -> " << list + i << endl;
#endif

#ifdef remove_at_testing
  list.push_front(102);
  list.push_front(201);

  cout << "remove at\n";
  list.remove_at(0);
  list.remove_at(2);
#endif

  return EXIT_SUCCESS;
}
