#include <dynarr/dynarr.hpp>
#include <iostream>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

TEST_CASE("dynarr ctor") {
  DynArr arr_def;
  CHECK_EQ(arr_def.Size(), 0);
  const int size = 5;
  DynArr arr_s(size);
  CHECK_EQ(arr_s[0], 0);
  CHECK_EQ(arr_s.Size(), size);
  CHECK_THROWS(void(DynArr(0)));
  CHECK_THROWS(void(DynArr(-size)));
}

TEST_CASE("dynarr op") {
  const int size = 5;
  DynArr arr1(size);
  CHECK_EQ(arr1[0], 0);
  CHECK_EQ(arr1[arr1.Size() - 1], 0);
  CHECK_THROWS(arr1[-1]);
  CHECK_THROWS(arr1[arr1.Size()]);
}

TEST_CASE("check") {
  DynArr da(4);
  CHECK_EQ(da.Size(), 4);
  da.Resize(3);
  CHECK_EQ(da.Size(), 3);
  da[2] = 2.2f;
  float x = da[2];
  DynArr da2 = da;
  CHECK_EQ(x, 2.2f);
  CHECK_EQ(da2[2], da[2]);
  CHECK_FALSE(&da2[2] == &da[2]);
  CHECK_THROWS(da.Resize(-1));
  CHECK_THROWS(da.Resize(0));
  CHECK_THROWS(DynArr(-1));
  CHECK_THROWS((DynArr(0)));
};