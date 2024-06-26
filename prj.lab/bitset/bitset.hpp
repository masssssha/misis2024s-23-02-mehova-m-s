#ifndef BITSET_HPP
#define BITSET_HPP

#include <stdexcept>
#include <vector>
#include <string>
#include <algorithm>
#include <utility>
#include <iostream>
#include <cstdint>

class BitSet {
public:
  class BitAccessor {
  private:
    BitSet& bs_;
    std::int32_t id_;
  public:
    BitAccessor() = delete;
    BitAccessor(BitSet& x, const std::int32_t ind) : bs_(x), id_(ind) {}
    ~BitAccessor() = default;
    BitAccessor& operator=(const bool v) {
      bs_.Set(id_, v);
      return *this;
    }
    operator bool() const {
      return bs_.Get(id_);
    }
    BitAccessor& operator=(const BitAccessor& x) {
      bs_.Set(id_, x.bs_.Get(x.id_));
      return *this;
    }
  };
  BitSet() = default;
  ~BitSet() = default;
  BitSet(const std::int32_t s);
  BitSet(const BitSet& x);
  BitSet(BitSet&& x) noexcept;
  BitSet& operator=(const BitSet& x);
  BitSet& operator=(BitSet&& x) noexcept;
  std::int32_t Size();
  void Resize(const std::int32_t s);
  bool Get(const std::int32_t ind) const;
  void Set(const std::int32_t ind, const bool v);
  void Clear();
  void Fill(const bool v) noexcept;
  bool operator==(const BitSet& x) const noexcept;
  bool operator!=(const BitSet& x) const noexcept;
  BitSet& operator&=(const BitSet& x);
  BitSet& operator|=(const BitSet& x);
  BitSet& operator^=(const BitSet& x);
  void operator~();
  BitAccessor operator[](const std::int32_t ind);
  bool operator[](const std::int32_t ind) const;
  std::ostream& WriteTxt(std::ostream& x) const noexcept;
  std::ostream& WriteBinary(std::ostream& x) const noexcept;
  std::istream& ReadTxt(std::istream& x) noexcept;
  std::istream& ReadBinary(std::istream& x) noexcept;
private:
  std::int32_t size_ = 0;
  std::vector<std::uint32_t> bit_set;
};

BitSet operator&(const BitSet& x, const BitSet& y);
BitSet operator|(const BitSet& x, const BitSet& y);
BitSet operator^(const BitSet& x, const BitSet& y);

inline std::ostream& operator<<(std::ostream& ostrm, const BitSet& x) noexcept {
  return x.WriteTxt(ostrm);
}
inline std::istream& operator>>(std::istream& istrm, BitSet& x) noexcept {
  return x.ReadTxt(istrm);
}

#endif
