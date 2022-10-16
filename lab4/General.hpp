#ifndef GENERAL_HPP
#define GENERAL_HPP

#include <cmath>
#include <vector>
#include <cstdint>
#include <limits>
#include <stdexcept>
#include <functional>
#include <iostream>
#include "FuncMaker.hpp"

using System = std::vector<std::function<double(const std::vector<double> &)>>;

struct Task {
    std::vector<FunctionalTree> trees;
    double X1, X2, a, b;
};

const uint64_t ITERATION_CAP = 20;
const uint64_t PRECISION = 2;

void printVector(const std::vector<double> &vec);

double findEpsillon ();

bool isEqual(double x, double y);

double derivative (const std::function<double(double)> &f, double x, uint64_t degree = 1);

double derivative (const std::function<double(const std::vector<double> &)> &f, const std::vector<double> &x, uint64_t i);

std::string toString (double val, uint64_t precision);

double stringFix (std::string &str);

Task getTaskInfo(const std::vector<std::string> &system);

double RungeRomberg (double X1, double X2);

#endif