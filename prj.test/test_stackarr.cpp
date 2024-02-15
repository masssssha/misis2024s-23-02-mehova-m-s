
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <stackarr/stackarr.hpp>
#include <complex/complex.hpp>
#include "doctest.h"
#include <fstream>

Complex z1(1, 2);
Complex z2(3, 4);
Complex z3(5, 6);

TEST_CASE("default ctor") {
  StackArr s;
}

TEST_CASE("initializer list ctor") {
  //StackArr s = { z1, z2, z3 };
  StackArr s;
  s.Push(z1);
  s.Push(z2);
  s.Push(z3);

  CHECK_EQ(z3, s.Top());
  s.Pop();
  CHECK_EQ(z2, s.Top());
  s.Pop();
  CHECK_EQ(z1, s.Top());
}

TEST_CASE("copy ctor") {
  //StackArr ss = { z1, z2, z3 };
  StackArr ss;
  ss.Push(z1);
  ss.Push(z2);
  ss.Push(z3);
  StackArr s(ss);

  CHECK_EQ(z3, s.Top());
  s.Pop();
  CHECK_EQ(z2, s.Top());
  s.Pop();
  CHECK_EQ(z1, s.Top());

  CHECK_EQ(z3, ss.Top());
  StackArr a;
  a.Push(Complex(5, 1));
  a.Push(Complex(5, 2));
  a.Push(Complex(5, 3));
  StackArr b;
  b = a;
  CHECK(b.Top() == a.Top());
  b.Pop();
  CHECK(b.Top() == Complex(5, 2));
  b.Pop();
  CHECK(b.Top() == Complex(5, 1));
  b.Pop();
  CHECK_THROWS(b.Top());
  b.Push(Complex(1, 1));
  b.Push(Complex(1, 2));
  b.Push(Complex(1, 3));
  b.Push(Complex(1, 4));
  b.Push(Complex(1, 5));
  b.Push(Complex(1, 6));
  b.Push(Complex(1, 7));
  b.Push(Complex(1, 8));
  b.Push(Complex(1, 9));
  CHECK(b.Top() == Complex(1, 9));
  a = b;
  CHECK(a.Top() == b.Top());
  a.Pop();
  CHECK(a.Top() == Complex(1, 8));
  b.Pop();
  b.Pop();
  b.Pop();
  CHECK(b.Top() == Complex(1, 6));
}

TEST_CASE("eq operator") {
  //StackArr ss = { z1, z2, z3 };
  StackArr ss;
  ss.Push(z1);
  ss.Push(z2);
  ss.Push(z3);
  StackArr s = ss;

  CHECK_EQ(z3, s.Top());
  s.Pop();
  CHECK_EQ(z2, s.Top());
  s.Pop();
  CHECK_EQ(z1, s.Top());

  CHECK_EQ(z3, ss.Top());
}

TEST_CASE("is empty") {
  StackArr s;
  CHECK_EQ(s.IsEmpty(), true);

  s.Push(z1);
  CHECK_EQ(z1, s.Top());
  CHECK_EQ(s.IsEmpty(), false);
  s.Pop();

  CHECK_EQ(s.IsEmpty(), true);
  CHECK_THROWS(s.Top());
  s.Push(Complex(5, 2));
  s = s;
  CHECK(s.Top() == Complex(5, 2));
}