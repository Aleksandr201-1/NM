#include "General.hpp"

double findEpsillon () {
    return std::pow(__DBL_EPSILON__, 1.0 / 3) * 10;
}

bool isEqual(double x, double y) {
    return std::fabs(x - y) < std::numeric_limits<double>::epsilon();
}

double derivative (const std::function<double(double)> &f, double x, uint64_t degree) {
    static double eps = findEpsillon();
    if (degree == 1) {
        return (f(x + eps) - f(x - eps)) / (2 * eps);
    }
    return (derivative(f, x + eps, degree - 1) - derivative(f, x - eps, degree - 1)) / (2 * eps);
}

double derivative (const std::function<double(const std::vector<double> &)> &f, const std::vector<double> &x, uint64_t i) {
    static double eps = findEpsillon();
    std::vector<double> tmp = x;
    double f1 = 0, f2 = 0;
    tmp[i] += eps;
    f1 = f(tmp);
    tmp[i] -= 2 * eps;
    f2 = f(tmp);
    //if (degree == 1) {
    return (f1 - f2) / (2 * eps);
    //}
    //return (derivative(f, x, degree - 1) - derivative(f, x, degree - 1)) / (2 * eps);
}