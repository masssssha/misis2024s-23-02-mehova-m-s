#include <stacklst/stacklst.hpp>
#include<complex/complex.hpp>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

TEST_CASE("stackarr") {
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
}