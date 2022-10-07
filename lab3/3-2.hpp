#ifndef B_HPP
#define B_HPP

#include <vector>
#include <cstdint>
#include <cmath>
#include "Matrix.hpp"
#include "LU.hpp"

Matrix<double> CubeSpline (const std::vector<double> &X, const std::vector<double> &Y);
double CubeSplineFunc (const std::vector<double> &X, const Matrix<double> &M, double x);

#endif