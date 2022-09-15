#ifndef GENERAL_HPP
#define GENERAL_HPP

#include <cmath>
#include <vector>
#include <cstdint>

double findEpsillon ();

double derivative (double (*f)(double), double x, uint64_t degree = 1);

double derivative (double (*f)(const std::vector<double>&), const std::vector<double> &x, uint64_t i);

#endif