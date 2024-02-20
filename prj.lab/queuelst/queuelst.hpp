#ifndef QUEUELST_HPP
#define QUEUELST_HPP
#include <cstddef>
#include <complex/complex.hpp>

class QueueLst {
public:
  QueueLst() = default;
  QueueLst(const QueueLst& x);
  ~QueueLst();
  const Complex& Top();
  void Push(const Complex& x);
  void Pop() noexcept;
  bool IsEmpty() noexcept;
  QueueLst& operator=(const QueueLst& x);
  void Clear() noexcept;
private:
  struct Node {
    Complex v;
    Node* next = nullptr;
  };
  Node* head_ = nullptr;
  Node* tail_ = nullptr;
};

#endif