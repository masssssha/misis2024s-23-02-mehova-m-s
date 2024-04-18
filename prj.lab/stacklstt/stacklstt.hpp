#ifndef STACKLSTT_HPP
#define STACKLSTT_HPP

#include <utility>
#include <algorithm>
#include <stdexcept>

template<class T> class StackLstT {
public:
  StackLstT() = default;
  StackLstT(const StackLstT& x);
  StackLstT(StackLstT&& x) noexcept;
  ~StackLstT();
  T& Top();
  const T& Top() const;
  void Push(const T& x);
  void Pop() noexcept;
  bool IsEmpty() noexcept;
  StackLstT& operator=(const StackLstT& x);
  StackLstT& operator=(StackLstT&& x) noexcept;
  void Clear() noexcept;
private:
  struct Node {
    T v;
    Node* next = nullptr;
  };
  Node* head_ = nullptr;
};

template<class T> 
StackLstT<T>::StackLstT(StackLstT&& x) noexcept {
  std::swap(head_, x.head_);
}

template<class T> 
StackLstT<T>& StackLstT<T>::operator=(StackLstT&& x) noexcept {
  if (head_ != x.head_) {
    std::swap(head_, x.head_);
  }
  return *this;
}

template<class T> 
T& StackLstT<T>::Top() {
  if (head_ == nullptr) {
    throw std::logic_error("Stack is empty");
  }
  return (head_->v);
}

template<class T> 
const T& StackLstT<T>::Top() const {
  if (head_ == nullptr) {
    throw std::logic_error("Stack is empty");
  }
  return (head_->v);
}

template<class T> 
void StackLstT<T>::Push(const T& x) {
  Node* temp = head_;
  head_ = new Node;
  head_->v = x;
  head_->next = temp;
}

template<class T> 
void StackLstT<T>::Pop() noexcept {
  if (head_ != nullptr) {
    Node* temp = head_;
    head_ = temp->next;
    delete temp;
  }
}

template<class T> 
bool StackLstT<T>::IsEmpty() noexcept {
  if (head_ == nullptr) {
    return true;
  }
  else {
    return false;
  }
}

template<class T> 
StackLstT<T>::~StackLstT() {
  while (!IsEmpty()) {
    Pop();
  }
}

template<class T> 
StackLstT<T>::StackLstT(const StackLstT& x) {
  if (x.head_ != nullptr) {
    head_ = new Node;
    head_->v = x.head_->v;
    Node* new_head = head_;
    Node* temp_head = x.head_;
    while (temp_head->next != nullptr) {
      new_head->next = new Node;
      new_head = new_head->next;
      temp_head = temp_head->next;
      new_head->v = temp_head->v;
    }
    new_head->next = nullptr;
  }
}

template<class T> 
StackLstT<T>& StackLstT<T>::operator=(const StackLstT& x) {
  if (x.head_ != head_) {
    if (x.head_ == nullptr) {
      while (head_ != nullptr) {
        Pop();
      }
    }
    else {
      if (head_ == nullptr) {
        head_ = new Node;
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
          new_stack->next = new Node;
          new_stack = new_stack->next;
          temp_head = temp_head->next;
          new_stack->v = temp_head->v;
        }
        new_stack->next = nullptr;
      }
      if (new_stack->next != nullptr && temp_head->next == nullptr) {
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

template<class T> 
void StackLstT<T>::Clear() noexcept {
  while (!IsEmpty()) {
    Pop();
  }
}

#endif