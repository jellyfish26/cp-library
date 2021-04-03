#pragma once

template<class T>
class Edge {
 public:
  int src_, to_;
  T cost_;

  Edge(int src, int to, T cost);
  Edge(int to, T cost);
  Edge(const Edge& edge);
};

template<class T>
Edge<T>::Edge(int src, int to, T cost) : src_(src), to_(to), cost_(cost) {}

template<class T>
Edge<T>::Edge(int to, T cost) : to_(to), cost_(cost) {}

template<class T>
Edge<T>::Edge(const Edge& edge) : src_(edge.src_), to_(edge.to_), cost_(edge.cost_) {}
