#include <stackarr/stackarr.hpp>
#include<complex/complex.hpp>
#include <iostream>
#include<cstddef>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

TEST_CASE("stackarr") {
  StackArr a;
  a.Push(Complex(2, 5));
  CHECK(a.Top() == Complex(2, 5));
  a.Push(Complex(3, 4));
  CHECK(a.IsEmpty() == false);
  StackArr b(a);
  CHECK(b.Top() == Complex(3, 4));
  b.Pop();
  CHECK(b.Top() == Complex(2, 5));
  a.Push(Complex(2, 7));
  a.Push(Complex(2, 8));
  a.Push(Complex(2, 9));
  a.Push(Complex(2, 10));
  a.Push(Complex(2, 7));
  a.Push(Complex(2, 8));
  a.Push(Complex(2, 9));
  a.Push(Complex(2, 10));
  a.Push(Complex(2, 7));
  a.Push(Complex(2, 8));
  a.Push(Complex(2, 9));
  a.Push(Complex(2, 10));
  a = b;
  CHECK(a.Top() == Complex(2, 5));
  a.Push(Complex(2, 7));
  a.Push(Complex(2, 8));
  a.Push(Complex(2, 9));
  a.Push(Complex(2, 10));
  a.Push(Complex(2, 7));
  a.Push(Complex(2, 8));
  a.Push(Complex(2, 9));
  a.Push(Complex(2, 10));
  a.Push(Complex(2, 7));
  a.Push(Complex(2, 8));
  a.Push(Complex(2, 9));
  a.Push(Complex(2, 11));
  b = a;
  CHECK(b.Top() == Complex(2, 11));
}