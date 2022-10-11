#ifndef B_HPP
#define B_HPP

#include <vector>
#include <functional>
#include "FuncMaker.hpp"
#include "Matrix.hpp"
#include "RUN.hpp"
#include "LU.hpp"

std::pair<std::vector<double>, std::vector<double>> Shoot (const std::function<double(double, double)> &f, double a, double b, double X1, double X2, double h);

std::pair<std::vector<double>, std::vector<double>> FiniteDifference (const std::vector<std::function<double(double)>> &f, double a, double b, double X1, double X2, double h);

std::pair<std::vector<double>, std::vector<double>> FiniteDifference (const std::vector<FunctionalTree> &trees, double a, double b, double X1, double X2, double h);

std::pair<std::vector<double>, std::vector<double>> FiniteDifference (const std::vector<std::string> &system, double h);

#endif