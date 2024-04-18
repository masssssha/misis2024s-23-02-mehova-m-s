#ifndef MAKE_VECTOR_HPP
#define MAKE_VECTOR_HPP

#include <vector>
#include <string>

template <typename T> std::vector<T> Make_Vector(int& count) {
  std::vector<T> test(count);
  for (int i = 0; i < count; i++) {
    test[i] = T(i);
  }
  return test;
}

template <> std::vector<std::string> Make_Vector(int& count) {
  std::vector<std::string> test(count);
  for (int i = 0; i < count; i++) {
    test[i] = std::string(i + 'a', i);
  }
  return test;
}

#endif