#ifndef QUEUELSTPRT_HPP
#define QUEUELSTPRT_HPP
#include <cstddef>
#include <utility>
#include <stdexcept>
#include <iostream>

template<class T> 
class QueueLstPrT {
public:
  QueueLstPrT() = default;
  QueueLstPrT(const QueueLstPrT& x);
  QueueLstPrT(QueueLstPrT&& x) noexcept;
  ~QueueLstPrT();
  T& Top();
  [[nodiscard]] const T& Top() const;
  void Push(const T& x);
  void Pop() noexcept;
  bool IsEmpty() const noexcept;
  QueueLstPrT& operator=(const QueueLstPrT& x);
  QueueLstPrT& operator=(QueueLstPrT&& x) noexcept;
  void Clear() noexcept;
private:
  struct Node {
    T v;
    Node* next = nullptr;
  };
  Node* head_ = nullptr;
};

template<class T>
void QueueLstPrT<T>::Push(const T& x) {
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

template<class T>
bool QueueLstPrT<T>::IsEmpty() const noexcept {
  if (head_ == nullptr) {
    return true;
  }
  return false;
}

template<class T>
T& QueueLstPrT<T>::Top() {
  if (!IsEmpty()) {
    return head_->v;
  }
  else {
    throw std::logic_error("QueueLstPrT is empty");
  }
}

template<class T>
const T& QueueLstPrT<T>::Top() const {
  if (!IsEmpty()) {
    return head_->v;
  }
  else {
    throw std::logic_error("QueueLstPrT is empty");
  }
}

template<class T>
QueueLstPrT<T>::~QueueLstPrT() {
  Clear();
}

template<class T>
void QueueLstPrT<T>::Pop() noexcept {
  if (!IsEmpty()) {
    head_ = head_->next;
  }
}

template<class T>
void QueueLstPrT<T>::Clear() noexcept {
  while (!IsEmpty()) {
    Pop();
  }
}

template<class T>
QueueLstPrT<T>::QueueLstPrT(const QueueLstPrT& x) {
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

template<class T>
QueueLstPrT<T>& QueueLstPrT<T>::operator=(const QueueLstPrT& x) {
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

template<class T>
QueueLstPrT<T>::QueueLstPrT(QueueLstPrT&& x) noexcept {
  std::swap(head_, x.head_);
  x.head_ = nullptr;
}

template<class T>
QueueLstPrT<T>& QueueLstPrT<T>::operator=(QueueLstPrT&& x) noexcept {
  std::swap(head_, x.head_);
  x.head_ = nullptr;
  return *this;
}

#endif