#include "3-4.hpp"

double derirative1 (const std::vector<double> &X, const std::vector<double> &Y, double x) {
    double ans = 0;
    uint64_t left = 0, right = 0;
    for (uint64_t i = 0; i < X.size(); ++i) {
        if (x <= X[i]) {
            right = i;
            break;
        }
        left = i;
    }
    ans = (2 * x - X[left] - X[right]);
    ans *= ((Y[right + 1] - Y[left + 1]) / (X[right + 1] - X[left + 1]) - (Y[right] - Y[left]) / (X[right] - X[left])) / (X[right + 1] - X[left]);
    ans += (Y[right] - Y[left]) / (X[right] - X[left]);
    return ans;
}

double derirative2 (const std::vector<double> &X, const std::vector<double> &Y, double x) {
    double ans = 0;
    uint64_t left = 0, right = 0;
    for (uint64_t i = 0; i < X.size(); ++i) {
        if (x <= X[i]) {
            right = i;
            break;
        }
        left = i;
    }
    ans = ((Y[right + 1] - Y[left + 1]) / (X[right + 1] - X[left + 1]) - (Y[right] - Y[left]) / (X[right] - X[left])) / (X[right + 1] - X[left]);
    ans *= 2;
    return ans;
}