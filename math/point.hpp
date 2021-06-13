#pragma once

#include <istream>
#include <ostream>

class Point {
 public:
  Point();
  Point(double x, double y);
  Point(const Point& pt);

  double Dot(const Point& target) const;
  double Cross(const Point& target) const;

  double Norm() const;
  int Orthant() const;

  Point RotateTheta(double theta) const;

  Point& operator+=(const Point& pt);
  Point& operator-=(const Point& pt);
  Point& operator*=(double times);
  Point& operator/=(double div);
  Point operator+(const Point& pt) const;
  Point operator-(const Point& pt) const;
  Point operator*(double times) const;
  Point operator/(double div) const;

  Point& operator=(const Point& pt);
  double Angle() const;

  bool operator<(const Point& pt) const;

  friend std::istream& operator>>(std::istream& stream, Point& pt);
  friend std::ostream& operator<<(std::ostream& stream, const Point& pt);

 protected:
  double x_, y_;
};

