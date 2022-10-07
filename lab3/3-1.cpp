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

std::string printLagrange (const std::vector<double> &coeff, const std::vector<double> &X) {
    std::string polynom = toString(0.0, PRECISION);
    for (uint64_t i = 0; i < coeff.size(); ++i) {
        if (isEqual(coeff[i], 0.0)) {
            continue;
        }
        if (coeff[i] < 0) {
            polynom += " - " + toString(std::abs(coeff[i]), PRECISION);
        } else {
            polynom += " + " + toString(coeff[i], PRECISION);
        }
        for (uint64_t j = 0; j < X.size(); ++j) {
            if (i == j) {
                continue;
            }
            if (isEqual(X[j], 0.0)) {
                polynom += "x"; 
            } else {
                polynom += "*(x";
                if (X[j] < 0) {
                    polynom += " + " + toString(std::abs(X[j]), PRECISION);
                } else {
                    polynom += " - " + toString(X[j], PRECISION);
                }
                polynom += ")";
            }
        }
    }
    return polynom;
}

std::vector<double> Newton (const std::vector<double> &X, const std::function<double(double)> &func) {
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

double NewtonFunc (const std::vector<double> &X, const std::vector<double> &W, double x) {
    double ans = 0;
    uint64_t index = 0;
    for (uint64_t i = 0; i < X.size(); ++i) {
        double tmp = 1;
        for (uint64_t j = 0; j < i; ++j) {
            tmp *= (x - X[j]);
        }
        tmp *= W[index];
        ans += tmp;
        index += X.size() - i;
    }
    return ans;
}

std::string printNewton (const std::vector<double> &coeff, const std::vector<double> &X) {
    std::string polynom = toString(coeff[0], PRECISION);
    uint64_t index = 0;
    for (uint64_t i = 0; i < X.size() - 1; ++i) {
        index += X.size() - i;
        if (isEqual(coeff[index], 0.0)) {
            continue;
        }
        if (coeff[index] < 0) {
            polynom += " - " + toString(std::abs(coeff[index]), PRECISION);
        } else {
            polynom += " + " + toString(coeff[index], PRECISION);
        }
        for (uint64_t j = 0; j < i + 1; ++j) {
            if (isEqual(X[j], 0.0)) {
                polynom += "x"; 
            } else {
                polynom += "*(x";
                if (X[j] < 0) {
                    polynom += " + " + toString(std::abs(X[j]), PRECISION);
                } else {
                    polynom += " - " + toString(X[j], PRECISION);
                }
                polynom += ")";
            }
        }
    }
    return polynom;
}

std::string printPolynom (const std::vector<double> &coeff, const std::vector<double> &X, Method method) {
    switch (method) {
        case Method::LAGRANGE:
            return printLagrange(coeff, X);
        case Method::NEWTON:
            return printNewton(coeff, X);
        default:
            return "";
    }
}