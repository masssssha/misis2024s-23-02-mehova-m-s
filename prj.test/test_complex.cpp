#include <complex/complex.hpp>
#include <iostream>

typedef Complex Rat;

int main() {
  Rat a(2, 4);
  std::cout << a.separator << " " << Complex::separator;
}