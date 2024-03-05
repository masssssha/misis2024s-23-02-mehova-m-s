#ifndef QUEUELSTPR_HPP
#define QUEUELSTPR_HPP
#include <cstddef>
#include <utility>

class QueueLstPr {
public:
  QueueLstPr() = default;
  QueueLstPr(const QueueLstPr& x);
  QueueLstPr(QueueLstPr&& x) noexcept;
  ~QueueLstPr();
  float& Top();
  [[nodiscard]] const float& Top() const;
  void Push(const float& x);
  void Pop() noexcept;
  bool IsEmpty() const noexcept;
  QueueLstPr& operator=(const QueueLstPr& x);
  QueueLstPr& operator=(QueueLstPr&& x) noexcept;
  void Clear() noexcept;
private:
  struct Node {
    float v = 0;
    Node* next = nullptr;
  };
  Node* head_ = nullptr;
};

#endif