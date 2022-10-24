#include "5-1.hpp"

void FiniteDifferenceExplicit (std::vector<std::vector<double>> &u, double xh, double th, double a) {
    double sigma = a * a * th / (xh * xh);
    if (sigma > 0.5) {
        std::cout << "sigma = " << sigma << " > 0.5\n";
        std::cout << "Явный метод расходится\n";
        return;
    }
    for (uint64_t i = 1; i < u.size(); ++i) {
        for (uint64_t j = 1; j < u[i].size() - 1; ++j) {
            u[i][j] = sigma * u[i - 1][j + 1] + (1 - 2 * sigma) * u[i - 1][j] + sigma * u[i - 1][j - 1];
            //u[i][j] = sigma * u[i + 1][j - 1] + (1 - 2 * sigma) * u[i][j - 1] + sigma * u[i - 1][j - 1];
        }
    }
}

void FiniteDifferenceNotExplicit (std::vector<std::vector<double>> &u, double xh, double th, double a) {
    double sigma = a * a * th / (xh * xh);
    for (uint64_t i = 1; i < u.size(); ++i) {
        uint64_t n = u[0].size() - 2;
        Matrix<double> M(n, n);
        std::vector<double> ans(n);
        M(0, 0) = -(1 + 2 * sigma);
        M(0, 1) = sigma;
        ans[0] = -(u[i - 1][1] + sigma * u[i][0]);
        for (uint64_t j = 1; j < n - 1; ++j) {
            M(j, j - 1) = sigma;
            M(j, j) = -(1 + 2 * sigma);
            M(j, j + 1) = sigma;
            ans[j] = -u[i - 1][j + 1];
        }
        M(n - 1, n - 2) = sigma;
        M(n - 1, n - 1) = -(1 + 2 * sigma);
        ans[n - 1] = -(u[i - 1][n] + sigma * u[i][n + 1]);
        ans = RUNsolveSLAE(M, ans);
        for (uint64_t j = 0; j < ans.size(); ++j) {
            u[i][j + 1] = ans[j];
        }
    }
}

void KrankNicolas (std::vector<std::vector<double>> &u, double xh, double th, double a) {
    double sigma = 0.5 * a * a * th / (xh * xh);
    for (uint64_t i = 1; i < u.size(); ++i) {
        uint64_t n = u[0].size() - 2;
        Matrix<double> M(n, n);
        std::vector<double> ans(n);
        M(0, 0) = -(1 + 2 * sigma);
        M(0, 1) = sigma;
        //ans[0] = -(u[i - 1][1] + sigma * u[i][0]);
        ans[0] = -(u[i - 1][1] + sigma * u[i][0] + sigma * (u[i - 1][2] - 2 * u[i - 1][1] + u[i - 1][0]));
        for (uint64_t j = 1; j < n - 1; ++j) {
            M(j, j - 1) = sigma;
            M(j, j) = -(1 + 2 * sigma);
            M(j, j + 1) = sigma;
            ans[j] = -u[i - 1][j + 1] - sigma * (u[i - 1][j + 2] - 2 * u[i - 1][j + 1] + u[i - 1][j]);
        }
        M(n - 1, n - 2) = sigma;
        M(n - 1, n - 1) = -(1 + 2 * sigma);
        //ans[n - 1] = -(u[i - 1][n] + sigma * u[i][n + 1]);
        ans[n - 1] = -(u[i - 1][n] + sigma * u[i][n + 1] + sigma * (u[i - 1][n + 1] - 2 * u[i - 1][n] + u[i - 1][n - 1]));
        ans = RUNsolveSLAE(M, ans);
        for (uint64_t j = 0; j < ans.size(); ++j) {
            u[i][j + 1] = ans[j];
        }
    }
}

std::vector<std::vector<double>> SolveIBVP (const Task &task, double xh, double th, Method method) {
    double X1 = task.X1, X2 = task.X2, a = task.a;//, c = task.c;
    std::vector<std::vector<double>> u(10, std::vector<double>((X2 - X1) / xh, 0));
    auto fx0 = [&] (double t) -> double {
        return task.trees[0](t);
    };
    auto fxl = [&] (double t) -> double {
        return task.trees[1](t);
    };
    auto ft0 = [&] (double x) -> double {
        return task.trees[2](x);
    };
    for (uint64_t i = 0; i < u[0].size(); ++i) {
        u[0][i] = ft0(i * xh);
    }
    for (uint64_t i = 1; i < u.size(); ++i) {
        u[i].front() = fx0(i * th);
        u[i].back() = fxl(i * th);
    }
    switch (method) {
        case Method::EXPLICIT:
            FiniteDifferenceExplicit(u, xh, th, a);
            break;
        case Method::NOT_EXPLICIT:
            FiniteDifferenceNotExplicit(u, xh, th, a);
            break;
        case Method::KRANK_NICOLAS:
            KrankNicolas(u, xh, th, a);
            break;
        default:
            break;
    }
    return u;
}

// std::vector<std::vector<double>> KrankNicolas (const Task &task, double xh, double th) {
//     double X1 = task.X1, X2 = task.X2, a = task.a;//, c = task.c;
//     std::vector<std::vector<double>> u(10, std::vector<double>((X2 - X1) / xh, 0));
//     auto fx0 = [&] (double t) -> double {
//         return task.trees[0](t);
//     };
//     auto fxl = [&] (double t) -> double {
//         return task.trees[1](t);
//     };
//     auto ft0 = [&] (double x) -> double {
//         return task.trees[2](x);
//     };
//     for (uint64_t i = 0; i < u[0].size(); ++i) {
//         u[0][i] = ft0(i * xh);
//     }
//     for (uint64_t i = 1; i < u.size(); ++i) {
//         u[i].front() = fx0(i * th);
//         u[i].back() = fxl(i * th);
//     }
//     return u;
// }