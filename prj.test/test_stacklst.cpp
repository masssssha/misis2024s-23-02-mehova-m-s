#include <stacklst/stacklst.hpp>
#include<complex/complex.hpp>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

TEST_CASE("stacklst") {
  StackLst a;
  CHECK(a.IsEmpty() == true);
  a.Push(Complex(2, 5));
  CHECK(a.Top() == Complex(2, 5));
  a.Push(Complex(1, 4));
  CHECK(a.IsEmpty() == false);
  CHECK(a.Top() == Complex(1, 4));
  a.Pop();
  CHECK(a.Top() == Complex(2, 5));
  a.Push(Complex(3, 4));
  a.Push(Complex(3, 5));
  a.Push(Complex(3, 7));
  CHECK(a.Top() == Complex(3, 7));
  a.Pop();
  CHECK(a.Top() == Complex(3, 5));
  StackLst b(a);
  CHECK(b.Top() == a.Top());
  a.Pop();
  b.Pop();
  CHECK(a.Top() == b.Top());
  b.Pop();
  CHECK(b.Top() == Complex(2, 5));
  b.Pop();
  CHECK_THROWS(b.Top());
  a.Pop();
  a.Pop();
  CHECK_THROWS(a.Top());
  a.Pop();
  CHECK_THROWS(a.Top());
  b.Push(Complex(7, 8));
  b.Push(Complex(1, 2));
  StackLst c(b);
  c.Pop();
  c.Push(Complex(11, 38));
  CHECK(c.Top() != b.Top());
  CHECK(c.Top() == Complex(11, 38));
  CHECK(b.Top() == Complex(1, 2));
  StackLst s;
  s.Push(Complex(1, 1));
  s.Push(Complex(1, 2));
  StackLst ss;
  ss = s;
  CHECK(ss.Top() == Complex(1, 2));
  ss.Pop();
  CHECK(ss.Top() == Complex(1, 1));
  ss.Pop();
  CHECK_THROWS(ss.Top());
  s = ss;
  CHECK_THROWS(s.Top());
  s.Push(Complex(1, 1));
  ss.Push(Complex(3, 5));
  s = ss;
  CHECK(s.Top() == Complex(3, 5));
  s.Push(Complex(1, 2));
  s.Push(Complex(1, 3));
  s = ss;
  CHECK(s.Top() == Complex(3, 5));
  s.Pop();
  CHECK_THROWS(s.Top());
  s.Push(Complex(1, 2));
  s.Push(Complex(1, 3));
  s.Push(Complex(1, 4));
  s.Push(Complex(1, 5));
  ss = s;
  CHECK(ss.Top() == Complex(1, 5));
  ss.Pop();
  CHECK(ss.Top() == Complex(1, 4));
  ss.Pop();
  CHECK(ss.Top() == Complex(1, 3));
  ss.Pop();
  CHECK(ss.Top() == Complex(1, 2));
}