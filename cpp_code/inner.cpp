#include <iostream>

class Image {
private:
  class Pixel {
  public:
    Pixel(): r{0}, b{0}, g{0} {}
    Pixel(int r, int g, int b) {
      this->r = r;
      this->g = g;
      this->b = b;
    }
    std::string get_info() {
      return "Pixel r: " + std::to_string(this->r) + " b: " + std::to_string(this->b) + " g: " + std::to_string(this->g);
    }
  private: int r, g, b;
  };
public:
  Pixel* pixels;
  int size;
  Image() {
    this->pixels = nullptr;
    this->size = 0;
  }
  Image(int value) {
    this->size = value;
    this->pixels = new Pixel[value];
    Pixel* move;
    int i = 0;
    for (move = this->pixels; move < this->pixels + this->size; ++move) {
      std::cout << "address: " << move << std::endl;
      *move = Pixel(i++, i + 2, i + 3);
    }
  }
  ~Image() {
    delete[] this->pixels;
    this->pixels = nullptr;
  }
  void print_info(void) {
    Pixel* move = this->pixels;
    for (move = this->pixels; move != this->pixels + this->size; ++move)
      std::cout << "info: " << move->get_info() << std::endl;
  }
};

int main(int, char const**) {
  Image image(2);
  image.print_info();
  return 0;
}
