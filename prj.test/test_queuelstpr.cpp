#include <queuelstpr/queuelstpr.hpp>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

TEST_CASE("queuelstpr") {
  QueueLstPr s;
  s.Push(2.5f);
  CHECK(s.Top() == 2.5f);
  s.Push(1.5f);
  CHECK(s.Top() == 1.5f);
  s.Push(1.2f);
  CHECK(s.Top() == 1.2f);
  s.Push(1.3f);
  s.Push(1.7f);
  QueueLstPr ff(s);
  CHECK(ff.Top() == 1.2f);
  s.Pop();
  CHECK(s.Top() == 1.3f);
  s.Pop();
  CHECK(s.Top() == 1.5f);
  s.Pop();
  CHECK(s.Top() == 1.7f);
  s.Pop();
  CHECK(s.Top() == 2.5f);
  s.Pop();
  CHECK_THROWS(s.Top());
  s.Push(3.4f);
  CHECK(s.Top() == 3.4f);
  s.Pop();
  CHECK_THROWS(s.Top());
  ff.Pop();
  CHECK(ff.Top() == 1.3f);
  ff.Pop();
  CHECK(ff.Top() == 1.5f);
  ff.Pop();
  CHECK(ff.Top() == 1.7f);
  ff.Pop();
  CHECK(ff.Top() == 2.5f);
  ff.Pop();
  ff.Push(1.4f);
  CHECK(ff.Top() == 1.4f);
  ff.Pop();
  CHECK_THROWS(ff.Top());
  ff.Push(30.5f);
  CHECK(ff.Top() == 30.5f);
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
}