#ifndef GENERAL_HPP
#define GENERAL_HPP

#include <cmath>
#include <vector>
#include <cstdint>
#include <limits>
#include <stdexcept>
#include <functional>

const uint64_t ITERATION_CAP = 20;

double findEpsillon ();

bool isEqual(double x, double y);

double derivative (const std::function<double(double)> &f, double x, uint64_t degree = 1);

double derivative (const std::function<double(const std::vector<double> &)> &f, const std::vector<double> &x, uint64_t i);

#endif