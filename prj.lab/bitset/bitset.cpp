#include "bitset.hpp"

std::int32_t BitSet::Size() {
  return size_;
}

void BitSet::Resize(const std::int32_t s) {
  if (s <= 0) {
    throw std::invalid_argument("Size must be a positive number");
  }
  else { 
    if (size_ == 0) {
      bit_set.push_back(0);
      size_ = 1;
    }
    if (s > size_) {
      std::int32_t curr_box = (size_-1) / 32;
      std::int32_t need_box = (s-1) / 32;
      while (curr_box < need_box) {
        bit_set.push_back(0);
        curr_box += 1;
      }
    }
    if (s < size_) {
      std::int32_t curr_box = (size_-1) / 32;
      std::int32_t curr_number = (size_-1) % 32 + 1;
      std::int32_t need_box = (s-1) / 32;
      std::int32_t need_number = (s-1) % 32 + 1;
      while (curr_box > need_box) {
        bit_set[curr_box] = 0;
        curr_box -= 1;
        curr_number = 31;
      }
      while (curr_number > need_number) {
        bit_set[curr_box] &= ~(1 << curr_number);
        curr_number -= 1;
      }
    }
    size_ = s;
  }
}

BitSet::BitSet(const BitSet& x) {
  bit_set = x.bit_set;
  size_ = x.size_;
}

BitSet::BitSet(BitSet&& x) noexcept {
  std::swap(bit_set, x.bit_set);
  std::swap(size_, x.size_);
}

void BitSet::Set(const std::int32_t ind, const bool v) {
  if ((ind >= size_ || ind < 0)) {
    throw std::out_of_range("index out of range");
  }
  if (v == 0) {
    bit_set[(ind) / 32] &= ~(1 << ind%32);
  }
  else {
    bit_set[(ind) / 32] |= (1 << ind%32);
  }
}

bool BitSet::Get(const std::int32_t ind) const {
  if (ind >= size_ || ind < 0) {
    throw std::out_of_range("index out of range");
  }
  return (bit_set[(ind) / 32] & (1 << ind%32));
}

BitSet& BitSet::operator=(BitSet&& x) noexcept {
  std::swap(bit_set, x.bit_set);
  std::swap(size_, x.size_);
  return *this;
}

BitSet& BitSet::operator=(const BitSet& x) {
  bit_set = x.bit_set;
  size_ = x.size_;
  return *this;
}

void BitSet::Clear() {
  bit_set.clear();
  size_ = 0;
}

BitSet::BitSet(const std::int32_t s) {
  Resize(s);
}

bool BitSet::operator==(const BitSet& x) const noexcept {
  if (size_ == x.size_) {
    if (size_ == 0) {
      return true;
    }
    int flag(0);
    for (int i = 0; i <= (size_-1) / 32; i++) {
      if (bit_set[i] != x.bit_set[i]) {
        flag = 1;
        break;
      }
    }
    return (flag == 0);
  }
  return false;
}

bool BitSet::operator!=(const BitSet& x) const noexcept {
  return !(operator==(x));
}

void BitSet::operator~() {
  for (int i = 0; i <= (size_ - 1) / 32; i++) {
    bit_set[i] = ~bit_set[i];
  }
}

BitSet& BitSet::operator&=(const BitSet& x) {
  if (x.size_ != size_) {
    throw std::length_error("bitsets must have same size");
  }
  for (int i = 0; i <= (size_ - 1) / 32; i++) {
    bit_set[i] &= x.bit_set[i];
  }
  return *this;
}

BitSet operator&(const BitSet& x, const BitSet& y) {
  return BitSet(x) &= y;
}

BitSet& BitSet::operator|=(const BitSet& x) {
  if (x.size_ != size_) {
    throw std::length_error("bitsets must have same size");
  }
  for (int i = 0; i <= (size_ - 1) / 32; i++) {
    bit_set[i] |= x.bit_set[i];
  }
  return *this;
}

BitSet operator|(const BitSet& x, const BitSet& y) {
  return BitSet(x) |= y;
}

BitSet& BitSet::operator^=(const BitSet& x) {
  if (x.size_ != size_) {
    throw std::length_error("bitsets must have same size");
  }
  for (int i = 0; i <= (size_ - 1) / 32; i++) {
    bit_set[i] ^= x.bit_set[i];
  }
  return *this;
}

BitSet operator^(const BitSet& x, const BitSet& y) {
  return BitSet(x) ^= y;
}

BitSet::BiA BitSet::operator[](const std::int32_t ind) {
  if (ind >= size_ || ind < 0) {
    throw std::out_of_range("index out of range");
  }
  BiA a(*this, ind);
  return a;
}

bool BitSet::operator[](const std::int32_t ind) const {
  if (ind >= size_ || ind < 0) {
    throw std::out_of_range("index out of range");
  }
  return Get(ind);
}

void BitSet::Fill(const bool v) noexcept {
  for (int i = 0; i < size_; i++) {
    Set(i, v);
  }
}

std::ostream& BitSet::WriteTxt(std::ostream& x) const noexcept {
  x << size_ << std::endl;
  int start = 1;
  for (int i = 0; i < size_; i++) {
    x << Get(i);
    if ((i + 1) % 32 == 0) {
      x << " " << start << "-" << (i + 1) << std::endl;
      start += 32;
    }
    else if ((i + 1) == size_) {
      int ind = i;
      while (ind < bit_set.size()*32) {
        x << " ";
        ind += 1;
      }
      x << start << "-" << size_ << std::endl;
    }
  }
  return x;
}

std::istream& BitSet::ReadTxt(std::istream& x) noexcept {
  std::string s;
  x >> s;
  if (x.good()) {
    Resize(s.length());
    for (int i = 0; i < s.length(); i++) {
      if (s[i] == '0' || s[i] == '1') {
        Set(i, int(s[i]) - '0');
      }
      else {
        x.setstate(std::ios_base::failbit);
      }
    }
  }
  size_ = s.length();
  return x;
}