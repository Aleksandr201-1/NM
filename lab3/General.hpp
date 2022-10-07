#ifndef GENERAL_HPP
#define GENERAL_HPP

#include <cmath>
#include <vector>
#include <cstdint>
#include <limits>
#include <stdexcept>
#include <functional>
#include <iostream>

using System = std::vector<std::function<double(const std::vector<double> &)>>;

const uint64_t ITERATION_CAP = 20;
const uint64_t PRECISION = 2;

void printVector(const std::vector<double> &vec);

double findEpsillon ();

bool isEqual(double x, double y);

double derivative (const std::function<double(double)> &f, double x, uint64_t degree = 1);

double derivative (const std::function<double(const std::vector<double> &)> &f, const std::vector<double> &x, uint64_t i);

std::string toString (double val, uint64_t precision);

#endif