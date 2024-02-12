#include <stacklst/stacklst.hpp>
#include <iostream>

const Complex& StackLst::Top() {
  return (head_->v);
}

void StackLst::Push(const Complex& x) {
  Node* temp = head_;
  head_ = new Node;
  head_->v = x;
  head_->next = temp;
}

void StackLst::Pop() noexcept {
  Node* temp = head_;
  head_ = temp->next;
  delete temp;
}

bool StackLst::IsEmpty() noexcept {
  if (head_ == nullptr) {
    return true;
  }
  else {
    return false;
  }
}

StackLst::~StackLst() {
  while (!IsEmpty()) {
    Pop();
  }
}

StackLst::StackLst(const StackLst& x) {
  Node* t_head = x.head_;
  while (t_head != nullptr) {
    head_ = new Node;
    head_->v = t_head->v;
    head_->next = t_head->next;
    t_head = t_head->next;
  }
}