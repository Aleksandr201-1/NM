#ifndef E_HPP
#define E_HPP

#include <cstdint>
#include <cmath>
#include <functional>

double IntegralRectangle (const std::function<double(double)> &f, double X1, double X2, double step);
double IntegralTrapeze   (const std::function<double(double)> &f, double X1, double X2, double step);
double IntegralSimpson   (const std::function<double(double)> &f, double X1, double X2, double step);
double IntegralRunge     (double ans1, double ans2, double k, double p);

#endif