#ifndef B_HPP
#define B_HPP

#include <tuple>
#include <functional>
#include "General.hpp"
#include "Matrix.hpp"

using System = std::vector<std::function<double(const std::vector<double> &)>>;

std::tuple<Matrix<double>, Matrix<double>, Matrix<double>> createAAJ (const System &system, const std::vector<double> &x);
std::pair<std::vector<double>, uint64_t> Newton (const System &system, const std::vector<double> &x, double e);

double findQ (const System &system, const std::vector<double> &x);
std::pair<std::vector<double>, uint64_t> SI (const System &system, const std::vector<double> &x, double e);

#endif