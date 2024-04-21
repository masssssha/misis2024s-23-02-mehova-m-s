#include <stacklstt/stacklstt.hpp>
#include <complex/complex.hpp>
#include "make_vector.hpp"
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

TEST_CASE_TEMPLATE("stacklstt", T, Complex, int, double, std::string) {
  std::vector<T> test;
  Make_Vector(test, 10);
  T z1(test[0]);
  T z2(test[3]);
  T z3(test[5]);
  StackLstT<T> a;
  StackLstT<T> pupupu(a);
  CHECK(a.IsEmpty() == true);
  a.Push(z1);
  CHECK(a.Top() == z1);
  a.Push(z1);
  CHECK(a.IsEmpty() == false);
  CHECK(a.Top() == z1);
  a.Pop();
  CHECK(a.Top() == z1);
  a.Push(z2);
  a.Push(z2);
  a.Push(z2);
  CHECK(a.Top() == z2);
  a.Pop();
  CHECK(a.Top() == z2);
  StackLstT<T> b(a);
  CHECK(b.Top() == a.Top());
  a.Pop();
  b.Pop();
  CHECK(a.Top() == b.Top());
  b.Pop();
  CHECK(b.Top() == z2);
  b.Pop();
  CHECK_THROWS(b.Top());
  a.Pop();
  a.Pop();
  CHECK_THROWS(a.Top());
  a.Pop();
  CHECK_THROWS(a.Top());
  b.Push(z3);
  b.Push(z3);
  StackLstT<T> c(b);
  c.Pop();
  c.Push(z3);
  CHECK(c.Top() != b.Top());
  CHECK(c.Top() == z3);
  CHECK(b.Top() == z3);
  StackLstT<T> s;
  s.Push(z1);
  s.Push(z1);
  StackLstT<T> ss;
  ss = s;
  CHECK(ss.Top() == z1);
  ss.Pop();
  CHECK(ss.Top() == z1);
  ss.Pop();
  CHECK_THROWS(ss.Top());
  s = ss;
  CHECK_THROWS(s.Top());
  s.Push(z1);
  ss.Push(z1);
  s = ss;
  CHECK(s.Top() == z1);
  s.Push(z1);
  s.Push(z1);
  s = ss;
  CHECK(s.Top() == z1);
  s.Pop();
  CHECK_THROWS(s.Top());
  s.Push(z1);
  s.Push(z1);
  s.Push(z1);
  s.Push(z1);
  ss = s;
  CHECK(ss.Top() == z1);
  ss.Pop();
  CHECK(ss.Top() == z1);
  ss.Pop();
  CHECK(ss.Top() == z1);
  ss.Pop();
  CHECK(ss.Top() == z1);
  ss.Pop();
  CHECK_THROWS(ss.Top());
  /*StackLstT<T> e;
  StackLstT<T> d;
  d.Push(z1);
  e.Push(T(1));
  e.Push(T(12));
  e.Push(T(3));
  e.Push(T(1));
  d = e; //присваиваю больший
  CHECK(d.Top() == T(1));
  d.Pop();
  CHECK(d.Top() == T(3));
  d.Pop();
  CHECK(d.Top() == T(12));
  d.Pop();
  CHECK(d.Top() == T(1));
  d.Pop();
  CHECK_THROWS(d.Top());*/
}