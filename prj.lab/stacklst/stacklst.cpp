#include <stacklst/stacklst.hpp>
#include <iostream>

const Complex& StackLst::Top() {
  if (head_ == nullptr) {
    throw std::logic_error("Stack is empty");
  }
  return (head_->v);
}

void StackLst::Push(const Complex& x) {
  Node* temp = head_;
  head_ = new Node;
  head_->v = x;
  head_->next = temp;
}

void StackLst::Pop() noexcept {
  if (head_ != nullptr) {
    Node* temp = head_;
    head_ = temp->next;
    delete temp;
  }
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