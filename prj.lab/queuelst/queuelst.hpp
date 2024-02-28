#ifndef QUEUELST_HPP
#define QUEUELST_HPP
#include <cstddef>
#include <complex/complex.hpp>
#include <utility>

class QueueLst {
public:
  QueueLst() = default;
  QueueLst(const QueueLst& x);
  QueueLst(QueueLst&& x) noexcept;
  ~QueueLst();
  Complex& Top();
  [[nodiscard]] const Complex& Top() const;
  void Push(const Complex& x);
  void Pop() noexcept;
  bool IsEmpty() const noexcept;
  QueueLst& operator=(const QueueLst& x);
  QueueLst& operator=(QueueLst&& x) noexcept;
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