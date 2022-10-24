#include "General.hpp"

void printVector(const std::vector<double> &vec) {
    for (double el : vec) {
        std::cout << el << " ";
    }
    std::cout << "\n";
}

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

std::string toString (double val, uint64_t precision) {
    return std::to_string(val).substr(0, std::to_string(val).find(".") + precision + 1);
}