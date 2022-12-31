#include "7-1.hpp"

double SIIteration (std::vector<std::vector<double>> &u, double xh, double yh, const std::vector<double> &coeff, const std::function<double(double, double)> &f) {
    double maxAbs = 0;
    double a = coeff[0], b = coeff[1], c = coeff[2];
    uint64_t height = u.size(), width = u[0].size();
    for (uint64_t i = 1; i < height - 1; ++i) {
        for (uint64_t j = 1; j < width - 1; ++j) {
            double currU = 0;
            currU += u[i + 1][j] * (a*xh*yh*yh - yh*yh);
            currU -= u[i - 1][j] * yh*yh;
            currU += u[i][j + 1] * (b*xh*xh*yh - xh*xh);
            currU -= u[i][j - 1] * xh*xh;
            currU += xh*xh*yh*yh*f(i*xh, j*yh);
            currU /= a*xh*yh*yh + b*xh*xh*yh - c*xh*xh*yh*yh - 2*yh*yh - 2*xh*xh;
            maxAbs = std::max(maxAbs, std::abs(u[i][j] - currU));
            u[i][j] = currU;
        }
    }
    return maxAbs;
}

void SI (std::vector<std::vector<double>> &u, double xh, double yh, const std::vector<double> &coeff, const std::function<double(double, double)> &f, double eps) {
    //std::cout << "ligma it\n";
    double maxAbs = 0;
    //LibmanInit(u);
    Matrix<double> matrix(u.size() * u[0].size());
    std::vector<double> ans(u.size() * u[0].size());
    for (uint64_t i = 0; i < u.size(); ++i) {
        for (uint64_t j = 0; j < u[0].size(); ++j) {
            //
        }
    }
    ans = SISolveSLAE(matrix, ans, eps, SIMethod::SI_YAKOBI_METHOD);
    for (uint64_t i = 0; i < u.size(); ++i) {
        for (uint64_t j = 0; j < u[0].size(); ++j) {
            u[i][j] = ans[i * u[0].size() + j];
        }
    }
    maxAbs = SIIteration(u, xh, yh, coeff, f);
    while (maxAbs > eps) {
        maxAbs = SIIteration(u, xh, yh, coeff, f);
    }
}

void LibmanInit (std::vector<std::vector<double>> &u) {
    uint64_t height = u.size(), width = u[0].size();
    for (uint64_t i = 1; i < height - 1; ++i) {
        double left = u[i].front(), right = u[i].back();
        double step = (right - left) / width;
        for (uint64_t j = 1; j < width - 1; ++j) {
            u[i][j] = left + step * j;
        }
    }
}

double LibmanIteration (std::vector<std::vector<double>> &u, double xh, double yh, const std::vector<double> &coeff, const std::function<double(double, double)> &f) {
    double maxAbs = 0;
    double a = coeff[0], b = coeff[1], c = coeff[2];
    uint64_t height = u.size(), width = u[0].size();
    for (uint64_t i = 1; i < height - 1; ++i) {
        for (uint64_t j = 1; j < width - 1; ++j) {
            double currU = 0;
            currU += u[i + 1][j] * (a*xh*yh*yh - yh*yh);
            currU -= u[i - 1][j] * yh*yh;
            currU += u[i][j + 1] * (b*xh*xh*yh - xh*xh);
            currU -= u[i][j - 1] * xh*xh;
            currU += xh*xh*yh*yh*f(i*xh, j*yh);
            currU /= a*xh*yh*yh + b*xh*xh*yh - c*xh*xh*yh*yh - 2*yh*yh - 2*xh*xh;
            maxAbs = std::max(maxAbs, std::abs(u[i][j] - currU));
            u[i][j] = currU;
        }
    }
    return maxAbs;
}

void Libman (std::vector<std::vector<double>> &u, double xh, double yh, const std::vector<double> &coeff, const std::function<double(double, double)> &f, double eps) {
    //std::cout << "ligma it\n";
    double maxAbs = 0;
    LibmanInit(u);
    maxAbs = LibmanIteration(u, xh, yh, coeff, f);
    while (maxAbs > eps) {
        maxAbs = LibmanIteration(u, xh, yh, coeff, f);
    }
}

std::vector<std::vector<double>> SolveIBVP (const Task &task, double xh, double yh, Method method) {
    //std::cout << "solve\n";
    double l1 = task.X[1], l2 = task.Y[1];
    //std::cout << l1 << " " << l2 << "\n";
    //std::vector<std::vector<double>> u(10, std::vector<double>((X2 - X1) / xh, 0));
    std::vector<std::vector<double>> u(uint64_t(l2 / yh), std::vector<double>(uint64_t(l1 / xh), 0));
    //ApproxLevel left = ApproxLevel::NONE, right = ApproxLevel::NONE, up = ApproxLevel::NONE, down = ApproxLevel::NONE;
    //std::cout << "coeff:\n" << task.ux[0][0] << " " << task.ux[0][1] << "\n" << task.ux[1][0] << " " << task.ux[1][1] << "\n";
    // if (task.ux[0][0] != 0) {
    //     left = ApproxLevel::POINT2_ORDER2;
    // }
    // if (task.ux[1][0] != 0) {
    //     right = ApproxLevel::POINT2_ORDER2;
    // }
    auto f = [&] (double x, double y) -> double {
        return task.trees[0]({0, 0, 0, x, y});
    };
    auto fx0 = [&] (double y) -> double {
        return task.trees[1](y);
    };
    auto fxl = [&] (double y) -> double {
        return task.trees[2](y);
    };
    auto fy0 = [&] (double x) -> double {
        return task.trees[3](x);
    };
    auto fyl = [&] (double x) -> double {
        return task.trees[4](x);
    };
    for (uint64_t i = 0; i < u[0].size(); ++i) {
        u.front()[i] = fy0(i * xh);
        u.back()[i] = fyl(i * xh);
    }
    for (uint64_t i = 1; i < u.size() - 1; ++i) {
        u[i].front() = fx0(i * yh);
        u[i].back() = fxl(i * yh);
    }
    switch (method) {
        case Method::YAKOBI:
            break;
        case Method::ZEIDEL:
            break;
        case Method::LIBMAN:
            Libman(u, xh, yh, task.coeff, f, 0.01);
            break;
        default:
            break;
    }
    return u;
}