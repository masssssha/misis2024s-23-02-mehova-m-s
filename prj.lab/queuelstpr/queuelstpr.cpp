#include "queuelstpr.hpp"
#include <stdexcept>
#include <iostream>

void QueueLstPr::Push(const float& x) {
  if (IsEmpty()) {
    head_ = new Node;
    head_->v = x;
  }
  else {
    Node* temp = head_;
    if (x < head_->v) {
      Node* cringe = head_;
      head_ = new Node;
      head_->v = x;
      head_->next = cringe;
    }
    else {
      while (temp->next != nullptr && x > temp->next->v) {
        temp = temp->next;
      }
      //std::cout << "TEMP1 " << temp->next << std::endl;
      Node* cur_next = temp->next;
      temp->next = new Node;
      temp->next->v = x;
      temp->next->next = cur_next;
      //std::cout << "TEMP2 " << temp->next << std::endl;
    }
  }
  //std::cout << head_ << " "  << head_->next << std::endl;
}

bool QueueLstPr::IsEmpty() const noexcept {
  if (head_ == nullptr) {
    return true;
  }
  return false;
}

float& QueueLstPr::Top() {
  if (!IsEmpty()) {
    return head_->v;
  }
  else {
    throw std::logic_error("QueueLstPr is empty");
  }
}

const float& QueueLstPr::Top() const {
  if (!IsEmpty()) {
    return head_->v;
  }
  else {
    throw std::logic_error("QueueLstPr is empty");
  }
}

QueueLstPr::~QueueLstPr() {
  Clear();
}

void QueueLstPr::Pop() noexcept {
  if (!IsEmpty()) {
    head_ = head_->next;
  }
}

void QueueLstPr::Clear() noexcept {
  while (!IsEmpty()) {
    Pop();
  }
}

QueueLstPr::QueueLstPr(const QueueLstPr& x) {
  if (x.head_ == nullptr) {
    Clear();
  }
  else {
    head_ = new Node;
    head_->v = x.head_->v;
    Node* temp = x.head_;
    Node* curr = head_;
    while (temp->next != nullptr) {
      curr->next = new Node;
      curr = curr->next;
      temp = temp->next;
      curr->v = temp->v;
    }
  }
}

QueueLstPr& QueueLstPr::operator=(const QueueLstPr& x) {
  if (head_ != x.head_) {
    if (x.head_ == nullptr) {
      Clear();
    }
    else {
      if (head_ == nullptr) {
        head_ = new Node;
      }
      head_->v = x.head_->v;
      Node* temp = x.head_;
      Node* curr = head_;
      while (temp->next != nullptr && curr->next != nullptr) {
        curr = curr->next;
        temp = temp->next;
        curr->v = temp->v;
      }
      if (curr->next == nullptr && temp->next != nullptr) {
        while (temp->next != nullptr) {
          curr->next = new Node;
          curr = curr->next;
          temp = temp->next;
          curr->v = temp->v;
        }
      }
      else if (curr->next != nullptr && temp->next == nullptr) {
        Node* cringe = curr->next;
        curr->next = nullptr;
        while (cringe->next != nullptr) {
          Node* pupu = cringe;
          cringe = pupu->next;
          delete pupu;
        }
      }
    }
  }
  return *this;
}

QueueLstPr::QueueLstPr(QueueLstPr&& x) noexcept {
  std::swap(head_, x.head_);
  x.head_ = nullptr;
}

QueueLstPr& QueueLstPr::operator=(QueueLstPr&& x) noexcept {
  std::swap(head_, x.head_);
  x.head_ = nullptr;
  return *this;
}