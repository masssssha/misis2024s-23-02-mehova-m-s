#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <stackarrt/stackarrt.hpp>
#include <complex/complex.hpp>
#include "doctest.h"
#include <fstream>

TEST_CASE_TEMPLATE("StackArrT", T, Complex, int, double) {
  std::vector<T> test;
  for (int i = 0; i < 10; i++) {
    test.push_back(T(i));
  }
  StackArrT<T> s;
  s.Push(test[0]);
  s.Push(test[8]);
  s.Push(test[1]);
  s.Push(test[5]);
  CHECK(s.Top() == test[5]);
  s.Push(test[0]);
  s.Push(test[1]);
  s.Push(test[2]);
  s.Push(test[3]);
  s.Push(test[4]);
  s.Push(test[5]);
  s.Push(test[6]);
  s.Push(test[7]);
  CHECK(s.Top() == test[7]);
  StackArrT<T> a;
  a = std::move(s);
  CHECK(a.Top() == test[7]);
  a.Pop();
  CHECK(a.Top() == test[6]);
  a.Pop();
  CHECK(a.Top() == test[5]);
  a.Pop();
  CHECK(a.Top() == test[4]);
  StackArrT<T> b(std::move(a));
  CHECK(b.Top() == test[4]);
  b.Pop();
  CHECK(b.Top() == test[3]);
  b.Pop();
  CHECK(b.Top() == test[2]);
  b.Pop();
  CHECK(b.Top() == test[1]);
  b.Pop();
  CHECK(b.Top() == test[0]);
  b.Pop();
  CHECK(b.Top() == test[5]);
  b.Pop();
  CHECK(b.Top() == test[1]);
  b.Pop();
  CHECK(b.Top() == test[8]);
  b.Pop();
  CHECK(b.Top() == test[0]);
  b.Pop();
  CHECK_THROWS(b.Top());
}

TEST_CASE_TEMPLATE("initializer list ctor", T, Complex, int, double) {
  //StackArrT<T> s = { z1, z2, z3 };
  T z1(1);
  T z2(3);
  T z3(5);
  StackArrT<T> s;
  s.Push(z1);
  s.Push(z2);
  s.Push(z3);

  CHECK_EQ(z3, s.Top());
  s.Pop();
  CHECK_EQ(z2, s.Top());
  s.Pop();
  CHECK_EQ(z1, s.Top());
}

TEST_CASE_TEMPLATE("copy ctor", T, Complex, int, double) {
  //StackArrT<T> ss = { z1, z2, z3 };
  T z1(1);
  T z2(3);
  T z3(5);
  StackArrT<T> ss;
  ss.Push(z1);
  ss.Push(z2);
  ss.Push(z3);
  StackArrT<T> s(ss);

  CHECK_EQ(z3, s.Top());
  s.Pop();
  CHECK_EQ(z2, s.Top());
  s.Pop();
  CHECK_EQ(z1, s.Top());

  CHECK_EQ(z3, ss.Top());
  StackArrT<T> a;
  a.Push(T(5));
  a.Push(T(5));
  a.Push(T(5));
  StackArrT<T> b;
  b = a;
  CHECK(b.Top() == a.Top());
  b.Pop();
  CHECK(b.Top() == T(5));
  b.Pop();
  CHECK(b.Top() == T(5));
  b.Pop();
  CHECK_THROWS(b.Top());
  b.Push(T(1));
  b.Push(T(1));
  b.Push(T(1));
  b.Push(T(1));
  b.Push(T(1));
  b.Push(T(1));
  b.Push(T(1));
  b.Push(T(1));
  b.Push(T(1));
  CHECK(b.Top() == T(1));
  a = b;
  CHECK(a.Top() == b.Top());
  a.Pop();
  CHECK(a.Top() == T(1));
  b.Pop();
  b.Pop();
  b.Pop();
  CHECK(b.Top() == T(1));
}

TEST_CASE_TEMPLATE("eq operator", T, Complex, int, double) {
  //StackArrT<T> ss = { z1, z2, z3 };
  T z1(1);
  T z2(3);
  T z3(5);
  StackArrT<T> ss;
  ss.Push(z1);
  ss.Push(z2);
  ss.Push(z3);
  StackArrT<T> s = ss;

  CHECK_EQ(z3, s.Top());
  s.Pop();
  CHECK_EQ(z2, s.Top());
  s.Pop();
  CHECK_EQ(z1, s.Top());

  CHECK_EQ(z3, ss.Top());
}

TEST_CASE_TEMPLATE("is empty", T, Complex, int, double) {
  T z1(1);
  T z2(3);
  T z3(5);
  StackArrT<T> s;
  CHECK_EQ(s.IsEmpty(), true);

  s.Push(z1);
  CHECK_EQ(z1, s.Top());
  CHECK_EQ(s.IsEmpty(), false);
  s.Pop();

  CHECK_EQ(s.IsEmpty(), true);
  CHECK_THROWS(s.Top());
  s.Push(T(5));
  s = s;
  CHECK(s.Top() == T(5));
}