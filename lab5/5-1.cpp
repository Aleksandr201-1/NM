#include "5-1.hpp"

void FiniteDifferenceExplicit (std::vector<std::vector<double>> &u, double X0, double xh, double th, const std::vector<double> &coeff, const std::function<double(double)> &f) {
    double a = coeff[0], b = coeff[1], c = coeff[2];
    double sigmaA = a * th / (xh * xh), sigmaB = b * th / (2 * xh), sigmaC = c * th;
    if (sigmaA > 0.5) {
        std::cout << "sigma = " << sigmaA << " > 0.5\n";
        std::cout << "Явный метод расходится\n";
        //return;
    }
    for (uint64_t i = 1; i < u.size(); ++i) {
        for (uint64_t j = 1; j < u[i].size() - 1; ++j) {
            double tmp = 0;
            tmp += sigmaA * (u[i - 1][j + 1] - 2 * u[i - 1][j] + u[i - 1][j - 1]);
            tmp += sigmaB * (u[i - 1][j + 1] - u[i - 1][j]);
            tmp += sigmaC * u[i - 1][j];
            tmp += f(X0 + j * xh) * th;
            u[i][j] = tmp + u[i - 1][j];
            //u[i][j] = sigma * u[i - 1][j + 1] + (1 - 2 * sigma) * u[i - 1][j] + sigma * u[i - 1][j - 1];
            //u[i][j] = sigma * u[i + 1][j - 1] + (1 - 2 * sigma) * u[i][j - 1] + sigma * u[i - 1][j - 1];
        }
    }
}

void FiniteDifferenceNotExplicit (std::vector<std::vector<double>> &u, double X0, double xh, double th, const std::vector<double> &coeff, const std::function<double(double)> &f) {
    double a = coeff[0], b = coeff[1], c = coeff[2];
    double sigmaA = a * th / (xh * xh), sigmaB = b * th / (2 * xh), sigmaC = c * th;
    //std::cout << "f: " << f(1) << " " << f(0) << " " << f(0.5) << "\n";
    for (uint64_t i = 1; i < u.size(); ++i) {
        uint64_t n = u[0].size() - 2;
        Matrix<double> M(n, n);
        std::vector<double> ans(n);
        M(0, 0) = -1 - 2 * sigmaA - sigmaB + sigmaC;
        M(0, 1) = sigmaA + sigmaB;
        ans[0] = -(u[i - 1][1] + (sigmaA + sigmaB + sigmaC) * u[i][0] + f(X0 + xh) * th);
        for (uint64_t j = 1; j < n - 1; ++j) {
            M(j, j - 1) = sigmaA;
            M(j, j) = -1 - 2 * sigmaA - sigmaB + sigmaC;
            M(j, j + 1) = sigmaA + sigmaB;
            ans[j] = -u[i - 1][j + 1] - f(X0 + (j + 1) * xh) * th;
        }
        M(n - 1, n - 2) = sigmaA;
        M(n - 1, n - 1) = -1 - 2 * sigmaA - sigmaB + sigmaC;
        ans[n - 1] = -(u[i - 1][n] + (sigmaA + sigmaB + sigmaC) * u[i][n + 1] + f(X0 + xh * n) * th);
        ans = RUNsolveSLAE(M, ans);
        for (uint64_t j = 0; j < ans.size(); ++j) {
            u[i][j + 1] = ans[j];
        }
    }
}

void KrankNicolas (double theta, std::vector<std::vector<double>> &u, double X0, double xh, double th, const std::vector<double> &coeff, const std::function<double(double)> &f) {
    if (theta < 0 || theta > 1) {
        throw std::logic_error("KrankNicolas: theta must be in range [0, 1]");
    }
    double a = coeff[0], b = coeff[1], c = coeff[2];
    double sigmaA = a * th / (xh * xh), sigmaB = b * th / (2 * xh), sigmaC = c * th;
    for (uint64_t i = 1; i < u.size(); ++i) {
        uint64_t n = u[0].size() - 2;
        Matrix<double> M(n, n);
        std::vector<double> ans(n);
        M(0, 0) = -1 - (2 * sigmaA - sigmaB + sigmaC) * theta;
        M(0, 1) = (sigmaA + sigmaB) * theta;
        //ans[0] = -(u[i - 1][1] + sigma * u[i][0]);
        //auto tmp = sigmaA * (u[i - 1][j + 1] - 2 * u[i - 1][j] + u[i - 1][j - 1]);
        //tmp += sigmaB * (u[i - 1][j + 1] - u[i - 1][j]);
        //tmp += sigmaC * u[i - 1][j];
        //tmp += f(X0 + j * xh) * th;
        ans[0] = -u[i - 1][1] - (sigmaA + sigmaB + sigmaC) * u[i][0] * theta;
        ans[0] += -(sigmaA * (u[i - 1][2] - 2 * u[i - 1][1] + u[i - 1][0]) + sigmaB * (u[i - 1][2] - u[i - 1][1]) + sigmaC * u[i - 1][1]) * (1 - theta);
        ans[0] += -f(X0 + xh) * th;
        for (uint64_t j = 1; j < n - 1; ++j) {
            //ans[j] = -u[i - 1][j + 1] - f(X0 + (j + 1) * xh) * th;
            M(j, j - 1) = sigmaA * theta;
            M(j, j) = -1 - (2 * sigmaA - sigmaB + sigmaC) * theta;
            M(j, j + 1) = (sigmaA + sigmaB) * theta;
            ans[j] = -u[i - 1][j + 1];// * theta;
            //ans[j] += -sigmaA * (u[i - 1][j + 2] - 2 * u[i - 1][j + 1] + u[i - 1][j]);
            ans[j] += -(sigmaA * (u[i - 1][j + 2] - 2 * u[i - 1][j + 1] + u[i - 1][j]) + sigmaB * (u[i - 1][j + 2] - u[i - 1][j + 1]) + sigmaC * u[i - 1][j + 1]) * (1 - theta);
            ans[j] += -f(X0 + (j + 1) * xh) * th;
            //ans[0] = -(u[i - 1][1] + (sigmaA + sigmaB + sigmaC) * u[i][0]) * theta;
            //ans[0] += -(sigmaA * (u[i - 1][2] - 2 * u[i - 1][1] + u[i - 1][0]) + sigmaB * (u[i - 1][2] - u[i - 1][1]) + sigmaC * u[i - 1][1]) * (1 - theta);
            //ans[0] += -f(X0 + xh) * th;
        }
        M(n - 1, n - 2) = sigmaA * theta;
        M(n - 1, n - 1) = -1 - (2 * sigmaA - sigmaB + sigmaC) * theta;
        //ans[n - 1] = -(u[i - 1][n] + sigma * u[i][n + 1]);
        //ans[n - 1] = -(u[i - 1][n] + sigmaA * u[i][n + 1] + sigmaA * (u[i - 1][n + 1] - 2 * u[i - 1][n] + u[i - 1][n - 1]));
        ans[n - 1] = -u[i - 1][n] - (sigmaA + sigmaB + sigmaC) * u[i][n + 1] * theta;// + f(X0 + xh * n) * th);
        ans[n - 1] += -(sigmaA * (u[i - 1][n + 1] - 2 * u[i - 1][n] + u[i - 1][n - 1]) + sigmaB * (u[i - 1][n + 1] - u[i - 1][n]) + sigmaC * u[i - 1][n]) * (1 - theta);
        ans[n - 1] += -f(X0 + xh * n) * th;
        //ans[0] = -(u[i - 1][1] + (sigmaA + sigmaB + sigmaC) * u[i][0]) * theta;
        //ans[0] +=     -(sigmaA * (u[i - 1][2] - 2 * u[i - 1][1] + u[i - 1][0]) + sigmaB * (u[i - 1][2] - u[i - 1][1]) + sigmaC * u[i - 1][1]) * (1 - theta);
        //ans[0] += -f(X0 + xh * n) * th;
        if (theta == 0.0) {
            for (uint64_t j = 0; j < ans.size(); ++j) {
                ans[j] *= -1;
            }
        } else {
            ans = RUNsolveSLAE(M, ans);
        }
        for (uint64_t j = 0; j < ans.size(); ++j) {
            u[i][j + 1] = ans[j];
        }
    }
}

std::vector<std::vector<double>> SolveIBVP (const Task &task, double xh, double th, Method method) {
    double X1 = task.X[0], X2 = task.X[1];
    std::vector<std::vector<double>> u(10, std::vector<double>((X2 - X1) / xh, 0));
    auto fx = [&] (double x) -> double {
        return task.trees[0]({0, 0, 0, x});
    };
    auto fx0 = [&] (double t) -> double {
        return task.trees[1](t);
    };
    auto fxl = [&] (double t) -> double {
        return task.trees[2](t);
    };
    auto ft0 = [&] (double x) -> double {
        return task.trees[3](x);
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
            KrankNicolas(0, u, X1, xh, th, task.coeff, fx);
            //FiniteDifferenceExplicit(u, X1, xh, th, task.coeff, fx);
            break;
        case Method::NOT_EXPLICIT:
            KrankNicolas(1, u, X1, xh, th, task.coeff, fx);
            //FiniteDifferenceNotExplicit(u, X1, xh, th, task.coeff, fx);
            break;
        case Method::KRANK_NICOLAS:
            //KrankNicolas(u, xh, th, a);
            KrankNicolas(0.5, u, X1, xh, th, task.coeff, fx);
            break;
        default:
            break;
    }
    return u;
}