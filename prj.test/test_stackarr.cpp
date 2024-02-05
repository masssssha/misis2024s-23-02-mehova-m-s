#include <stackarr/stackarr.hpp>
#include <iostream>

int main() {
  StackArr a;
  std::cout << a.IsEmpty() << std::endl;
  a.Push(Complex(5));
  std::cout << a.Top() << std::endl;
  std::cout << a.IsEmpty() << std::endl;
  a.Push(Complex(2, 4));
  std::cout << a.Top() << std::endl;
  a.Pop();
  std::cout << a.Top() << std::endl;
  a.Push(Complex(3, 1));
  std::cout << a.Top() << std::endl;
  a.Push(Complex(2, 2));
  a.Push(Complex(4, 4));
  a.Push(Complex(8, 8));
  a.Push(Complex(1, 2));
  a.Push(Complex(2, 4));
  a.Push(Complex(2, 10));
  a.Push(Complex(12, 2));
  std::cout << a.Top() << std::endl;
  a.Pop();
  a.Pop();
  std::cout << a.Top() << std::endl;
  StackArr b;
  b = a;
  std::cout << b.Top() << std::endl;
  b.Pop();
  b.Pop();
  std::cout << b.Top() << std::endl;
  a = b;
  std::cout << a.Top() << std::endl;
}