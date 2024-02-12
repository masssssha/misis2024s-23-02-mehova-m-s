#include <stacklst/stacklst.hpp>
#include <iostream>
#include <algorithm>

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

