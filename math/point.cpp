#include "point.hpp"

#include <cmath>
#include <istream>
#include <math.h>
#include <ostream>

Point::Point() : x_(0), y_(0) {}
Point::Point(double x, double y) : x_(x), y_(y) {}
Point::Point(const Point& pt) : x_(pt.x_), y_(pt.y_) {}

double Point::Dot(const Point& target) const {
  return x_ * target.x_ + y_ * target.y_;
}

double Point::Cross(const Point& target) const {
  return x_ * target.y_ - y_ * target.x_;
}

double Point::Norm() const {
  return std::sqrt(x_ * x_ + y_ * y_);
}

int Point::Orthant() const {
  if (x_ == 0 && y_ == 0) return 1;
  if (x_ > 0) return y_ > 0 ? 1 : 4;
  else return y_ > 0 ? 2 : 3;
}

Point Point::RotateTheta(double theta) const {
  return Point(std::cos(theta) * x_ - std::sin(theta) * y_, std::sin(theta) * x_ + std::cos(theta) * y_);
}

Point& Point::operator+=(const Point& pt) {
  x_ += pt.x_;
  y_ += pt.y_;
  return *this;
}

Point& Point::operator-=(const Point& pt) {
  x_ -= pt.x_;
  y_ -= pt.y_;
  return *this;
}

Point& Point::operator*=(double times) {
  x_ *= times;
  y_ *= times;
  return *this;
}

Point& Point::operator/=(double div) {
  x_ /= div;
  y_ /= div;
  return *this;
}

Point Point::operator+(const Point& pt) const {
  return Point(*this) += pt;
}

Point Point::operator-(const Point& pt) const {
  return Point(*this) -= pt;
}

Point Point::operator*(double times) const {
  return Point(*this) *= times;
}

Point Point::operator/(double div) const {
  return Point(*this) /= div;
}

Point& Point::operator=(const Point& pt) {
  x_ = pt.x_;
  y_ = pt.y_;
  return *this;
}

double Point::Angle() const {
  double ret = std::atan2(y_, x_) * 180.0 / acos(-1);
  if (ret < 0) {
    ret = 360 + ret;
  }
  return ret;
}

bool Point::operator<(const Point& pt) const {
  return Angle() < pt.Angle();
}

std::istream& operator>>(std::istream& stream, Point& pt) {
  return stream >> pt.x_ >> pt.y_;
}

std::ostream& operator<<(std::ostream& stream, const Point& pt) {
  return stream << pt.x_ << " " << pt.y_;
}
