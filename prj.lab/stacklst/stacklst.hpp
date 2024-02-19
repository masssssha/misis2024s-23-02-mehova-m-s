#ifndef STACKLST_HPP
#define STACKLST_HPP
#include <cstddef>
#include <complex/complex.hpp>

class StackLst {
public:
  StackLst() = default;
  StackLst(const StackLst& x);
  ~StackLst();
  const Complex& Top();
  void Push(const Complex& x);
  void Pop() noexcept;
  bool IsEmpty() noexcept;
  StackLst& operator=(const StackLst& x);
  void Clear() noexcept;
private:
  struct Node {
    Complex v;
    Node* next = nullptr;
  };
  Node* head_ = nullptr;
};

#endif