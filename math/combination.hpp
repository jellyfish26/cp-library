#pragma once
#include <cstdint>
#include <vector>

#include "modint.hpp"

template<const std::int64_t kMod>
class Combination {
 public:
  explicit Combination(std::size_t size);

  ModInt<kMod> P(int n, int k) const;
  ModInt<kMod> C(int n, int k) const;
  ModInt<kMod> H(int n, int k) const;

 protected:
  std::size_t size_;
  std::vector<ModInt<kMod>> fact_, inv_, fact_inv_;
};

template<const std::int64_t kMod>
Combination<kMod>::Combination(std::size_t size)
    : size_(size), fact_(size), inv_(size), fact_inv_(size) {
  fact_[0] = fact_[1] = 1;
  inv_[1] = 1;
  fact_inv_[0] = fact_inv_[1] = 1;
  for (std::size_t idx = 2; idx < size_; ++idx) {
    fact_[idx] = fact_[idx - 1] * idx;
    inv_[idx] = ModInt<kMod>(0) - inv_[kMod % idx] * (kMod / idx);
    fact_inv_[idx] = fact_inv_[idx - 1] * inv_[idx];
  }
}

template<const std::int64_t kMod>
ModInt<kMod> Combination<kMod>::P(int n, int k) const {
  if (n < 0 || k < 0) return ModInt<kMod>(0);
  if (n < k) return ModInt<kMod>(0);
  return fact_[n] * fact_inv_[n - k];
}

template<const std::int64_t kMod>
ModInt<kMod> Combination<kMod>::C(int n, int k) const {
  if (k < 0) return ModInt<kMod>(0);
  return P(n, k) * fact_inv_[k];
}

template<const std::int64_t kMod>
ModInt<kMod> Combination<kMod>::H(int n, int k) const {
  if (n < 0 || k < 0) return ModInt<kMod>(0);
  return k == 0 ? 1 : C(n + k - 1, k);
}
