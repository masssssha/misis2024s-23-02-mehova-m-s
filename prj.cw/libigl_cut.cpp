#include <tinysplinecxx.h>
#include <iostream>

int main() {
  tinyspline::BSpline spline_ = tinyspline::BSpline::interpolateCubicNatural(
    {
      -1.0, 0.0, 0.0,
      1.0, 0.0, 0.0,
      2.0, 0.0, 0.0,
      4.0, 0.0, 0.0,

    }, 3);
  int n(10);
  const int n_points = n + 1;
  auto knots = spline_.uniformKnotSeq(n_points);
  auto points = spline_.evalAll(knots);
  double len_spline_(0);
  int x(3), y(4), z(5);
  while (z+1 <= points.size()) {
    len_spline_ += std::sqrt(std::pow(points[x - 3] - points[x], 2) + std::pow(points[y - 3] - points[y], 2) + std::pow(points[z - 3] - points[z], 2));
    x += 3;
    y += 3;
    z += 3;
  }
  double len = len_spline_ / n_points;
  const int tn_points = n_points * 100;
  auto knots2 = spline_.uniformKnotSeq(tn_points);
  auto points2 = spline_.evalAll(knots2);
  int count(0);
  std::cout << len << std::endl;
  int i(0);
  while (count + 1 < n_points) {
    double x2(0), y2(0), z2(0);
    while ((std::sqrt(std::pow(points[count * 3] - points2[i], 2) + std::pow(points[count * 3 + 1] - points2[i + 1], 2) + std::pow(points[count * 3 + 2] - points2[i + 2], 2)) <= len)) {
      x2 = (points2[i] + points2[i + 3]) / 2;
      y2 = (points2[i + 1] + points2[i + 4]) / 2;
      z2 = (points2[i + 2] + points2[i + 5]) / 2;
      i += 3;
    }
    points[count * 3 + 3] = x2;
    points[count * 3 + 4] = y2;
    points[count * 3 + 5] = z2;
    std::cout << points[count * 3 + 3] << " " << points[count * 3 + 4] << " " << points[count * 3 + 5] << std::endl;
    count += 1;
  }
}