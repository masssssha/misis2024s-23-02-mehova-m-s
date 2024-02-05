#ifndef STACKARR_HPP
#define STACKARR_HPP
#include <iosfwd>
#include <complex/complex.hpp>
#include <stdexcept>

class StackArr {
public:
  StackArr() = default;
  StackArr(const StackArr& x);
  ~StackArr();
  StackArr& operator=(const StackArr& x);
  const Complex& Top();
  void Push(const Complex& x);
  void Pop() noexcept;
  bool IsEmpty() noexcept;
private:
  Complex* data_ = nullptr;
  std::ptrdiff_t size_ = 0;
  std::ptrdiff_t i_head_ = -1;
};

#endif