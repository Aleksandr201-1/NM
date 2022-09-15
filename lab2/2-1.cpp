#include "2-1.hpp"

bool checkNewton (double x, double (*function)(double)) {
    return function(x) * derivative(function, x, 2) > 0;
}

std::pair<double, uint64_t> Newton (double x, double approx, double (*function)(double)) {
    //double q = std::max(std::abs(dif_fi(a)), std::abs(dif_fi(b)));
    uint64_t count = 1;
    double x2 = x - function(x) / derivative(function, x, 1);
    while (std::abs(x2 - x) > approx) {
        x = x2;
        x2 = x - function(x) / derivative(function, x, 1);
        ++count;
    }
    return {x2, count};
}

std::pair<double, uint64_t> simple_iteration (double x, double a, double b, double approx, double (*fi)(double)) {
    double q = std::max(std::abs(derivative(fi, a, 1)), std::abs(derivative(fi, b, 1)));
    uint64_t count = 1;
    double x2 = fi(x);
    while ((std::abs(q / (1 - q)) * std::abs(x2 - x)) > approx) {
        x = x2;
        x2 = fi(x2);
        ++count;
    }
    return {fi(x2), count};
}