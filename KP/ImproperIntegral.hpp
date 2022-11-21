#ifndef IMPROPER_INTEGRAL
#define IMPROPER_INTEGRAL

#include "General.hpp"

// const std::vector<std::pair<std::string, std::function<double(double, double)>>> ope = {
//     std::make_pair("+", [] (double x, double y) {return x + y;}),
//     std::make_pair("-", [] (double x, double y) {return x - y;}),
//     std::make_pair("*", [] (double x, double y) {return x * y;}),
//     std::make_pair("/", [] (double x, double y) {return x / y;})
// };

std::vector<double> getBreakPoints (const std::function<double(double)> &f, double a, double b);

std::vector<double> getBreakPointsNewton (const std::function<double(double)> &f, double a, double b);

double IntegralSimpson   (const std::function<double(double)> &f, double X1, double X2, double step);

double ImproperIntegral (const std::function<double(double)> &f, double a, double b);

double ImproperIntegral (const std::function<double(double)> &f, double a, double b, const std::vector<double> &points);

#endif