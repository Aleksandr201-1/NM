#include <iostream>
#include <cmath>
#include <vector>
#include "3-1.hpp"

template <class T>
void printVector(const std::vector<T> &vec) {
    for (T el : vec) {
        std::cout << el << " ";
    }
    std::cout << "\n";
}

double y (double x) {
    return std::sin(x * std::acos(-1) / 6.0);
}

std::vector<double> getY (const std::vector<double> &X, double (*func)(double)) {
    std::vector<double> Y;
    for (uint64_t i = 0; i < X.size(); ++i) {
        Y.push_back(func(X[i]));
    }
    return Y;
}

int main () {
    // std::vector<double> X = {0.1, 0.5, 0.9, 1.3};
    std::vector<double> X = {0, 1, 2, 3};
    std::vector<double> Y = getY(X, y);
    std::vector<double> W = Lagrange(X, Y);
    std::vector<double> N = Newton(X, y);
    double check = -0.5;
    printVector(X);
    printVector(Y);
    printVector(W);
    printVector(N);
    std::cout << "\nПогрешность: " << std::abs(LagrangeFunc(X, W, check) - y(check)) << "\n";
    return 0;
}