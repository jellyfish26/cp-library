#pragma once

#include <vector>

template<typename T>
class CumulativeSum2D {
 public:
   CumulativeSum2D(int H, int W);

   void Build();
   void Update(int h, int w, T value);

   // Index 1-based
   T Sum(int h, int w);
   T Query(int down_h, int down_w, int up_h, int up_w);

 private:
   int H_, W_;
   std::vector<std::vector<T>> data_;
};

template<typename T>
CumulativeSum2D<T>::CumulativeSum2D(int H, int W) : H_(H + 1), W_(W + 1), data_(H + 1, std::vector<T>(W + 1)) {}

template<typename T>
void CumulativeSum2D<T>::Build() {
  for (int h = 0; h < H_; ++h) {
    for (int w = 1; w < W_; ++w) {
      data_[h][w] += data_[h][w - 1];
    }
  }
  for (int w = 0; w < W_; ++w) {
    for (int h = 1; h < H_; ++h) {
      data_[h][w] += data_[h - 1][w];
    }
  }
}

template<typename T>
void CumulativeSum2D<T>::Update(int h, int w, T value) {
  data_[h + 1][w + 1] = value;
}

template<typename T>
T CumulativeSum2D<T>::Sum(int h, int w) {
  return data_[h][w];
}

template<typename T>
T CumulativeSum2D<T>::Query(int down_h, int down_w, int up_h, int up_w) {
  T ret = Sum(up_h + 1, up_w + 1);
  ret -= Sum(down_h, up_w + 1);
  ret -= Sum(up_h + 1, down_w);
  ret += Sum(down_h, down_w);
  return ret;
}


