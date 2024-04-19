#ifndef MAKE_VECTOR_HPP
#define MAKE_VECTOR_HPP

#include <vector>
#include <string>

template <typename T> void Make_Vector(std::vector<T>& x, int& count) {
  x.resize(count);
  for (int i = 0; i < count; i++) {
    x[i] = T(i);
  }
}

/*template <> void Make_Vector<std::string>(std::vector<std::string>& x, int& count) {
  x.resize(count);
  for (int i = 0; i < count; i++) {
    x[i] = std::string(i + 'a', i);
  }
}*/

#endif