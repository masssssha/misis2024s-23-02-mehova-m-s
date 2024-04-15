#include <stacklstt/stacklstt.hpp>
#include <complex/complex.hpp>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

TEST_CASE_TEMPLATE("stacklstt", T, Complex) {
  StackLstT<T> a;
  StackLstT<T> pupupu(a);
  CHECK(a.IsEmpty() == true);
  a.Push(T(2, 5));
  CHECK(a.Top() == T(2, 5));
  a.Push(T(1, 4));
  CHECK(a.IsEmpty() == false);
  CHECK(a.Top() == T(1, 4));
  a.Pop();
  CHECK(a.Top() == T(2, 5));
  a.Push(T(3, 4));
  a.Push(T(3, 5));
  a.Push(T(3, 7));
  CHECK(a.Top() == T(3, 7));
  a.Pop();
  CHECK(a.Top() == T(3, 5));
  StackLstT<T> b(a);
  CHECK(b.Top() == a.Top());
  a.Pop();
  b.Pop();
  CHECK(a.Top() == b.Top());
  b.Pop();
  CHECK(b.Top() == T(2, 5));
  b.Pop();
  CHECK_THROWS(b.Top());
  a.Pop();
  a.Pop();
  CHECK_THROWS(a.Top());
  a.Pop();
  CHECK_THROWS(a.Top());
  b.Push(T(7, 8));
  b.Push(T(1, 2));
  StackLstT<T> c(b);
  c.Pop();
  c.Push(T(11, 38));
  CHECK(c.Top() != b.Top());
  CHECK(c.Top() == T(11, 38));
  CHECK(b.Top() == T(1, 2));
  StackLstT<T> s;
  s.Push(T(1, 1));
  s.Push(T(1, 2));
  StackLstT<T> ss;
  ss = s;
  CHECK(ss.Top() == T(1, 2));
  ss.Pop();
  CHECK(ss.Top() == T(1, 1));
  ss.Pop();
  CHECK_THROWS(ss.Top());
  s = ss;
  CHECK_THROWS(s.Top());
  s.Push(T(1, 1));
  ss.Push(T(3, 5));
  s = ss;
  CHECK(s.Top() == T(3, 5));
  s.Push(T(1, 2));
  s.Push(T(1, 3));
  s = ss;
  CHECK(s.Top() == T(3, 5));
  s.Pop();
  CHECK_THROWS(s.Top());
  s.Push(T(1, 2));
  s.Push(T(1, 3));
  s.Push(T(1, 4));
  s.Push(T(1, 5));
  ss = s;
  CHECK(ss.Top() == T(1, 5));
  ss.Pop();
  CHECK(ss.Top() == T(1, 4));
  ss.Pop();
  CHECK(ss.Top() == T(1, 3));
  ss.Pop();
  CHECK(ss.Top() == T(1, 2));
  ss.Pop();
  CHECK_THROWS(ss.Top());
  StackLstT<T> e;
  StackLstT<T> d;
  d.Push(T(5, 5));
  e.Push(T(1, 12));
  e.Push(T(12, 1));
  e.Push(T(3, 4));
  e.Push(T(1, 5));
  /*d = e; //присваиваю больший
  CHECK(d.Top() == Complex(1, 5));
  d.Pop();
  CHECK(d.Top() == Complex(3, 4));
  d.Pop();
  CHECK(d.Top() == Complex(12, 1));
  d.Pop();
  CHECK(d.Top() == Complex(1, 12));
  d.Pop();
  CHECK_THROWS(d.Top());*/
}