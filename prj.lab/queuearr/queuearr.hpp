#ifndef QUEUEARR_HPP
#define QUEUEARR_HPP
#include <cstddef>

struct Complex;

class QueueArr {
public:
  QueueArr() = default;
  QueueArr(const QueueArr& x);
  ~QueueArr();
  QueueArr& operator=(const QueueArr& x);
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
  std::ptrdiff_t i_tail_ = -1;
  std::ptrdiff_t count = 0;
};

#endif