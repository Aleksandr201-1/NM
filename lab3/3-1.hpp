#ifndef A_HPP
#define A_HPP

#include <vector>
#include <string>
#include <cstdint>
#include "General.hpp"

enum class Method {
    LAGRANGE,
    NEWTON
};

std::vector<double> Lagrange (const std::vector<double> &X, const std::vector<double> &Y);
double LagrangeFunc (const std::vector<double> &X, const std::vector<double> &W, double x);
std::string printLagrange (const std::vector<double> &coeff, const std::vector<double> &X);


std::vector<double> Newton (const std::vector<double> &X, const std::function<double(double)> &func);
double NewtonFunc (const std::vector<double> &X, const std::vector<double> &W, double x);
std::string printNewton (const std::vector<double> &coeff, const std::vector<double> &X);

std::string printPolynom (const std::vector<double> &coeff, const std::vector<double> &X, Method method);

#endif