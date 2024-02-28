#include "queuelst.hpp"
#include <stdexcept>
#include <iostream>

QueueLst::QueueLst(QueueLst&& x) noexcept {
  head_ = x.head_;
  tail_ = x.tail_;
  x.head_ = nullptr;
  x.tail_ = nullptr;
}

QueueLst& QueueLst::operator=(QueueLst&& x) noexcept {
  if (x.head_ != head_) {
    Clear();
    head_ = x.head_;
    tail_ = x.tail_;
    x.head_ = nullptr;
    x.tail_ = nullptr;
  }
  return *this;
}

Complex& QueueLst::Top() {
  if (head_ == nullptr) {
    throw std::logic_error("Queue is empty");
  }
  return (head_->v);
}

//should work
const Complex& QueueLst::Top() const {
  if (head_ == nullptr) {
    throw std::logic_error("Queue is empty");
  }
  return (head_->v);
}

//correct
void QueueLst::Push(const Complex& x) {
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
void QueueLst::Pop() noexcept {
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
bool QueueLst::IsEmpty() const noexcept {
  if (head_ == nullptr) {
    return true;
  }
  else {
    return false;
  }
}

//correct
QueueLst::~QueueLst() {
  while (!IsEmpty()) {
    Pop();
  }
}

//i have some questions
QueueLst::QueueLst(const QueueLst& x) {
  head_ = new Node;
  tail_ = head_;
  head_->v = x.head_->v;
  Node* new_tail = tail_;
  Node* temp_head = x.head_;
  while (temp_head->next != nullptr) {
    new_tail->next = new Node;
    new_tail = new_tail ->next;
    temp_head = temp_head->next;
    new_tail->v = temp_head->v;
  }
}

//rewrite pls!!!!!!!
QueueLst& QueueLst::operator=(const QueueLst& x) {
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
void QueueLst::Clear() noexcept {
  while (!IsEmpty()) {
    Pop();
  }
}