#ifndef A_HPP
#define A_HPP

#include <vector>
#include <functional>
#include "General.hpp"
#include "3-3.hpp"

//std::function<double(double)> Euler (const std::function<double(double)> &y, double a, double b, double X1, double X2, double h);

//std::pair<std::vector<double>, std::vector<double>> Euler (const std::function<double(double, double)> &f, double a, double b, double X1, double X2, double h);
std::pair<std::vector<double>, std::vector<double>> Euler (const Task &task, double h);

//std::pair<std::vector<double>, std::vector<double>> Runge (const std::function<double(double, double)> &f, double a, double b, double X1, double X2, double h);
std::pair<std::vector<double>, std::vector<double>> Runge (const Task &task, double h);

//std::pair<std::vector<double>, std::vector<double>> Adams (const std::function<double(double, double)> &f, double a, double b, double X1, double X2, double h);
std::pair<std::vector<double>, std::vector<double>> Adams (const Task &task, double h);

#endif