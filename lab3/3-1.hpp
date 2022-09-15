#ifndef A_HPP
#define A_HPP

#include <vector>
#include <cstdint>

enum class Method {
    LAGRANGE,
    NEWTON
};

std::vector<double> Lagrange (const std::vector<double> &X, const std::vector<double> &Y);
double LagrangeFunc (const std::vector<double> &X, const std::vector<double> &W, double x);
void printLagrange (const std::vector<double> &coeff, const std::vector<double> &X, uint64_t countOfElements);


std::vector<double> Newton (const std::vector<double> &X, double (*func)(double));
double NewtonFunc (const std::vector<double> &X, const std::vector<double> &W, double x);
void printNewton (const std::vector<double> &coeff, const std::vector<double> &X, uint64_t countOfElements);

void printPolynom (const std::vector<double> &coeff, const std::vector<double> &X, uint64_t countOfElements, Method method);

#endif