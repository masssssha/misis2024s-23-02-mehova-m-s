#include <complex/complex.hpp>
#include <iostream>
#include <utility>

typedef Complex Rat;

int main() {
  Complex a(5, 1);
  Complex b;
  b = std::move(a);
  std::cout << b;
}