#pragma once

#include <cassert>
#include <vector>

template<typename T>
class CumulativeSum {
 public:
  explicit CumulativeSum(int size);

  void Update(int idx, T value);
  void Build();

  // [0, idx]
  T Sum(int idx);

  // [left, right)
  T Query(int left, int right);
 private:
  int size_;
  std::vector<T> data_;
};

template<typename T>
CumulativeSum<T>::CumulativeSum(int size) : size_(size), data_(size + 1) {}

template<typename T>
void CumulativeSum<T>::Update(int idx, T value) {
  data_[idx] = value;
}

template<typename T>
void CumulativeSum<T>::Build() {
  for (int idx = 1; idx <= size_; ++idx) {
    data_[idx] += data_[idx - 1];
  }
}

template<typename T>
T CumulativeSum<T>::Sum(int idx) {
  return data_[idx];
}

template<typename T>
T CumulativeSum<T>::Query(int left, int right) {
  assert(right > 0);
  assert(left >= 0);
  T ret = Sum(right - 1);
  ret -= (left == 0 ? 0 : Sum(left - 1));
  return ret;
}
