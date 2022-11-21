#include "4-2.hpp"

bool stop (double y_last, double y, double e) {
    return std::abs(y_last - y) < e;
}

double newN (double n_last, double n, const std::vector<double> &ans_last, const std::vector<double> &ans, double y) {
    double phi_last = std::abs(ans_last.back() - y);
    double phi = std::abs(ans.back() - y);
    return n - (n - n_last) / (phi - phi_last) * phi;
}

std::pair<std::vector<double>, std::vector<double>> Shoot (const Task &task, double h) {
    double n = task.X1, n_last = task.X2;
    Task oldTask = task;
    oldTask.a = n_last;
    oldTask.b = n_last;
    auto prev = FiniteDifference(oldTask, h);
    oldTask.a = n;
    oldTask.b = n;
    auto next = FiniteDifference(oldTask, h);
    oldTask.a = task.a;
    uint64_t count = 0;
    while (!stop(next.second.back(), task.b, 0.01)) {
        double tmp = n;
        n = newN(n_last, n, prev.second, next.second, task.b);
        n_last = tmp;
        prev = next;
        oldTask.b = n;
        next = FiniteDifference(oldTask, h);
        ++count;
        if (count > ITERATION_CAP) {
            next.first.clear();
            next.second.clear();
            break;
        }
    }
    return next;
}

std::pair<std::vector<double>, std::vector<double>> FiniteDifference (const Task &task, double h) {
    double X1 = task.X1, X2 = task.X2, a = task.a, b = task.b;
    const std::vector<FunctionalTree> &trees = task.trees;
    
    std::vector<double> X, Y;
    for (double i = X1; i <= X2; i += h) {
        X.push_back(i);
    }
    auto p = [&] (double x) -> double {
        static auto c1 = trees[0].getCoeff(2);
        static auto c2 = trees[0].getCoeff(1);
        return c1(x) / c2(x);
    };
    auto q = [&] (double x) -> double {
        static auto c1 = trees[0].getCoeff(3);
        static auto c2 = trees[0].getCoeff(1);
        return c1(x) / c2(x);
    };
    auto f = [&] (double x) -> double {
        static auto c2 = trees[0].getCoeff(1);
        return trees[1](x) / c2(x);
    };
    uint64_t n = X.size();
    Matrix<double> S(n, n);
    std::vector<double> c(n);
    double c0, c1;

    c0 = trees[2].getCoeff(0)(1);
    c1 = trees[2].getCoeff(1)(1);
    if (c0 == 0.0) {
        S(0, 0) = c1;
        c[0] = a;
    } else {
        S(0, 0) = c1 / c0 * 2 * h - 3;
        S(0, 1) = 4;
        S(0, 2) = -1;
        c[0] = a / c0 * 2 * h;
    }
    for (uint64_t i = 1; i < c.size() - 1; ++i) {
        S(i, i - 1) = 1 - h * p(X[i]) / 2;
        S(i, i) = -2 + h * h * q(X[i]);
        S(i, i + 1) = 1 + h * p(X[i]) / 2;
        c[i] = h * h * f(X[i]);
    }
    c0 = trees[3].getCoeff(0)(1);
    c1 = trees[3].getCoeff(1)(1);
    if (c0 == 0.0) {
        S(n - 1, n - 1) = c1;
        c[n - 1] = b;
    } else {
        S(n - 1, n - 3) = 1;
        S(n - 1, n - 2) = -4;
        S(n - 1, n - 1) = c1 / c0 * 2 * h + 3;
        c[n - 1] = b / c0 * 2 * h;
    }

    c = LUsolveSLAE(S, c);

    for (uint64_t i = 0; i < c.size(); ++i) {
        Y.push_back(c[i]);
    }

    return std::make_pair(X, Y);
}