#include <stacklstt/stacklstt.hpp>
#include <complex/complex.hpp>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

TEST_CASE_TEMPLATE("stacklstt", T, Complex) {
  StackLstT<T> a;
  a.Push(T(1, 2));
  a.Push(T(2, 3));
  CHECK(a.Top() == T(2, 3));
}