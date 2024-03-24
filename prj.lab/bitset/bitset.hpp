#ifndef BITSET_HPP
#define BITSET_HPP

#include <stdexcept>
#include <vector>
#include <algorithm>
#include <utility>
#include <iostream>

class BitSet {
public:
  BitSet() = default;
  ~BitSet() = default;
  BitSet(const std::int32_t s);
  BitSet(const BitSet& x);
  BitSet(BitSet&& x) noexcept;
  BitSet& operator=(const BitSet& x);
  BitSet& operator=(BitSet&& x) noexcept;
  std::int32_t Size();                           //done
  void Resize(const std::int32_t s);
  bool Get(const std::int32_t ind) const;
  void Set(const std::int32_t ind, const bool v);
  void Clear();
  bool operator==(const BitSet& x) const noexcept;
  bool operator!=(const BitSet& x) const noexcept;
  BitSet& operator&=(const BitSet& x);
  BitSet& operator|=(const BitSet& x);
  BitSet& operator^=(const BitSet& x);
  void operator~();
private:
  std::int32_t size_ = 0;
  std::vector<std::uint32_t> bit_set;
};

BitSet operator&(const BitSet& x, const BitSet& y);
BitSet operator|(const BitSet& x, const BitSet& y);
BitSet operator^(const BitSet& x, const BitSet& y);

#endif
