#include <queuelstt/queuelstt.hpp>
#include <complex/complex.hpp>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "make_vector.hpp"

TEST_CASE_TEMPLATE("queuelstt", T, Complex, int, double, std::string) {
  std::vector<T> test;
  Make_Vector(test, 10);
  QueueLstT<T> s;
  QueueLstT<T> cringe(s);
  CHECK_THROWS(cringe.Top());
  s.Push(test[0]);
  CHECK(s.Top() == test[0]);
  s.Push(test[1]);
  QueueLstT<T> b;
  b = s;
  CHECK(b.Top() == test[0]);
  b.Pop();
  CHECK(b.Top() == test[1]);
  b.Pop();
  CHECK_THROWS(b.Top());
  s = b;
  CHECK_THROWS(s.Top());
  b.Push(test[0]);
  b.Push(test[0]);
  b.Push(test[0]);
  b.Push(test[0]);
  s.Push(test[0]);
  s = b; //присваиваю больший
  CHECK(s.Top() == test[0]);
  s.Pop();
  CHECK(s.Top() == test[0]);
  s.Pop();
  CHECK(s.Top() == test[0]);
  s.Pop();
  CHECK(s.Top() == test[0]);
  s.Pop();
  CHECK_THROWS(s.Top());
  s.Push(test[0]);
  b = s;
  CHECK(b.Top() == test[0]);
  b.Pop();
  CHECK_THROWS(b.Top());
  QueueLstT<T> x;
  QueueLstT<T> y;
  x = y;
  CHECK_THROWS(x.Top());
  QueueLstT<T> z(std::move(s));
  CHECK(z.Top() == test[0]);
  z.Pop();
  CHECK_THROWS(z.Top());
  z.Push(test[0]);
  z.Push(test[0]);
  z.Push(test[0]);
  z.Push(test[0]);
  z.Push(test[0]);
  z.Push(test[0]);
  z.Push(test[0]);
  z.Push(test[0]);
  z.Push(test[0]);
  z.Push(test[0]);
  z.Push(test[0]);
  z.Push(test[0]);
  CHECK(z.Top() == test[0]);
  z.Pop();
  CHECK(z.Top() == test[0]);
  x = std::move(z);
  CHECK(x.Top() == test[0]);
  x.Pop();
  CHECK(x.Top() == test[0]);
  x.Pop();
  CHECK(x.Top() == test[0]);
  x.Pop();
  CHECK(x.Top() == test[0]);
  x.Pop();
  CHECK(x.Top() == test[0]);
  x.Pop();
  CHECK(x.Top() == test[0]);
  x.Pop();
  CHECK(x.Top() == test[0]);
  x.Pop();
  CHECK(x.Top() == test[0]);
  x.Pop();
  CHECK(x.Top() == test[0]);
  x.Pop();
  CHECK(x.Top() == test[0]);
  x.Pop();
  CHECK(x.Top() == test[0]);
  x.Pop();
  CHECK_THROWS(x.Top());
}