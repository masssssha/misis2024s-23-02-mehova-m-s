/*#include <bitset/bitset.hpp>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

TEST_CASE("size test") {
  BitSet a;
  CHECK(a.Size() == 0);
  a.Resize(5);
  CHECK(a.Size() == 5);
  a.Set(4, 1);
  CHECK(a.Get(4) == 1);
  CHECK(a.Get(3) == 0);
  CHECK_THROWS(a.Get(5));
  a.Set(4, 0);
  a.Resize(69);
  a.Set(32, 1);
  a.Set(65, 1);
  CHECK(a.Get(32) == 1);в п
  CHECK(a.Get(65) == 1);
  CHECK(a.Get(68) == 0);
}*/

#include <bitset/bitset.hpp>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

TEST_CASE("ctor") {
  BitSet bitset(8);
  CHECK_EQ(bitset.Size(), 8);
  CHECK_NOTHROW(bitset.Set(0, 1));
  CHECK_NOTHROW(bitset.Set(1, 0));
  CHECK_NOTHROW(bitset.Set(2, 1));
  CHECK_NOTHROW(bitset.Set(3, 0));
  CHECK_NOTHROW(bitset.Set(4, 1));
  CHECK_NOTHROW(bitset.Set(5, 0));
  CHECK_NOTHROW(bitset.Set(6, 1));
  CHECK_NOTHROW(bitset.Set(7, 0));
  CHECK_EQ(bitset.Size(), 8);
  CHECK_EQ(bitset.Get(0), 1);
  CHECK_EQ(bitset.Get(1), 0);
  CHECK_EQ(bitset.Get(2), 1);
  CHECK_EQ(bitset.Get(3), 0);
  CHECK_EQ(bitset.Get(4), 1);
  CHECK_EQ(bitset.Get(5), 0);
  CHECK_EQ(bitset.Get(6), 1);
  CHECK_EQ(bitset.Get(7), 0);
}

TEST_CASE("resize test") {
  BitSet bitset(8);
  CHECK_EQ(bitset.Size(), 8);
  CHECK_NOTHROW(bitset.Set(0, 1));
  CHECK_NOTHROW(bitset.Set(1, 0));
  CHECK_NOTHROW(bitset.Set(2, 1));
  CHECK_NOTHROW(bitset.Set(3, 0));
  CHECK_NOTHROW(bitset.Set(4, 1));
  CHECK_NOTHROW(bitset.Set(5, 0));
  CHECK_NOTHROW(bitset.Set(6, 1));
  CHECK_NOTHROW(bitset.Set(7, 0));

  bitset.Resize(10);
  CHECK_EQ(bitset.Size(), 10);
  CHECK_EQ(bitset.Get(8), 0);
  CHECK_EQ(bitset.Get(9), 0);

  CHECK_EQ(bitset.Get(0), 1);
  CHECK_EQ(bitset.Get(1), 0);
  CHECK_EQ(bitset.Get(2), 1);
  CHECK_EQ(bitset.Get(3), 0);
  CHECK_EQ(bitset.Get(4), 1);
  CHECK_EQ(bitset.Get(5), 0);
  CHECK_EQ(bitset.Get(6), 1);
  CHECK_EQ(bitset.Get(7), 0);
}

TEST_CASE("clear test") {
  BitSet bitset(8);
  CHECK_EQ(bitset.Size(), 8);
  CHECK_NOTHROW(bitset.Set(0, 1));
  CHECK_NOTHROW(bitset.Set(1, 0));
  CHECK_NOTHROW(bitset.Set(2, 1));
  CHECK_NOTHROW(bitset.Set(3, 0));
  CHECK_NOTHROW(bitset.Set(4, 1));
  CHECK_NOTHROW(bitset.Set(5, 0));
  CHECK_NOTHROW(bitset.Set(6, 1));
  CHECK_NOTHROW(bitset.Set(7, 0));

  bitset.Clear();
  CHECK_THROWS_AS(bitset.Get(0), std::out_of_range);
}

TEST_CASE("out of range test") {
  BitSet bitset(8);
  CHECK_EQ(bitset.Size(), 8);
  CHECK_NOTHROW(bitset.Set(0, 1));
  CHECK_NOTHROW(bitset.Set(1, 0));
  CHECK_NOTHROW(bitset.Set(2, 1));
  CHECK_NOTHROW(bitset.Set(3, 0));
  CHECK_NOTHROW(bitset.Set(4, 1));
  CHECK_NOTHROW(bitset.Set(5, 0));
  CHECK_NOTHROW(bitset.Set(6, 1));
  CHECK_NOTHROW(bitset.Set(7, 0));

  CHECK_THROWS_AS(bitset.Get(8), std::out_of_range);
  CHECK_THROWS_AS(bitset.Get(-1), std::out_of_range);
  CHECK_THROWS_AS(bitset.Get(32), std::out_of_range);
  CHECK_THROWS_AS(bitset.Set(8, 1), std::out_of_range);
  CHECK_THROWS_AS(bitset.Set(-1, 1), std::out_of_range);
  CHECK_THROWS_AS(bitset.Get(-1), std::out_of_range);
}

TEST_CASE("bit operations test") {
  BitSet bitset(8);
  CHECK_EQ(bitset.Size(), 8);
  CHECK_NOTHROW(bitset.Set(0, 1));
  CHECK_NOTHROW(bitset.Set(1, 0));
  CHECK_NOTHROW(bitset.Set(2, 1));
  CHECK_NOTHROW(bitset.Set(3, 0));
  CHECK_NOTHROW(bitset.Set(4, 1));
  CHECK_NOTHROW(bitset.Set(5, 0));
  CHECK_NOTHROW(bitset.Set(6, 1));
  CHECK_NOTHROW(bitset.Set(7, 0));

  BitSet bitset1(8);
  CHECK_EQ(bitset1.Size(), 8);
  bitset1 = bitset;
  ~bitset;
  CHECK_FALSE(bitset1.Get(0) == bitset.Get(0));
  CHECK_FALSE(bitset1.Get(1) == bitset.Get(1));
  CHECK_FALSE(bitset1.Get(2) == bitset.Get(2));
  CHECK_FALSE(bitset1.Get(3) == bitset.Get(3));
  CHECK_FALSE(bitset1.Get(4) == bitset.Get(4));
  CHECK_FALSE(bitset1.Get(5) == bitset.Get(5));
  CHECK_FALSE(bitset1.Get(6) == bitset.Get(6));
  CHECK_FALSE(bitset1.Get(7) == bitset.Get(7));

  BitSet bitset2(8);
  CHECK_EQ(bitset2.Size(), 8);
  CHECK_NOTHROW(bitset2.Set(0, 1));
  CHECK_NOTHROW(bitset2.Set(1, 1));
  CHECK_NOTHROW(bitset2.Set(2, 1));
  CHECK_NOTHROW(bitset2.Set(3, 1));
  CHECK_NOTHROW(bitset2.Set(4, 1));
  CHECK_NOTHROW(bitset2.Set(5, 1));
  CHECK_NOTHROW(bitset2.Set(6, 1));
  CHECK_NOTHROW(bitset2.Set(7, 1));

  BitSet bitset3(8);
  CHECK_EQ(bitset3.Size(), 8);
  bitset3 = bitset & bitset2;
  CHECK_EQ(bitset3.Get(0), bitset.Get(0));
  CHECK_EQ(bitset3.Get(1), bitset.Get(1));
  CHECK_EQ(bitset3.Get(2), bitset.Get(2));
  CHECK_EQ(bitset3.Get(3), bitset.Get(3));
  CHECK_EQ(bitset3.Get(4), bitset.Get(4));
  CHECK_EQ(bitset3.Get(5), bitset.Get(5));
  CHECK_EQ(bitset3.Get(6), bitset.Get(6));
  CHECK_EQ(bitset3.Get(7), bitset.Get(7));

  BitSet bitset4(8);
  CHECK_EQ(bitset4.Size(), 8);
  bitset4 = bitset | bitset2;
  CHECK_EQ(bitset4.Get(0), 1);
  CHECK_EQ(bitset4.Get(1), 1);
  CHECK_EQ(bitset4.Get(2), 1);
  CHECK_EQ(bitset4.Get(3), 1);
  CHECK_EQ(bitset4.Get(4), 1);
  CHECK_EQ(bitset4.Get(5), 1);
  CHECK_EQ(bitset4.Get(6), 1);
  CHECK_EQ(bitset4.Get(7), 1);

  BitSet bitset5(8);
  CHECK_EQ(bitset5.Size(), 8);
  bitset5 = bitset ^ bitset1;
  CHECK_EQ(bitset5.Get(0), 1);
  CHECK_EQ(bitset5.Get(1), 1);
  CHECK_EQ(bitset5.Get(2), 1);
  CHECK_EQ(bitset5.Get(3), 1);
  CHECK_EQ(bitset5.Get(4), 1);
  CHECK_EQ(bitset5.Get(5), 1);
  CHECK_EQ(bitset5.Get(6), 1);
  CHECK_EQ(bitset5.Get(7), 1);
}

TEST_CASE("comparison test") {
  BitSet bitset(8);
  CHECK_EQ(bitset.Size(), 8);
  CHECK_NOTHROW(bitset.Set(0, 1));
  CHECK_NOTHROW(bitset.Set(1, 0));
  CHECK_NOTHROW(bitset.Set(2, 1));
  CHECK_NOTHROW(bitset.Set(3, 0));
  CHECK_NOTHROW(bitset.Set(4, 1));
  CHECK_NOTHROW(bitset.Set(5, 0));
  CHECK_NOTHROW(bitset.Set(6, 1));
  CHECK_NOTHROW(bitset.Set(7, 0));

  BitSet bitset1(8);
  CHECK_EQ(bitset1.Size(), 8);
  CHECK_NOTHROW(bitset1.Set(0, 1));
  CHECK_NOTHROW(bitset1.Set(1, 0));
  CHECK_NOTHROW(bitset1.Set(2, 1));
  CHECK_NOTHROW(bitset1.Set(3, 0));
  CHECK_NOTHROW(bitset1.Set(4, 1));
  CHECK_NOTHROW(bitset1.Set(5, 0));
  CHECK_NOTHROW(bitset1.Set(6, 1));
  CHECK_NOTHROW(bitset1.Set(7, 0));

  CHECK(bitset == bitset1);

  CHECK_NOTHROW(bitset1.Set(0, 0));

  CHECK(bitset != bitset1);

  BitSet x, y;
  CHECK(x == y);

  BitSet bitset2(8);
  CHECK_EQ(bitset2.Size(), 8);
  CHECK_NOTHROW(bitset2.Set(0, 1));
  CHECK_NOTHROW(bitset2.Set(1, 1));
  CHECK_NOTHROW(bitset2.Set(2, 1));
  CHECK_NOTHROW(bitset2.Set(3, 1));
  CHECK_NOTHROW(bitset2.Set(4, 1));
  CHECK_NOTHROW(bitset2.Set(5, 1));
  CHECK_NOTHROW(bitset2.Set(6, 1));
  CHECK_NOTHROW(bitset2.Set(7, 1));

  CHECK(bitset != bitset2);

  CHECK_NOTHROW(bitset2.Set(1, 0));
  CHECK_NOTHROW(bitset2.Set(3, 0));
  CHECK_NOTHROW(bitset2.Set(5, 0));
  CHECK_NOTHROW(bitset2.Set(7, 0));

  CHECK(bitset == bitset2);
}

TEST_CASE("operator[]") {
  BitSet a(89);
  a.Set(10, 1);
  a.Set(55, 1);
  a.Set(63, 1);
  a.Set(64, 1);
  a.Set(65, 1);
  CHECK_THROWS(a[89] = 1);
  a[55] = 1;
  CHECK(a.Get(55) == 1);
  std::cout << a;
  BitSet b(32);
  std::cout << b;
  b[0] = 1;
  CHECK(b.Get(0) == 1);
  std::cout << b;
  CHECK(a[55] == 1);
  CHECK(a[55] != 0);
  b[5] = a[55];
  a[11] = 1;
  b[10] = a[11];
  CHECK(b[5] == 1);
  std::cout << b << std::endl;
}
