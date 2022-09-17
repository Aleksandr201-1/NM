#ifndef A_HPP
#define A_HPP

#include <utility>
#include "General.hpp"

bool checkNewton (double x, double (*function)(double));

std::pair<double, uint64_t> Newton (double x, double approx, double (*function)(double));

bool checkSI (double a, double b, double (*function)(double));

std::pair<double, uint64_t> SI (double x, double a, double b, double approx, double (*fi)(double));

#endif