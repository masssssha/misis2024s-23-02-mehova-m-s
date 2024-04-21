#include <queuelstprt/queuelstprt.hpp>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "make_vector.hpp"
#include <string>

TEST_CASE_TEMPLATE("queuelstprt", T, float, int, double, std::string) {
  std::vector<T> test;
  Make_Vector(test, 10);
  QueueLstPrT<T> s;
  s.Push(test[0]);
  CHECK(s.Top() == test[0]);
  s.Push(test[0]);
  CHECK(s.Top() == test[0]);
  s.Push(test[0]);
  CHECK(s.Top() == test[0]);
  s.Push(test[0]);
  s.Push(test[0]);
  QueueLstPrT<T> ff(s);
  CHECK(ff.Top() == test[0]);
  s.Pop();
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
  CHECK(s.Top() == test[0]);
  s.Pop();
  CHECK_THROWS(s.Top());
  ff.Pop();
  CHECK(ff.Top() == test[0]);
  ff.Pop();
  CHECK(ff.Top() == test[0]);
  ff.Pop();
  CHECK(ff.Top() == test[0]);
  ff.Pop();
  CHECK(ff.Top() == test[0]);
  ff.Pop();
  ff.Push(test[0]);
  CHECK(ff.Top() == test[0]);
  ff.Pop();
  CHECK_THROWS(ff.Top());
  ff.Push(test[0]);
  CHECK(ff.Top() == test[0]);
}

/*TEST_CASE("ctor copy") {
  QueueLstPr a;
  QueueLstPr b(a);
  CHECK_THROWS(b.Top());
  b.Push(3.5f);
  b.Push(3.1f);
  b.Push(0.9f);
  b.Push(2.1f);
  b.Push(3.5f);
  QueueLstPr c(b);
  CHECK(c.Top() == 0.9f);
  c.Pop();
  CHECK(c.Top() == 2.1f);
}

TEST_CASE("operator=") {
  QueueLstPr a;
  QueueLstPr emp;
  QueueLstPr small;
  small.Push(2.6f);
  small.Push(3.1f);
  small.Push(0.9f);
  a.Push(1.7f);
  a.Push(1.5f);
  a.Push(1.3f);
  a.Push(3.0f);
  a.Push(2.7f);
  a.Push(1.0f);
  a.Push(3.9f);
  a.Push(1.8f); // 1, 1.3, 1.5, 1.7, 1.8, 2.7, 3.0, 3.9
  QueueLstPr b;
  //empte = empty
  b = emp;
  CHECK_THROWS(b.Top());
  CHECK_THROWS(emp.Top());
  //empty = big;
  b = a;
  CHECK(b.Top() == 1.0f);
  b.Pop();
  CHECK(b.Top() == 1.3f);
  b.Pop();
  CHECK(b.Top() == 1.5f);
  b.Pop();
  CHECK(b.Top() == 1.7f);
  b.Pop();
  CHECK(b.Top() == 1.8f);
  b.Pop();
  CHECK(b.Top() == 2.7f);
  b.Pop();
  CHECK(b.Top() == 3.0f);
  b.Pop();
  CHECK(b.Top() == 3.9f);
  b.Pop();
  CHECK_THROWS(b.Top());
  b = a;
  //big = small
  b = small;
  CHECK(b.Top() == 0.9f);
  b.Pop();
  CHECK(b.Top() == 2.6f);
  b.Pop();
  CHECK(b.Top() == 3.1f);
  b.Pop();
  CHECK_THROWS(b.Top());
  b = small;
  //small = big
  b = a;
  CHECK(b.Top() == 1.0f);
  b.Pop();
  CHECK(b.Top() == 1.3f);
  b.Pop();
  CHECK(b.Top() == 1.5f);
  b.Pop();
  CHECK(b.Top() == 1.7f);
  b.Pop();
  CHECK(b.Top() == 1.8f);
  b.Pop();
  CHECK(b.Top() == 2.7f);
  b.Pop();
  CHECK(b.Top() == 3.0f);
  b.Pop();
  CHECK(b.Top() == 3.9f);
  b.Pop();
  CHECK_THROWS(b.Top());
  b = a;
  b = emp;
  CHECK_THROWS(b.Top());
}*/