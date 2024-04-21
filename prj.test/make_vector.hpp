#ifndef MAKE_VECTOR_HPP
#define MAKE_VECTOR_HPP

#include <vector>
#include <string>

template <class T> 
void Make_Vector(std::vector<T>& x, const int count) {
  x.clear();
  x.reserve(count);
  for (int i = 0; i < count; i++) {
    x.emplace_back(i);
  }
}

template <> 
void Make_Vector(std::vector<std::string>& x, const int count) {
  x.clear();
  x.reserve(count);
  for (int i = 0; i < count; i++) {
    x.emplace_back(std::to_string(i));
  }
}

#endif