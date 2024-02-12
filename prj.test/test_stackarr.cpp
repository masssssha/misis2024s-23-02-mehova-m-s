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
  a.Pop();
  CHECK_THROWS(a.Top());
}