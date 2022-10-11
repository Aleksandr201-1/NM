#include "4-2.hpp"

std::pair<std::vector<double>, std::vector<double>> Shoot (const std::function<double(double, double)> &f, double a, double b, double X1, double X2, double h) {
    return {{f(a, b)}, {f(X1 + h, X2)}};
}

std::pair<std::vector<double>, std::vector<double>> FiniteDifference (const std::vector<std::function<double(double)>> &f, double a, double b, double X1, double X2, double h) {
    std::vector<double> X, Y;
    for (double i = X1; i <= X2; i += h) {
        X.push_back(i);
    }
    uint64_t n = X.size();
    std::cout << "size: " << n << "\n";
    //Y.push_back(f[0](a + b));
    //Y.push_back(f[0](X1 + h + X2));
    Matrix<double> S(n - 1, n - 1);
    std::vector<double> c(n - 1);
    S(0, 0) = -2 + h * h * f[1](X[1]);
    S(0, 1) = 1 + h * f[0](X[1]) / 2;
    c[0] = h * h * f[2](X[1]) - (1 - h * f[0](X[1]) / 2) * a;
    for (uint64_t i = 1; i < c.size() - 1; ++i) {
        S(i, i - 1) = 1 - h * f[0](X[i + 1]) / 2;
        S(i, i) = -2 + h * h * f[1](X[i + 1]);
        S(i, i + 1) = 1 + h * f[0](X[i + 1]) / 2;
        c[i] = h * h * f[2](X[i + 1]);
    }
    S(n - 2, n - 3) = 1 - h * f[0](X[n - 1]) / 2;
    S(n - 2, n - 2) = -2 + h * h * f[1](X[n - 1]);
    c[n - 2] = h * h + f[2](X[n - 1]) - (1 + h * f[0](X[n - 1]) / 2) * b;
    printVector(c);
    c = RUNsolveSLAE(S, c);

    Y.push_back(a);
    for (uint64_t i = 0; i < c.size(); ++i) {
        Y.push_back(c[i]);
    }
    Y.push_back(b);

    std::cout << "Matrix:\n" << S << "\n";
    printVector(c);
    std::cout << "\n";
    // Y.push_back(a + b);
    // return std::make_pair(X, Y);
    return std::make_pair(X, Y);
}

double stringFix (std::string &str) {
    double val = 0;
    std::string tmp(str);
    str = "";
    for (uint64_t i = 0; i < tmp.size(); ++i) {
        if (tmp[i] == 'y') {
            std::string valStr;
            while (tmp[i] != '(') {
                str += tmp[i];
                ++i;
            }
            ++i;
            while (tmp[i] != ')') {
                valStr += tmp[i];
                ++i;
            }
            val = std::atof(valStr.c_str());
        } else {
            str += tmp[i];
        }
    }
    return val;
}

std::pair<std::vector<double>, std::vector<double>> FiniteDifferenceQ (const std::vector<FunctionalTree> &trees, double a, double b, double X1, double X2, double h) {
    std::vector<double> X, Y;
    for (double i = X1; i <= X2; i += h) {
        X.push_back(i);
    }
    std::cout << "y'': "; trees[0].getCoeff(1).printFunc(); std::cout << "\n";
    std::cout << "y': "; trees[0].getCoeff(2).printFunc(); std::cout << "\n";
    std::cout << "y: "; trees[0].getCoeff(3).printFunc(); std::cout << "\n";
    std::cout << "func ans: " << trees[0].getCoeff(1)(2) << "\n";
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
    std::cout << "func check: " << p(2) << " " << q(2) << " " << f(2) << "\n";
    uint64_t n = X.size() - 1;
    std::cout << "size: " << n << "\n";
    //Y.push_back(f[0](a + b));
    //Y.push_back(f[0](X1 + h + X2));
    Matrix<double> S(n, n);
    std::vector<double> c(n);
    double c0, c1;

    c0 = trees[2].getCoeff(0)(1);
    c1 = trees[2].getCoeff(1)(1);
    if (c0 == 0.0) {
        //std::cout << "woo\n";
        S(0, 0) = -2 + h * h * q(X[1]);
        S(0, 1) = 1 + h * p(X[1]) / 2;
        c[0] = h * h * f(X[1]) - (1 - h * p(X[1]) / 2) * a;
    } else {
        S(0, 0) = c1 / c0 * h - 1;
        S(0, 1) = 1;
        c[0] = a / c0 * h;
    }
    for (uint64_t i = 1; i < c.size() - 1; ++i) {
        //std::cout << "bug[" << X[i + 1] << "]: " << p(X[i + 1]) / 2 << "\n";
        S(i, i - 1) = 1 - h * p(X[i + 1]) / 2;
        S(i, i) = -2 + h * h * q(X[i + 1]);
        S(i, i + 1) = 1 + h * p(X[i + 1]) / 2;
        c[i] = h * h * f(X[i + 1]);
    }
    c0 = trees[3].getCoeff(0)(1);
    c1 = trees[3].getCoeff(1)(1);
    if (c0 == 0.0) {
        //std::cout << "wee\n";
        S(n - 1, n - 2) = 1 - h * p(X[n - 1]) / 2;
        S(n - 1, n - 1) = -2 + h * h * q(X[n - 1]);
        c[n - 1] = h * h + f(X[n - 1]) - (1 + h * p(X[n - 1]) / 2) * b;
    } else {
        S(n - 1, n - 2) = -1;
        S(n - 1, n - 1) = c1 / c0 * h + 1;
        c[n - 1] = b / c0 * h;
    }

    printVector(c);
    //c = LUsolveSLAE(S, c);
    c = RUNsolveSLAE(S, c);

    //Y.push_back(c[0] - a*h);
    Y.push_back(a);
    for (uint64_t i = 0; i < c.size(); ++i) {
        Y.push_back(c[i]);
    }
    //Y.push_back(b);

    std::cout << "Matrix:\n" << S << "\nVector:\n";
    printVector(c);
    std::cout << "\n";
    // Y.push_back(a + b);
    // return std::make_pair(X, Y);
    return std::make_pair(X, Y);
}

std::pair<std::vector<double>, std::vector<double>> FiniteDifference (const std::vector<FunctionalTree> &trees, double a, double b, double X1, double X2, double h) {
    std::vector<double> X, Y;
    for (double i = X1; i <= X2; i += h) {
        X.push_back(i);
    }
    // std::cout << "y'': "; trees[0].getCoeff(1).printFunc(); std::cout << "\n";
    // std::cout << "y': "; trees[0].getCoeff(2).printFunc(); std::cout << "\n";
    // std::cout << "y: "; trees[0].getCoeff(3).printFunc(); std::cout << "\n";
    // std::cout << "func ans: " << trees[0].getCoeff(1)(2) << "\n";
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
    //std::cout << "func check: " << p(2) << " " << q(2) << " " << f(2) << "\n";
    uint64_t n = X.size();// - 1;
    //std::cout << "size: " << n << "\n";
    //Y.push_back(f[0](a + b));
    //Y.push_back(f[0](X1 + h + X2));
    Matrix<double> S(n, n);
    std::vector<double> c(n);
    double c0, c1;

    c0 = trees[2].getCoeff(0)(1);
    c1 = trees[2].getCoeff(1)(1);
    if (c0 == 0.0) {
        S(0, 0) = c1;
        c[0] = a;
    } else {
        // S(0, 0) = c1 / c0 * h - 1;
        // S(0, 1) = 1;
        // c[0] = a / c0 * h;
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
        // S(n - 1, n - 2) = -1;
        // S(n - 1, n - 1) = c1 / c0 * h + 1;
        // c[n - 1] = b / c0 * h;
        S(n - 1, n - 3) = 1;
        S(n - 1, n - 2) = -4;
        S(n - 1, n - 1) = c1 / c0 * 2 * h + 3;
        c[n - 1] = b / c0 * 2 * h;
    }

    //printVector(c);
    //c = RUNsolveSLAE(S, c);
    c = LUsolveSLAE(S, c);

    //Y.push_back(c[0] - a*h);
    //Y.push_back(a);
    for (uint64_t i = 0; i < c.size(); ++i) {
        Y.push_back(c[i]);
    }
    //Y.push_back(b);

    //std::cout << "Matrix:\n" << S << "\nVector:\n";
    //printVector(c);
    //std::cout << "\n";
    return std::make_pair(X, Y);
}

std::pair<std::vector<double>, std::vector<double>> FiniteDifference (const std::vector<std::string> &system, double h) {
    uint64_t idx = 0, size = 0;
    double a, b, X1, X2;
    std::vector<FunctionalTree> trees;

    idx = system[0].find('=');
    size = system[0].size();
    //std::cout << system[0].substr(0, idx) << "||" << system[0].substr(idx + 1, size - idx) << "\n";
    trees.push_back(std::move(FunctionalTree(system[0].substr(0, idx), {"x", "y''", "y'", "y"})));
    trees.push_back(std::move(FunctionalTree(system[0].substr(idx + 1, size - idx), {"x"})));

    idx = system[1].find('=');
    size = system[1].size();
    std::string tmp = system[1].substr(0, idx);
    X1 = stringFix(tmp);
    a = FunctionalTree(system[1].substr(idx + 1, size - idx), {}).func(0);
    trees.push_back(std::move(FunctionalTree(tmp, {"y'", "y"})));
    //std::cout << tmp << "||" << system[1].substr(idx + 1, size - idx) << "\n";

    idx = system[2].find('=');
    size = system[2].size();
    tmp = system[2].substr(0, idx);
    X2 = stringFix(tmp);
    b = FunctionalTree(system[2].substr(idx + 1, size - idx), {}).func(0);
    trees.push_back(std::move(FunctionalTree(tmp, {"y'", "y"})));
    //std::cout << tmp << "||" << system[2].substr(idx + 1, size - idx) << "\n";

    //FunctionalTree tree1(system[0].substr(0, idx), "x"), tree2, tree3;
    //std::cout << "Needed info: " << X1 << " " << X2 << " " << a << " " << b << "\n\n";
    return FiniteDifference(trees, a, b, X1, X2, h);
}