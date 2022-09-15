#ifndef B_HPP
#define B_HPP

#include <tuple>
#include "General.hpp"
#include "Matrix.hpp"

using System = std::vector<double (*)(const std::vector<double> &)>;

std::tuple<Matrix<double>, Matrix<double>, Matrix<double>> createAAJ (const System &system, const std::vector<double> &x);
std::vector<double> Newton (const System &system, const std::vector<double> &x, double e);

std::vector<double> SI (const System &system, const std::vector<double> &x, double e);

#endif