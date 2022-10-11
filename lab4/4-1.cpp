#include "4-1.hpp"

// std::function<double(double)> Euler (const std::function<double(double)> &y, double a, double b, double X1, double X2, double h) {
//     auto func_maker = [] (const std::vector<double> &X, const std::vector<double> &Y) {
//         return [=] (double x) {
//             static const std::vector<double> V = LeastSquareMethod(X, Y, 5);
//             return LSMFunc(V, x); 
//         };
//     };
//     std::vector<double> X, Y;
//     for (double i = X1; i <= X2; i += h) {
//         X.push_back(i);
//     }
//     printVector(X);
//     for (uint64_t i = 0; i < X.size(); ++i) {
//         Y.push_back(y(X[i]) + a + b);
//     }
//     printVector(Y);
//     return func_maker(X, Y);
// }

std::pair<std::vector<double>, std::vector<double>> Euler (const std::function<double(double, double)> &f, double a, double b, double X1, double X2, double h) {
    std::vector<double> X, Y;
    for (double i = X1; i <= X2; i += h) {
        X.push_back(i);
    }
    Y.push_back(a + b);
    for (uint64_t i = 1; i < X.size(); ++i) {
        double x_h = X[i - 1] + h  / 2;
        double y_h = Y[i - 1] + h / 2 * f(X[i - 1], Y[i - 1]);
        Y.push_back(Y[i - 1] + h * f(x_h, y_h));
    }
    return std::make_pair(X, Y);
}

std::pair<std::vector<double>, std::vector<double>> Runge (const std::function<double(double, double)> &f, double a, double b, double X1, double X2, double h) {
    std::vector<double> X, Y;
    for (double i = X1; i <= X2; i += h) {
        X.push_back(i);
    }
    Y.push_back(a + b);
    for (uint64_t i = 1; i < X.size(); ++i) {
        double delta_y;
        double K1 = h * f(X[i - 1], Y[i - 1]);
        double K2 = h * f(X[i - 1] + 1.0 / 2.0 * h, Y[i - 1] + 1.0 / 2.0 * K1);
        double K3 = h * f(X[i - 1] + 1.0 / 2.0 * h, Y[i - 1] + 1.0 / 2.0 * K2);
        double K4 = h * f(X[i - 1] + h, Y[i - 1] + K3);
        delta_y = 1.0 / 6.0 * (K1 + 2 * K2 + 2 * K3 + K4);
        Y.push_back(Y[i - 1] + delta_y);
    }
    return std::make_pair(X, Y);
}

std::pair<std::vector<double>, std::vector<double>> Adams (const std::function<double(double, double)> &f, double a, double b, double X1, double X2, double h) {
    std::vector<double> X, Y;
    for (double i = X1; i <= X2; i += h) {
        X.push_back(i);
    }
    Y.push_back(a + b);
    Y = Runge(f, a, b, X1, X1 + h * 3, h).second;
    for (uint64_t i = 4; i < X.size(); ++i) {
        double f1 = f(X[i - 1], Y[i - 1]);
        double f2 = f(X[i - 2], Y[i - 2]);
        double f3 = f(X[i - 3], Y[i - 3]);
        double f4 = f(X[i - 4], Y[i - 4]);
        double delta_y = Y[i - 1] + h / 24.0 * (55 * f1 - 59 * f2 + 37 * f3 - 9 * f4);

        Y.push_back(Y[i - 1] + h / 24.0 * (9 * f(X[i], delta_y) + 19 * f1 - 5 * f2 + f3));
    }
    return std::make_pair(X, Y);
}