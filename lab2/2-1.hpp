#ifndef A_HPP
#define A_HPP

#include <utility>
#include "General.hpp"

bool checkNewton (double x, double (*function)(double));

std::pair<double, uint64_t> Newton (double x, double approx, double (*function)(double));

std::pair<double, uint64_t> simple_iteration (double x, double a, double b, double approx, double (*fi)(double));

#endif