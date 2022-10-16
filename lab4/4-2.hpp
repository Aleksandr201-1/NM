#ifndef B_HPP
#define B_HPP

#include <vector>
#include <functional>
#include "General.hpp"
#include "Matrix.hpp"
#include "RUN.hpp"
#include "LU.hpp"
#include "4-1.hpp"

std::pair<std::vector<double>, std::vector<double>> Shoot (const Task &task, double h);

std::pair<std::vector<double>, std::vector<double>> FiniteDifference (const Task &task, double h);

#endif