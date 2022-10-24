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

struct Task {
    std::vector<FunctionalTree> trees;
    double X1, X2;
    double a, c;
    uint64_t leftKind, rightKind;
};

const uint64_t ITERATION_CAP = 20;
const uint64_t PRECISION = 2;

void printVector(const std::vector<double> &vec);

double findEpsillon ();

bool isEqual(double x, double y);

double derivative (const std::function<double(double)> &f, double x, uint64_t degree = 1);

std::string toString (double val, uint64_t precision);

double stringFix (std::string &str);

Task getTaskInfo(const std::vector<std::string> &system, double a, double c);

std::string readLine ();

#endif