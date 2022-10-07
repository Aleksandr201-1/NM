#include "3-5.hpp"

double IntegralRectangle (const std::function<double(double)> &f, double X1, double X2, double step) {
    double ans = 0;
    uint64_t size = (X2 - X1) / step;
    for (uint64_t i = 0; i < size; ++i) {
        ans += f((X1 * 2 + step) / 2) * step;
        X1 += step;
    }
    return ans;
}

double IntegralTrapeze (const std::function<double(double)> &f, double X1, double X2, double step) {
    double ans = 0;
    uint64_t size = (X2 - X1) / step;
    ans = f(X1) + f(X2);
    ans /= 2;
    for (uint64_t i = 1; i < size; ++i) {
        ans += f(X1 + i * step);
    }
    ans *= step;
    return ans;
}

double IntegralSimpson (const std::function<double(double)> &f, double X1, double X2, double step) {
    double ans = 0;
    uint64_t size = (X2 - X1) / step;
    ans += f(X1) + f(X2);
    for (uint64_t i = 1; i < size; ++i) {
        ans += f(X1 + step * i) * (i & 1 ? 4 : 2);
    }
    ans *= step / 3;
    return ans;
}

double IntegralRunge (double ans1, double ans2, double k, double p) {
    return std::abs((ans1 - ans2) / (std::pow(k, p) - 1));
    //return ans1 + (ans1 - ans2) / (std::pow(k, p) - 1);
}