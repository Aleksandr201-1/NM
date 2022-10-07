#ifndef C_HPP
#define C_HPP

#include <vector>
#include <cstdint>
#include <functional>
#include "LU.hpp"

std::vector<double> LeastSquareMethod (const std::vector<double> &X, const std::vector<double> &Y, uint64_t n);

double ErrorSquareSum (const std::vector<double> &X, const std::vector<double> &Y, const std::vector<double> &poly);

std::string LSMToText (const std::vector<double> &poly);

#endif