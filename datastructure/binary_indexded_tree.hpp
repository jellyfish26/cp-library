#pragma once
#include <cstddef>
#include <vector>

template<class T>
class BinaryIndexdedTree {
 public:
  explicit BinaryIndexdedTree(std::size_t size);

  void Add(std::size_t idx, T value);

  T Sum(std::size_t idx) const;
  T SumAll() const;

  T Query(std::size_t left_idx, std::size_t right_idx) const;

 private:
  std::vector<T> data_;
  std::size_t size_;
};

template<class T>
BinaryIndexdedTree<T>::BinaryIndexdedTree(std::size_t size)
    : data_(size + 1), size_(size) {}

template<class T>
void BinaryIndexdedTree<T>::Add(std::size_t idx, T value) {
  for (std::size_t update_idx = idx + 1; update_idx < data_.size(); update_idx += (update_idx & -update_idx)) {
    data_[update_idx] += value;
  }
}

template<class T>
T BinaryIndexdedTree<T>::Sum(std::size_t idx) const {
  T ret = 0;
  for (std::size_t ref_idx = idx + 1; ref_idx > 0; ref_idx -= (ref_idx & -ref_idx)) {
    ret += data_[ref_idx];
  }
  return ret;
}

template<class T>
T BinaryIndexdedTree<T>::SumAll() const {
  return Sum(size_ - 1);
}

template<class T>
T BinaryIndexdedTree<T>::Query(std::size_t left_idx, std::size_t right_idx) const {
  T ret = 0;
  ret += (right_idx == 0 ? 0 : Sum(right_idx - 1));
  ret -= (left_idx == 0 ? 0 : Sum(left_idx - 1));
  return ret;
}
