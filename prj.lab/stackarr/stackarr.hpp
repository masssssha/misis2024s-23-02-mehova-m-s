#ifndef STACKARR_HPP
#define STACKARR_HPP
#include <complex/complex.hpp>
#include <cstddef>
#include <utility>
#include <stdexcept>
#include <algorithm>
#include <iostream>

struct Complex;

class StackArr {
public:
  StackArr() = default;
  StackArr(const StackArr& x);
  StackArr(StackArr&& x) noexcept;
  ~StackArr();
  StackArr& operator=(const StackArr& x);
  StackArr& operator=(StackArr&& x) noexcept;
  Complex& Top();
  const Complex& Top() const;
  void Push(const Complex& x);
  void Pop() noexcept;
  bool IsEmpty() noexcept;
  void Clear() noexcept;
private:
  Complex* data_ = nullptr;
  std::ptrdiff_t size_ = 0;
  std::ptrdiff_t i_head_ = -1;
};

#endif