#include <queuearr/queuearr.hpp>
#include<complex/complex.hpp>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

TEST_CASE("queuearr") {
  QueueArr a;
  CHECK_THROWS(a.Top());
  a.Push(Complex(1, 2));
  CHECK(a.Top() == Complex(1, 2));
  a.Pop();
  CHECK_THROWS(a.Top());
  a.Push(Complex(1, 2));
  a.Push(Complex(2, 4));
  a.Push(Complex(3, 4));
  a.Push(Complex(4, 4));
  a.Push(Complex(5, 4));
  a.Push(Complex(6, 4));
  a.Push(Complex(7, 4));
  a.Push(Complex(8, 4));
  a.Pop();
  CHECK(a.Top() == Complex(2, 4));
  a.Push(Complex(9, 4));
  a.Pop();
  CHECK(a.Top() == Complex(3, 4));
  a.Pop();
  a.Pop();
  a.Pop();
  a.Pop();
  a.Pop();
  a.Pop();
  CHECK(a.Top() == Complex(9, 4));
  a.Pop();
  CHECK_THROWS(a.Top());
  a.Push(Complex(9, 4));
  a.Push(Complex(10, 4));
  a.Push(Complex(11, 4));
  a.Push(Complex(12, 4));
  a.Push(Complex(13, 4));
  a.Push(Complex(14, 4));
  a.Push(Complex(15, 4));
  a.Push(Complex(16, 4));
  a.Push(Complex(17, 4));
  a.Push(Complex(18, 4));
  a.Push(Complex(19, 4));
  QueueArr b(a);
  CHECK(a.Top() == b.Top());
  b.Pop();
  CHECK(b.Top() == Complex(10, 4));
  b.Pop();
  b.Pop();
  b.Pop();
  b.Pop();
  b.Pop();
  b.Pop();
  b.Pop();
  b.Pop();
  b.Pop();
  CHECK(b.Top() == Complex(19, 4));
  b.Pop();
  CHECK_THROWS(b.Top());
}