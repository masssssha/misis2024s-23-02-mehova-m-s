#ifndef QUEUEARRT_HPP
#define QUEUEARRT_HPP
#include <cstddef>
#include <utility>
#include <memory>
#include <stdexcept>
#include <algorithm>
#include <iostream>

template<class T>
class QueueArrT {
public:
  QueueArrT() = default;
  QueueArrT(const QueueArrT& x);
  QueueArrT(QueueArrT&& x) noexcept;
  ~QueueArrT() = default;
  QueueArrT& operator=(const QueueArrT& x);
  QueueArrT& operator=(QueueArrT&& x) noexcept;
  T& Top();
  const T& Top() const;
  void Push(const T& x);
  void Pop() noexcept;
  bool IsEmpty() noexcept;
  void Clear() noexcept;
private:
  std::unique_ptr<T[]> data_ = nullptr;
  std::ptrdiff_t size_ = 0;
  std::ptrdiff_t i_head_ = -1;
  std::ptrdiff_t i_tail_ = -1;
  std::ptrdiff_t count = 0;
};

template<class T>
QueueArrT<T>::QueueArrT(QueueArrT&& x) noexcept {
  size_ = x.size_;
  i_head_ = x.i_head_;
  i_tail_ = x.i_tail_;
  count = x.count;
  std::swap(data_, x.data_);
  x.data_ = nullptr;
}

template<class T>
QueueArrT<T>& QueueArrT<T>::operator=(QueueArrT&& x) noexcept {
  if (data_ != x.data_) {
    size_ = x.size_;
    i_head_ = x.i_head_;
    i_tail_ = x.i_tail_;
    count = x.count;
    std::swap(data_, x.data_);
    x.data_ = nullptr;
  }
  return *this;
}

template<class T>
QueueArrT<T>& QueueArrT<T>::operator=(const QueueArrT& x) {
  if (data_ != x.data_) {
    if (size_ <= x.size_) {
      data_ = std::make_unique<T[]>(x.size_);
    }
    //auto r = std::copy(x.data_, x.data_ + size_, data_);
    size_ = x.size_;
    for (int i = 0; i < size_; i++) {
      data_[i] = x.data_[i];
    }
    i_head_ = x.i_head_;
    i_tail_ = x.i_tail_;
    count = x.count;
  }
  return *this;
}


//ready

template<class T>
QueueArrT<T>::QueueArrT(const QueueArrT& x) {
  size_ = x.size_;
  i_head_ = x.i_head_;
  i_tail_ = x.i_tail_;
  count = x.count;
  data_ = std::make_unique<T[]>(x.size_);
  for (int i = 0; i < size_; i++) {
    data_[i] = x.data_[i];
  }
}

template<class T>
void QueueArrT<T>::Pop() noexcept {
  if (count <= 1) {
    i_head_ = -1;
    i_tail_ = -1;
    count = 0;
  }
  if (count != 0) {
    i_head_ += 1;
    count -= 1;
  }
  //std::cout << "POP " << i_head_ << " " << data_[i_head_%size_] << "   " << i_tail_ << " " << data_[i_tail_%size_] << " COUNT " << count << std::endl;
}

template<class T>
void QueueArrT<T>::Clear() noexcept {
  i_head_ = -1;
  i_tail_ = -1;
  count = 0;
}

template<class T>
T& QueueArrT<T>::Top() {
  if (count != 0) {
    return data_[i_head_ % size_];
  }
  else {
    throw std::logic_error("QueueArrT is empty");
  }
}

template<class T>
const T& QueueArrT<T>::Top() const {
  if (count != 0) {
    return data_[i_head_ & size_];
  }
  else {
    throw std::logic_error("QueueArrT is empty");
  }
}

template<class T>
bool QueueArrT<T>::IsEmpty() noexcept {
  if (count == 0) {
    return true;
  }
  else {
    return false;
  }
}

template<class T>
void QueueArrT<T>::Push(const T& x) {
  if (size_ != 0) {
    if (count + 1 <= size_) {
      if (count == 0) {
        i_head_ += 1;
      }
      i_tail_ += 1;
      data_[(i_tail_) % size_] = x;
      count += 1;
    }
    else {
      //QueueArrT temp(*this);
      auto data = std::make_unique<T[]>(size_ * 2);
      //data_ = std::make_unique<T[]>(size_*2);
      for (int i = 0; i < size_ - i_head_; i++) {
        data[i] = data_[i + i_head_];
      }
      for (int i = 0; i < i_tail_ % size_; i++) {
        data[size_ - i_head_ + 1] = data_[i];
      }
      std::swap(data, data_);
      data_[size_ + 1] = x;
      i_head_ = 0;
      i_tail_ += 1;
      count += 1;
      size_ *= 2;
    }
  }
  if (size_ == 0) {
    data_ = std::make_unique<T[]>(8);
    size_ = 8;
    i_tail_ += 1;
    i_head_ += 1;
    count += 1;
    data_[i_tail_] = x;
  }
  //std::cout << "PUSH " << i_head_ << " " << data_[i_head_%size_] << "   " << i_tail_ << " " << data_[i_tail_%size_] << std::endl;
}

#endif