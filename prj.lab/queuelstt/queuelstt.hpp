#ifndef QUEUELSTT_HPP
#define QUEUELSTT_HPP
#include <cstddef>
#include <utility>
#include <stdexcept>
#include <iostream>

template<class T>
class QueueLstT {
public:
  QueueLstT() = default;
  QueueLstT(const QueueLstT& x);
  QueueLstT(QueueLstT&& x) noexcept;
  ~QueueLstT();
  T& Top();
  [[nodiscard]] const T& Top() const;
  void Push(const T& x);
  void Pop() noexcept;
  bool IsEmpty() const noexcept;
  QueueLstT& operator=(const QueueLstT& x);
  QueueLstT& operator=(QueueLstT&& x) noexcept;
  void Clear() noexcept;
private:
  struct Node {
    T v;
    Node* next = nullptr;
  };
  Node* head_ = nullptr;
  Node* tail_ = nullptr;
};

template<class T>
QueueLstT<T>::QueueLstT(QueueLstT&& x) noexcept {
  head_ = x.head_;
  tail_ = x.tail_;
  x.head_ = nullptr;
  x.tail_ = nullptr;
}

template<class T>
QueueLstT<T>& QueueLstT<T>::operator=(QueueLstT&& x) noexcept {
  if (x.head_ != head_) {
    Clear();
    head_ = x.head_;
    tail_ = x.tail_;
    x.head_ = nullptr;
    x.tail_ = nullptr;
  }
  return *this;
}

template<class T>
T& QueueLstT<T>::Top() {
  if (head_ == nullptr) {
    throw std::logic_error("Queue is empty");
  }
  return (head_->v);
}

//should work
template<class T>
const T& QueueLstT<T>::Top() const {
  if (head_ == nullptr) {
    throw std::logic_error("Queue is empty");
  }
  return (head_->v);
}

//correct
template<class T>
void QueueLstT<T>::Push(const T& x) {
  if (head_ == nullptr) {
    tail_ = new Node;
    tail_->v = x;
    head_ = tail_;
  }
  else {
    tail_->next = new Node;
    tail_ = tail_->next;
    tail_->v = x;
  }
}

//correct
template<class T>
void QueueLstT<T>::Pop() noexcept {
  if (head_ != nullptr) {
    if (head_ == tail_) {
      tail_ = tail_->next;
    }
    Node* temp = head_;
    head_ = temp->next;
    delete temp;
  }
}

//correct
template<class T>
bool QueueLstT<T>::IsEmpty() const noexcept {
  if (head_ == nullptr) {
    return true;
  }
  else {
    return false;
  }
}

//correct
template<class T>
QueueLstT<T>::~QueueLstT() {
  while (!IsEmpty()) {
    Pop();
  }
}

//i have some questions
template<class T>
QueueLstT<T>::QueueLstT(const QueueLstT& x) {
  if (x.head_ != nullptr) {
    head_ = new Node;
    tail_ = head_;
    head_->v = x.head_->v;
    Node* new_tail = tail_;
    Node* temp_head = x.head_;
    while (temp_head->next != nullptr) {
      new_tail->next = new Node;
      new_tail = new_tail->next;
      temp_head = temp_head->next;
      new_tail->v = temp_head->v;
    }
  }
}

//rewrite pls!!!!!!!
template<class T>
QueueLstT<T>& QueueLstT<T>::operator=(const QueueLstT& x) {
  if (x.head_ != head_) {
    if (x.head_ == nullptr) {
      while (head_ != nullptr) {
        Pop();
      }
    }
    else {
      if (head_ == nullptr) {
        head_ = new Node;
        tail_ = head_;
      }
      Node* new_stack = head_;
      Node* temp_head = x.head_;
      new_stack->v = temp_head->v;
      while (new_stack->next != nullptr && temp_head->next != nullptr) {
        new_stack = new_stack->next;
        temp_head = temp_head->next;
        new_stack->v = temp_head->v;
      }
      if (new_stack->next == nullptr && temp_head->next != nullptr) {
        while (temp_head->next != nullptr) {
          temp_head = temp_head->next;
          Push(temp_head->v);
        }
      }
      else if (new_stack->next != nullptr && temp_head->next == nullptr) {
        Node* show = new_stack->next;
        new_stack->next = nullptr;
        while (show->next != nullptr) {
          Node* curr = show;
          show = show->next;
          delete curr;
        }
      }
    }
  }
  return *this;
}

//should work
template<class T>
void QueueLstT<T>::Clear() noexcept {
  while (!IsEmpty()) {
    Pop();
  }
}

#endif