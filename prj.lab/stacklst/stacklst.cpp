#include "stacklst.hpp"
#include <stdexcept>

StackLst::StackLst(StackLst&& x) noexcept {
  Clear();
  head_ = x.head_;
  x.head_ = nullptr;
}

StackLst& StackLst::operator=(StackLst&& x) noexcept {
  if (head_ != x.head_) {
    Clear();
    head_ = x.head_;
    x.head_ = nullptr;
  }
  return *this;
}

Complex& StackLst::Top() {
  if (head_ == nullptr) {
    throw std::logic_error("Stack is empty");
  }
  return (head_->v);
}

const Complex& StackLst::Top() const {
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

StackLst& StackLst::operator=(const StackLst& x) {
  if (x.head_ != head_) {
    if (x.head_ == nullptr && head_ != nullptr) {
      while (head_ != nullptr) {
        Pop();
      }
    }
    else {
      if (head_ == nullptr && x.head_ != nullptr) {
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

void StackLst::Clear() noexcept {
  while (!IsEmpty()) {
    Pop();
  }
}