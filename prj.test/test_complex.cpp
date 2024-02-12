#include <complex/complex.hpp>
#include <iostream>

typedef Complex Rat;

int main() {
  Rat a(2, -5);
  std::cout << (a * a) << std::endl;
}