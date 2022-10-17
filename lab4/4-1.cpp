#include "4-1.hpp"

std::pair<std::vector<double>, std::vector<double>> Euler (const Task &task, double h) {
    double X1 = task.X1, X2 = task.X2, a = task.a, b = task.b;
    const std::vector<FunctionalTree> &trees = task.trees;

    std::vector<double> X, Y;
    for (double i = X1; i <= X2; i += h) {
        X.push_back(i);
    }
    Y.push_back(a);
    double z = b;
    auto g = [&] (double x, double y, double z) -> double {
        static auto c2 = trees[0].getCoeff(1);
        return -trees[0]({x, 0, z, y}) / c2(x);
    };

    for (uint64_t i = 1; i < X.size(); ++i) {
        z += h * g(X[i - 1], Y[i - 1], z);
        Y.push_back(Y[i - 1] + h * z);
    }
    return std::make_pair(X, Y);
}

std::pair<std::vector<double>, std::vector<double>> Runge (const Task &task, double h) {
    double X1 = task.X1, X2 = task.X2, a = task.a, b = task.b;
    const std::vector<FunctionalTree> &trees = task.trees;

    std::vector<double> X, Y, Z;
    for (double i = X1; i <= X2; i += h) {
        X.push_back(i);
    }
    Y.push_back(a);
    Z.push_back(b);
    auto g = [&] (double x, double y, double z) -> double {
        static auto c2 = trees[0].getCoeff(1);
        return -trees[0]({x, 0, z, y}) / c2(x);
    };
    for (uint64_t i = 1; i < X.size(); ++i) {
        double delta_y, delta_z;
        double K1 = h * Z[i - 1];
        double L1 = h * g(X[i - 1], Y[i - 1], Z[i - 1]);
        double K2 = h * (Z[i - 1] + 1.0 / 2.0 * L1);
        double L2 = h * g(X[i - 1] + 1.0 / 2.0 * h, Y[i - 1] + 1.0 / 2.0 * K1, Z[i - 1] + 1.0 / 2.0 * L1);
        double K3 = h * (Z[i - 1] + 1.0 / 2.0 * L2);
        double L3 = h * g(X[i - 1] + 1.0 / 2.0 * h, Y[i - 1] + 1.0 / 2.0 * K2, Z[i - 1] + 1.0 / 2.0 * L2);
        double K4 = h * (Z[i - 1] + L3);
        double L4 = h * g(X[i - 1] + h, Y[i - 1] + K3, Z[i - 1] + L3);
        delta_y = 1.0 / 6.0 * (K1 + 2 * K2 + 2 * K3 + K4);
        delta_z = 1.0 / 6.0 * (L1 + 2 * L2 + 2 * L3 + L4);
        Y.push_back(Y[i - 1] + delta_y);
        Z.push_back(Z[i - 1] + delta_z);
    }
    return std::make_pair(X, Y);
}

std::pair<std::vector<double>, std::vector<double>> Adams (const Task &task, double h) {
    double X1 = task.X1, X2 = task.X2, a = task.a, b = task.b;
    const std::vector<FunctionalTree> &trees = task.trees;

    std::vector<double> X, Y, Z;
    for (double i = X1; i <= X2; i += h) {
        X.push_back(i);
    }
    Y.push_back(a);
    Z.push_back(b);
    auto g = [&] (double x, double y, double z) -> double {
        static auto c2 = trees[0].getCoeff(1);
        return -trees[0]({x, 0, z, y}) / c2(x);
    };
    for (uint64_t i = 1; i < 4; ++i) {
        double delta_y, delta_z;
        double K1 = h * Z[i - 1];
        double L1 = h * g(X[i - 1], Y[i - 1], Z[i - 1]);
        double K2 = h * (Z[i - 1] + 1.0 / 2.0 * L1);
        double L2 = h * g(X[i - 1] + 1.0 / 2.0 * h, Y[i - 1] + 1.0 / 2.0 * K1, Z[i - 1] + 1.0 / 2.0 * L1);
        double K3 = h * (Z[i - 1] + 1.0 / 2.0 * L2);
        double L3 = h * g(X[i - 1] + 1.0 / 2.0 * h, Y[i - 1] + 1.0 / 2.0 * K2, Z[i - 1] + 1.0 / 2.0 * L2);
        double K4 = h * (Z[i - 1] + L3);
        double L4 = h * g(X[i - 1] + h, Y[i - 1] + K3, Z[i - 1] + L3);
        delta_y = 1.0 / 6.0 * (K1 + 2 * K2 + 2 * K3 + K4);
        delta_z = 1.0 / 6.0 * (L1 + 2 * L2 + 2 * L3 + L4);
        Y.push_back(Y[i - 1] + delta_y);
        Z.push_back(Z[i - 1] + delta_z);
    }
    for (uint64_t i = 4; i < X.size(); ++i) {
        double f1 = g(X[i - 1], Y[i - 1], Z[i - 1]);
        double f2 = g(X[i - 2], Y[i - 2], Z[i - 2]);
        double f3 = g(X[i - 3], Y[i - 3], Z[i - 3]);
        double f4 = g(X[i - 4], Y[i - 4], Z[i - 4]);
        double delta_y = Y[i - 1] + h / 24.0 * (55 * Z[i - 1] - 59 * Z[i - 2] + 37 * Z[i - 3] - 9 * Z[i - 4]);
        double delta_z = Z[i - 1] + h / 24.0 * (55 * f1 - 59 * f2 + 37 * f3 - 9 * f4);
        double f0 = g(X[i], delta_y, delta_z);
        Z.push_back(Z[i - 1] + h / 24.0 * (9 * f0 + 19 * f1 - 5 * f2 + f3));
        Y.push_back(Y[i - 1] + h / 24.0 * (9 * Z[i] + 19 * Z[i - 1] - 5 * Z[i - 2] + Z[i - 3]));
    }
    return std::make_pair(X, Y);
}