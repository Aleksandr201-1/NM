#include "2-2.hpp"
#include <iostream>
std::tuple<Matrix<double>, Matrix<double>, Matrix<double>> createAAJ (const System &system, const std::vector<double> &x) {
    Matrix<double> A1(x.size()), A2(x.size()), J(x.size());
    for (uint64_t i = 0; i < x.size(); ++i) {
        for (uint64_t j = 0; j < x.size(); ++j) {
            J(i, j) = derivative(system[i], x, j);
        }
    }
    A1(0, 0) = system[0](x);
    A1(0, 1) = derivative(system[0], x, 1);
    A1(1, 0) = system[1](x);
    A1(1, 1) = derivative(system[1], x, 1);

    A2(0, 0) = derivative(system[0], x, 0);
    A2(0, 1) = system[0](x);
    A2(1, 0) = derivative(system[1], x, 0);
    A2(1, 1) = system[1](x);

    return std::make_tuple(A1, A2, J);
}

std::pair<std::vector<double>, uint64_t> Newton (const System &system, const std::vector<double> &x, double e) {
    std::vector<double> ans(x);
    uint64_t count = 0;
    Matrix<double> A1, A2, J;
    double maxDiff;
    do {
        maxDiff = 0;
        std::tie(A1, A2, J) = createAAJ(system, ans);
        double Adet[2] = {A1.det(), A2.det()}, Jdet = J.det();
        if (isEqual(Jdet, 0.0)) {
            throw std::runtime_error("Newton: det(J) == 0.0");
        }
        for (uint64_t i = 0; i < ans.size(); ++i) {
            double tmp = ans[i] - Adet[i] / Jdet;
            if (std::abs(tmp - ans[i]) > maxDiff) {
                maxDiff = std::abs(tmp - ans[i]);
            }
            ans[i] = tmp;
        }
        ++count;
        if (count > ITERATION_CAP) {
            throw std::runtime_error("Newton: the maximum number of iterations has been reached");
        }
    } while (maxDiff > e);
    return {ans, count};
}

double findQ (const System &system, const std::vector<double> &x) {
    double q = 0;
    for (uint64_t i = 0; i < x.size(); ++i) {
        double sum = 0;
        for (uint64_t j = 0; j < x.size(); ++j) {
            sum += std::abs(derivative(system[i], x, i));
        }
        if (sum > q) {
            q = sum;
        }
    }
    return q;
}

std::pair<std::vector<double>, uint64_t> SI (const System &system, const std::vector<double> &x, double e) {
    double q = findQ(system, x), maxDiff;
    if (q > 1.0) {
        throw std::runtime_error("SI: q > 1.0");
    }
    std::vector<double> ans(x), tmp(x);
    //for (uint64_t i = 0; i < tmp.size(); ++i) {
    //    tmp[i] += 0.5;
    //}
    uint64_t count = 0;
    //std::cout << "Q: " << q << "\n";
    do {
        maxDiff = 0;
        for (uint64_t i = 0; i < ans.size(); ++i) {
            tmp[i] = system[i](ans);
            if (std::abs(tmp[i] - ans[i]) > maxDiff) {
                maxDiff = std::abs(tmp[i] - ans[i]);
            }
        }
        ans = tmp;
        // for (auto el : ans) {
        //     std::cout << el << " ";
        // }
        // std::cout << "\n";
        ++count;
        if (count > ITERATION_CAP) {
            throw std::runtime_error("SI: the maximum number of iterations has been reached");
        }
    } while ((q / (1 - q)) * maxDiff > e);
    return {ans, count};
}