#ifndef B_HPP
#define B_HPP

#include <vector>
#include <cstdint>

std::vector<double> CubeSpline (const std::vector<double> &X, const std::vector<double> &Y);
double CubeSplineFunc (const std::vector<double> &X, const std::vector<double> &W, double x);

void printPolynom (const std::vector<double> &vec, uint64_t countOfElements);

#endif