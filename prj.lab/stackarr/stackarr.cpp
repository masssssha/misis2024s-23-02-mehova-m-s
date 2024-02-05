#include <stackarr/stackarr.hpp>
#include <iostream>
#include <algorithm>

StackArr::StackArr(const StackArr& x) : size_(x.size_) {
  data_ = new Complex[x.size_];
  auto rat = std::copy(x.data_, x.data_ + size_, data_);
}

StackArr::~StackArr() {
  delete[] data_;
  data_ = nullptr;
  size_ = 0;
}

const Complex& StackArr::Top() {
  if (i_head_ != -1) {
    return data_[i_head_];
  }
}

void StackArr::Push(const Complex& x) {
  if (size_ == 0) {
    data_ = new Complex[8];
    i_head_ += 1;
    data_[i_head_] = x;
    size_ = 8;
  }
  if (i_head_ + 1 < size_) {
    i_head_ += 1;
    data_[i_head_] = x;
  }
  else {
    Complex* new_data_ = new Complex[size_ * 2];
    auto rat = std::copy(data_, data_ + size_, new_data_);
    i_head_ += 1;
    *(new_data_ + i_head_) = x;
    size_ *= 2;
    delete[] data_;
    data_ = new_data_;
  }
}

void StackArr::Pop() noexcept {
  if (i_head_ != -1) {
    i_head_ -= 1;
  }
}

bool StackArr::IsEmpty() noexcept {
  if (size_ == 0) {
    return true;
  }
  else {
    return false;
  }
}

StackArr& StackArr::operator=(const StackArr& x) {
  if (size_ <= x.size_) {
    size_ = x.size_;
    data_ = new Complex[size_];
    auto rat = std::copy(x.data_, x.data_ + size_, data_);
  }
  else {
    for (int i = 0; i < x.size_; i++) {
      data_[i] = x.data_[i];
    }
    size_ = x.size_;
  }
  i_head_ = x.i_head_;
  return *this;
}