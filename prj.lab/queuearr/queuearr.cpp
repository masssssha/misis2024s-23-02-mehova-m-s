#include <complex/complex.hpp>
#include "queuearr.hpp"


QueueArr::QueueArr(QueueArr&& x) noexcept {
  size_ = x.size_;
  i_head_ = x.i_head_;
  i_tail_ = x.i_tail_;
  count = x.count;
  data_ = std::move(x.data_);
  x.data_ = nullptr;
}

QueueArr& QueueArr::operator=(QueueArr&& x) noexcept {
  if (data_ != x.data_) {
    size_ = x.size_;
    i_head_ = x.i_head_;
    i_tail_ = x.i_tail_;
    count = x.count;
    data_ = std::move(x.data_);
    x.data_ = nullptr;
  }
  return *this;
}

QueueArr& QueueArr::operator=(const QueueArr& x) {
  if (data_ != x.data_) {
    if (size_ <= x.size_) {
      data_ = std::make_unique<Complex[]>(x.size_);
    }
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

QueueArr::QueueArr(const QueueArr& x) {
  size_ = x.size_;
  i_head_ = x.i_head_;
  i_tail_ = x.i_tail_;
  count = x.count;
  data_ = std::make_unique<Complex[]>(x.size_);
  for (int i = 0; i < size_; i++) {
    data_[i] = x.data_[i];
  }
}

QueueArr::~QueueArr() {
  data_ = nullptr;
  size_ = 0;
  count = 0;
  i_head_ = -1;
  i_tail_ = -1;
}

void QueueArr::Pop() noexcept {
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

void QueueArr::Clear() noexcept {
  i_head_ = -1;
  i_tail_ = -1;
  count = 0;
}

Complex& QueueArr::Top() {
  if (count != 0) {
    return data_[i_head_%size_];
  }
  else {
    throw std::logic_error("QueueArr is empty");
  }
}

const Complex& QueueArr::Top() const {
  if (count != 0) {
    return data_[i_head_&size_];
  }
  else {
    throw std::logic_error("QueueArr is empty");
  }
}

bool QueueArr::IsEmpty() noexcept {
  if (count == 0) {
    return true;
  }
  else {
    return false;
  }
}

void QueueArr::Push(const Complex& x) {
  if (size_ != 0) {
    if (count + 1 <= size_) {
      if (count == 0) {
        i_head_ += 1;
      }
      i_tail_ += 1;
      data_[(i_tail_)%size_] = x;
      count += 1;
    }
    else {
      QueueArr temp(*this);
      data_ = std::make_unique<Complex[]>(size_*2);
      for (int i = 0; i < size_ - i_head_; i++) {
        data_[i] = temp.data_[i + i_head_];
      }
      for (int i = 0; i < i_tail_%size_; i++) {
        data_[size_ - i_head_+1] = temp.data_[i];
      }
      i_head_ = 0;
      data_[size_ + 1] = x;
      i_tail_ += 1;
      count += 1;
      size_ *= 2;
    }
  }
  if (size_ == 0) {
    data_ = std::make_unique<Complex[]>(8);
    size_ = 8;
    i_tail_ += 1;
    i_head_ += 1;
    count += 1;
    data_[i_tail_] = x;
  }
  //std::cout << "PUSH " << i_head_ << " " << data_[i_head_%size_] << "   " << i_tail_ << " " << data_[i_tail_%size_] << std::endl;
}