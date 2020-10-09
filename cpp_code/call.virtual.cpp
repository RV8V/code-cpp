#include <iostream>

class Message {
private:
  std::string message;
public:
  Message(std::string msg) {
    this->message = msg;
  }
  virtual std::string get_message(void) {
    return this->message;
  }
};

class BracketsMessage : public Message {
public:
  BracketsMessage(std::string msg): Message(msg) {
  }
  std::string get_message(void) override {
    return "[" + /*BracketsMessage*/::Message::get_message() + "]";
  }
};

class Printer {
public:
  void print_message(Message* msg) {
    std::cout << msg->get_message() << std::endl;
  }
};

int main(int, char const**) {
  Message m("hello");
  BracketsMessage b("hello world");
  Printer p;
  p.print_message(&b);
  return 0;
}
