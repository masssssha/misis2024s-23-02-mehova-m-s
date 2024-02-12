#ifndef STACKLST_HPP
#define STACKLST_HPP
#include <iosfwd>
#include <stdexcept>
#include <cstddef>
#include <complex/complex.hpp>

class StackLst {
public:
  struct Node {
    Complex v;
    Node* next = nullptr;
  };
  Node* head_ = nullptr;
  StackLst() = default;
  StackLst(const StackLst& x);
  ~StackLst();
  const Complex& Top();
  void Push(const Complex& x);
  void Pop() noexcept;
  bool IsEmpty() noexcept;
  StackLst& operator=(const StackLst& x);
};

#endif