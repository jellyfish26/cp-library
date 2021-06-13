#pragma once
#include <functional>
#include <queue>
#include <tuple>
#include <utility>
#include <vector>

#include "edge.hpp"

template<class T>
class Dijkstra {
 public:
  using Graph = std::vector<std::vector<Edge<T>>>;
  Dijkstra(const Graph& graph, T inf);

  const std::vector<T>& Calc(int start);

 private:
  const Graph& graph_;
  const T kInf_;
  std::vector<T> dist_;
};

template<class T>
Dijkstra<T>::Dijkstra(const Graph& graph, T inf) : graph_(graph), kInf_(inf) {}

template<class T>
const std::vector<T>& Dijkstra<T>::Calc(int start) {
  dist_ = std::vector<T>(graph_.size(), kInf_);

  std::priority_queue<std::pair<T, int>,
                      std::vector<std::pair<T, int>>,
                      std::greater<std::pair<T, int>>> next_edges;
  dist_[start] = 0;
  next_edges.emplace(dist_[start], start);
  while (!next_edges.empty()) {
    T now_cost;
    int now_vertex;
    std::tie(now_cost, now_vertex) = next_edges.top();
    next_edges.pop();

    if (dist_[now_vertex] < now_cost) continue;

    for (const Edge<T>& next_edge : graph_[now_vertex]) {
      T next_cost = now_cost + next_edge.cost_;
      if (dist_[next_edge.to_] <= next_cost) continue;

      dist_[next_edge.to_] = next_cost;
      next_edges.emplace(next_cost, next_edge.to_);
    }
  }
  return dist_;
}
