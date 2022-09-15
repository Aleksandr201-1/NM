#include "3-1.hpp"

std::vector<double> Lagrange (const std::vector<double> &X, const std::vector<double> &Y) {
    std::vector<double> W;
    for (uint64_t i = 0; i < X.size(); ++i) {
        double w_el = 1;
        for (uint64_t j = 0; j < i; ++j) {
            w_el *= (X[i] - X[j]);
        }
        for (uint64_t j = i + 1; j < Y.size(); ++j) {
            w_el *= (X[i] - X[j]);
        }
        W.push_back(w_el);
    }
    for (uint64_t i = 0; i < W.size(); ++i) {
        W[i] = Y[i] / W[i];
    }
    return W;
}

double LagrangeFunc (const std::vector<double> &X, const std::vector<double> &W, double x) {
    double ans = 0;
    for (uint64_t i = 0; i < W.size(); ++i) {
        double tmp = 1;
        for (uint64_t j = 0; j < i; ++j) {
            tmp *= (x - X[j]);
        }
        for (uint64_t j = i + 1; j < X.size(); ++j) {
            tmp *= (x - X[j]);
        }
        tmp *= W[i];
        ans += tmp;
    }
    return ans;
}

std::vector<double> Newton (const std::vector<double> &X, double (*func)(double)) {
    std::vector<double> ans;
    for (uint64_t i = 0; i < X.size(); ++i) {
        ans.push_back(func(X[i]));
    }
    uint64_t startIndex = 0;
    for (uint64_t i = 1; i < X.size(); ++i) {
        for (uint64_t j = 0; j < X.size() - i; ++j) {
            double tmp = (ans[startIndex] - ans[startIndex + 1]) / (X[j] - X[i + j]);
            ans.push_back(tmp);
            ++startIndex;
        }
        startIndex += 1;
    }
    return ans;
}

void printPolynom (const std::vector<double> &coeff, const std::vector<double> &X, uint64_t countOfElements, Method method) {
    switch (method) {
        case Method::LAGRANGE:
            printLagrange(coeff, X, countOfElements);
            break;
        case Method::NEWTON:
            printNewton(coeff, X, countOfElements);
            break;
        default:
            break;
    }
}