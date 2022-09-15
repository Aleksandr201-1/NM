#include "2-2.hpp"

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

std::vector<double> Newton (const System &system, const std::vector<double> &x, double e) {
    std::vector<double> ans(x);
    Matrix<double> A1, A2, J;
    double maxDiff;
    do {
        maxDiff = 0;
        //std::cout << "Creating AAJ\n";
        std::tie(A1, A2, J) = createAAJ(system, ans);
        double Adet[2] = {A1.det(), A2.det()}, Jdet = J.det();
        for (uint64_t i = 0; i < ans.size(); ++i) {
            double tmp = ans[i] - Adet[i] / Jdet;
            if (std::abs(tmp - ans[i]) > maxDiff) {
                maxDiff = std::abs(tmp);
            }
            ans[i] = tmp;
        }
    } while (maxDiff > e);
    return ans;
}

std::vector<double> SI (const System &system, const std::vector<double> &x, double e) {
    std::vector<double> ans(x);
    double q = 0.5, maxDiff;
    do {
        maxDiff = 0;
        for (uint64_t i = 0; i < ans.size(); ++i) {
            double tmp = system[i](ans);
            if (std::abs(tmp - ans[i]) > maxDiff) {
                maxDiff = std::abs(tmp);
            }
            ans[i] = tmp;
        }
    } while ((q / (1 - q)) * maxDiff > e);
    return ans;
}