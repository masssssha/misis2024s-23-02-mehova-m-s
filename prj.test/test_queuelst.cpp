#include <queuelst/queuelst.hpp>
#include<complex/complex.hpp>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

TEST_CASE("queuelst") {
  QueueLst s;
  s.Push(Complex(2, 2));
  CHECK(s.Top() == Complex(2, 2));
  s.Push(Complex(3, 3));
  QueueLst b;
  b = s;
  CHECK(b.Top() == Complex(2, 2));
  b.Pop();
  CHECK(b.Top() == Complex(3, 3));
  b.Pop();
  CHECK_THROWS(b.Top());
  s = b;
  CHECK_THROWS(s.Top());
  b.Push(Complex(1, 12));
  b.Push(Complex(12, 1));
  b.Push(Complex(3, 4));
  b.Push(Complex(1, 5));
  s.Push(Complex(1));
  s = b; //присваиваю больший
  CHECK(s.Top() == Complex(1, 12));
  s.Pop();
  CHECK(s.Top() == Complex(12, 1));
  s.Pop();
  CHECK(s.Top() == Complex(3, 4));
  s.Pop();
  CHECK(s.Top() == Complex(1, 5));
  s.Pop();
  CHECK_THROWS(s.Top());
  s.Push(Complex(2));
  b = s;
  CHECK(b.Top() == Complex(2));
  b.Pop();
  CHECK_THROWS(b.Top());
}