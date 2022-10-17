#include "2-1.hpp"

bool checkNewton (double x, double (*function)(double)) {
    return function(x) * derivative(function, x, 2) > 0.0;
}

std::pair<double, uint64_t> Newton (double x, double approx, double (*function)(double)) {
    if (!checkNewton(x, function)) {
        throw std::runtime_error("Newton: Incorrect begining point");
    }
    uint64_t count = 1;
    double x2 = x - function(x) / derivative(function, x, 1);
    while (std::abs(x2 - x) > approx) {
        x = x2;
        x2 = x - function(x) / derivative(function, x, 1);
        ++count;
        if (count > ITERATION_CAP) {
            throw std::runtime_error("Newton: the maximum number of iterations has been reached");
        }
    }
    return {x2, count};
}


bool checkSI (double a, double b, double (*function)(double), double q) {
    double e = findEpsillon(), x = a;
    while (x + e < b) {
        x += e;
        if (derivative(function, x) > q) {
            return false;
        }
        if (function(x) < a || function(x) > b) {
            return false;
        }
    }
    return true;
}

std::pair<double, uint64_t> SI (double x, double a, double b, double approx, double (*fi)(double)) {
    double q = std::max(std::abs(derivative(fi, a)), std::abs(derivative(fi, b)));
    if (!checkSI(a, b, fi, q)) {
        throw std::runtime_error("SI: Incorrect function fi(x). fi'(x) > q, x in (a, b) or fi(x) not in (a, b)");
    }
    uint64_t count = 1;
    double x2 = fi(x);
    while ((q / (1 - q)) * (std::abs(x2 - x)) > approx) {
        x = x2;
        x2 = fi(x2);
        ++count;
        if (count > ITERATION_CAP) {
            throw std::runtime_error("SI: the maximum number of iterations has been reached");
        }
    }
    return {fi(x2), count + 1};
}