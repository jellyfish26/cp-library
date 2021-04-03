#pragma once
#include <cstdint>
#include <istream>
#include <ostream>

template<const std::int64_t kMod>
class ModInt {
 public:
  ModInt();
  ModInt(std::int64_t value);
  ModInt(const ModInt& target);

  std::int64_t Get() const;
  ModInt Inverse() const;

  ModInt& operator+=(const ModInt& target);
  ModInt& operator-=(const ModInt& target);
  ModInt& operator*=(const ModInt& target);
  ModInt& operator/=(const ModInt& target);
  
  ModInt operator+(const ModInt& target) const;
  ModInt operator-(const ModInt& target) const;
  ModInt operator*(const ModInt& target) const;
  ModInt operator/(const ModInt& target) const;

  ModInt operator-() const;

  bool operator==(const ModInt& target) const;
  bool operator!=(const ModInt& target) const;

  ModInt& operator=(std::int64_t value);
  ModInt& operator=(const ModInt& target);

  ModInt Pow(std::int64_t value) const;
  static std::int64_t GetMod();

  template<const std::int64_t kX>
  friend std::istream& operator>>(std::istream &stream, ModInt<kX>& target);

  template<const std::int64_t kX>
  friend std::ostream& operator<<(std::ostream &stream, const ModInt<kX>& target);

 protected:
  std::int64_t value_;
};

template<const std::int64_t kMod>
ModInt<kMod>::ModInt() : value_(0) {}

template<const std::int64_t kMod>
ModInt<kMod>::ModInt(std::int64_t value)
    : value_(value >= 0 ? value % kMod : kMod - ((-kMod) % kMod)) {}

template<const std::int64_t kMod>
ModInt<kMod>::ModInt(const ModInt& target) : value_(target.value_) {}

template<const std::int64_t kMod>
std::int64_t ModInt<kMod>::Get() const {
  return value_;
}

template<const std::int64_t kMod>
ModInt<kMod> ModInt<kMod>::Inverse() const {
  std::int64_t base = value_, p = kMod, u = 1, v = 0;
  while(p) {
    std::int64_t tmp = base / p;
    std::swap(base -= tmp * p, p);
    std::swap(u -= tmp * v, v);
  }
  return ModInt(u);
}

template<const std::int64_t kMod>
ModInt<kMod>& ModInt<kMod>::operator+=(const ModInt& target) {
  this->value_ += target.value_;
  if (value_ >= kMod) {
    value_ -= kMod;
  }
  return *this;
}

template<const std::int64_t kMod>
ModInt<kMod>& ModInt<kMod>::operator-=(const ModInt& target) {
  value_ += (kMod - target.value_);
  if (value_ >= kMod) {
    value_ -= kMod;
  }
  return *this;
}


template<const std::int64_t kMod>
ModInt<kMod>& ModInt<kMod>::operator*=(const ModInt& target) {
  value_ = value_ * target.value_ % kMod;
  return *this;
}

template<const std::int64_t kMod>
ModInt<kMod>& ModInt<kMod>::operator/=(const ModInt& target) {
  *this *= target.Inverse();
  return *this;
}

template<const std::int64_t kMod>
ModInt<kMod> ModInt<kMod>::operator+(const ModInt& target) const {
  return ModInt(*this) += target;
}

template<const std::int64_t kMod>
ModInt<kMod> ModInt<kMod>::operator-(const ModInt& target) const {
  return ModInt(*this) -= target;
}

template<const std::int64_t kMod>
ModInt<kMod> ModInt<kMod>::operator*(const ModInt& target) const {
  return ModInt(*this) *= target;
}

template<const std::int64_t kMod>
ModInt<kMod> ModInt<kMod>::operator/(const ModInt& target) const {
  return ModInt(*this) /= target;
}

template<const std::int64_t kMod>
ModInt<kMod> ModInt<kMod>::operator-() const {
  return ModInt(-value_);
}

template<const std::int64_t kMod>
ModInt<kMod>& ModInt<kMod>::operator=(std::int64_t value) {
  this->value_ = value;
  return *this;
}

template<const std::int64_t kMod>
ModInt<kMod>& ModInt<kMod>::operator=(const ModInt& target) {
  this->value_ = target.value_;
  return *this;
}

template<const std::int64_t kMod>
ModInt<kMod> ModInt<kMod>::Pow(std::int64_t n) const {
  ModInt ret(1), x(value_);
  while (n > 0) {
    if (n&1) ret *= x;
    x *= x;
    n >>= 1;
  }
  return ret;
}

template<const std::int64_t kMod>
std::int64_t ModInt<kMod>::GetMod() {
  return kMod;
}

template<const std::int64_t kMod>
std::istream& operator>>(std::istream& stream, ModInt<kMod>& target) {
  std::int64_t tmp;
  stream >> tmp;
  target = ModInt<kMod>(tmp);
  return stream;
}

template<const std::int64_t kMod>
std::ostream& operator<<(std::ostream& stream, const ModInt<kMod>& target) {
  return stream << target.Get();
}
