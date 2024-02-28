#ifndef STACKLST_HPP
#define STACKLST_HPP
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <utility>
#include <complex/complex.hpp>

class StackLst {
public:
  StackLst() = default;
  StackLst(const StackLst& x);
  StackLst(StackLst&& x) noexcept;
  ~StackLst();
  Complex& Top();
  const Complex& Top() const;
  void Push(const Complex& x);
  void Pop() noexcept;
  bool IsEmpty() noexcept;
  StackLst& operator=(const StackLst& x);
  StackLst& operator=(StackLst&& x) noexcept;
  void Clear() noexcept;
private:
  struct Node {
    Complex v;
    Node* next = nullptr;
  };
  Node* head_ = nullptr;
};

#endif