#ifndef STACKARRT_HPP
#define STACKARRT_HPP

#include <cstddef>
#include <utility>
#include <stdexcept>
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

template <class T> class StackArrT {
public:
  StackArrT() = default;
  StackArrT(const StackArrT& x);
  StackArrT(StackArrT&& x) noexcept;
  ~StackArrT();
  StackArrT& operator=(const StackArrT& x);
  StackArrT& operator=(StackArrT&& x) noexcept;
  T& Top();
  const T& Top() const;
  void Push(const T& x);
  void Pop() noexcept;
  bool IsEmpty() noexcept;
  void Clear() noexcept;
private:
  T* data_ = nullptr;
  std::ptrdiff_t size_ = 0;
  std::ptrdiff_t i_head_ = -1;
};


template <class T>
StackArrT<T>& StackArrT<T>::operator=(StackArrT&& x) noexcept {
  if (data_ != x.data_) {
    delete[] data_;
    data_ = x.data_;
    size_ = x.size_;
    i_head_ = x.i_head_;
    x.data_ = nullptr;
  }
  return *this;
}

template <class T> 
StackArrT<T>::StackArrT(StackArrT&& x) noexcept {
  delete[] data_;
  data_ = x.data_;
  size_ = x.size_;
  i_head_ = x.i_head_;
  x.data_ = nullptr;
}

template <class T> 
StackArrT<T>::StackArrT(const StackArrT& x) {
  size_ = x.size_;
  i_head_ = x.i_head_;
  data_ = new T[x.size_];
  auto rat = std::copy(x.data_, x.data_ + size_, data_);
}

template<class T>
StackArrT<T>::~StackArrT() {
  delete[] data_;
  data_ = nullptr;
  size_ = 0;
}

template<class T>
T& StackArrT<T>::Top() {
  if (i_head_ == -1) {
    throw std::logic_error("StackArr is empty");
  }
  return data_[i_head_];
}

template<class T>
const T& StackArrT<T>::Top() const {
  if (i_head_ == -1) {
    throw std::logic_error("StackArr is empty");
  }
  return data_[i_head_];
}

template<class T>
void StackArrT<T>::Push(const T& x) {
  if (i_head_ + 1 < size_) {
    i_head_ += 1;
    data_[i_head_] = x;
  }
  else {
    if (size_ == 0) {
      data_ = new T[8];
      i_head_ += 1;
      data_[i_head_] = x;
      size_ = 8;
    }
    else {
      T* new_data_ = new T[size_ * 2];
      auto rat = std::copy(data_, data_ + size_, new_data_);
      i_head_ += 1;
      *(new_data_ + i_head_) = x;
      size_ *= 2;
      delete[] data_;
      data_ = new_data_;
    }
  }
}

template<class T>
void StackArrT<T>::Pop() noexcept {
  if (i_head_ != -1) {
    i_head_ -= 1;
  }
}

template<class T>
bool StackArrT<T>::IsEmpty() noexcept {
  if (i_head_ == -1) {
    return true;
  }
  else {
    return false;
  }
}

template<class T>
StackArrT<T>& StackArrT<T>::operator=(const StackArrT& x) {
  if (data_ != x.data_) {
    if (size_ <= x.size_) {
      delete[] data_;
      data_ = new T[x.size_];
    }
    size_ = x.size_;
    auto rat = std::copy(x.data_, x.data_ + size_, data_);
    //}
    /*else {
      for (int i = 0; i < x.size_; i++) {
        data_[i] = x.data_[i];
      }
      size_ = x.size_;
    }*/
    i_head_ = x.i_head_;
  }
  return *this;
}

template<class T>
void StackArrT<T>::Clear() noexcept {
  i_head_ = -1;
}

#endif