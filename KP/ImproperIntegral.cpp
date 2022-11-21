#include "ImproperIntegral.hpp"

// bool checkNewton (double x, const std::function<double(double)> &f) {
//     return f(x) * derivative(f, x, 2) > 0.0;
// }

// double Newton (double x, double approx, const std::function<double(double)> &f) {
//     if (!checkNewton(x, f)) {
//         throw std::runtime_error("Newton: Incorrect begining point");
//     }
//     uint64_t count = 1;
//     double x2 = x - f(x) / derivative(f, x, 1);
//     while (std::abs(x2 - x) > approx) {
//         x = x2;
//         x2 = x - f(x) / derivative(f, x, 1);
//         ++count;
//         if (count > ITERATION_CAP) {
//             throw std::runtime_error("Newton: the maximum number of iterations has been reached");
//         }
//     }
//     return x2;
// }

std::vector<double> getBreakPoints (const std::function<double(double)> &f, double a, double b) {
    if (a == -INFINITY || b == INFINITY) {
        return {};
    }
    std::vector<double> ans;
    double eps = (b - a) / 10;//findEpsillon();
    double tmp, inf = std::pow(10, 30);
    while (a < b) {
        tmp = f(a);
        //std::cout << "a = " << a << " f(a) = " << tmp << "\n";
        if (std::abs(tmp) > inf) {
            ans.push_back(a);
        }
        a += eps;
    }
    if (std::abs(f(b)) > inf) {
        ans.push_back(b);
    }
    return ans;
}

// std::vector<double> getBreakPointsNewton (const std::function<double(double)> &f, double a, double b) {
//     std::vector<double> ans;
//     double eps = (b - a) / 10;//findEpsillon();
//     double tmp;
//     while (a <= b) {
//         tmp = a;
//         while (f(tmp) * f(a) > 0 && tmp < b) {
//             tmp += eps;
//         }
//         if (tmp == a) {
//             ans.push_back(tmp);
//             a += eps;
//             continue;
//         }
//         std::cout << "area: " << a << " " << tmp << "\n";
//         ans.push_back(Newton((tmp + a) / 2, 0.01, f));
//         std::cout << "got: " << ans.back() << "\n";
//         a = tmp;
//     }
//     return ans;
// }

double IntegralSimpson (const std::function<double(double)> &f, double X1, double X2, double step) {
    double ans = 0;
    uint64_t size = (X2 - X1) / step;
    ans += f(X1) + f(X2);
    for (uint64_t i = 1; i < size; ++i) {
        ans += f(X1 + step * i) * (i & 1 ? 4 : 2);
    }
    ans *= step / 3;
    return ans;
}

double IntegralRunge (double ans1, double ans2, double k, double p) {
    return std::abs((ans1 - ans2) / (std::pow(k, p) - 1));
}

double ImproperIntegralFirst (const std::function<double(double)> &f, double a, double b, uint64_t n) {
    if (isEqual(a, b)) {
        return 0;
    }
    if (a != -INFINITY && b != INFINITY) {
        return IntegralSimpson(f, a, b, (b - a) / n);
    }
    double res1, res2, val[2], mul, prevDiff = 0, nextDiff = 0;
    uint64_t idx, iterNum = 0;
    if (a == -INFINITY) {
        idx = 0;
        mul = -1;
        val[0] = b - 1;
        val[1] = b;
    } else {
        idx = 1;
        mul = 1;
        val[0] = a;
        val[1] = a + 1;
    }
    res1 = IntegralSimpson(f, val[0], val[1], (val[1] - val[0]) / n);
    val[idx] += mul * 10;
    res2 = IntegralSimpson(f, val[0], val[1], (val[1] - val[0]) / n);
    prevDiff = std::abs(res2 - res1);
    nextDiff = prevDiff;
    while (nextDiff > 0.001 && prevDiff >= nextDiff) {
        val[idx] += mul * 10;
        if (std::abs(val[idx]) == INFINITY || iterNum > ITERATION_CAP) {
            res2 = INFINITY;
            break;
        }
        res1 = res2;
        res2 = IntegralSimpson(f, val[0], val[1], (val[1] - val[0]) / n);
        prevDiff = nextDiff;
        nextDiff = std::abs(res2 - res1);
        //std::cout << "res" << iterNum << ": " << res2 << " args: " << val[0] << " " << val[1] << " " << prevDiff << " " << nextDiff << "\n";
        //std::cin.get();
        ++iterNum;
    }
    if (iterNum == 1 && prevDiff < nextDiff) {
        return INFINITY;
    }
    return res2;
}

double ImproperIntegralSecond (const std::function<double(double)> &f, double a, double b, uint64_t idx, uint64_t n) {
    if (isEqual(a, b)) {
        return 0;
    }
    double res1, res2, val[2], tmp[2], mul, prevDiff = 0, nextDiff = 0;
    uint64_t iterNum = 0;
    val[0] = tmp[0] = a;
    val[1] = tmp[1] = b;
    mul = idx == 0 ? -1 : 1;
    tmp[idx] -= mul * 0.001;
    val[idx] = (tmp[1] + tmp[0]) / 2;
    //std::cout << "val " << val[idx] << "\n";

    res1 = IntegralSimpson(f, val[0], val[1], (val[1] - val[0]) / n);
    val[idx] += mul * std::abs((tmp[idx] - val[idx]) / 2);
    res2 = IntegralSimpson(f, val[0], val[1], (val[1] - val[0]) / n);
    //std::cout << "val: " << val[idx] << " ans: " << res2 << "\n";
    prevDiff = std::abs(res2 - res1);
    nextDiff = prevDiff;
    while (nextDiff > 0.001 && prevDiff >= nextDiff) {
        val[idx] += mul * std::abs((tmp[idx] - val[idx]) / 2);
        if (std::abs(val[idx]) == INFINITY || iterNum > ITERATION_CAP) {
            res2 = val[idx];
            break;
        }
        res1 = res2;
        res2 = IntegralSimpson(f, val[0], val[1], (val[1] - val[0]) / n);
        prevDiff = nextDiff;
        nextDiff = std::abs(res2 - res1);
        ++iterNum;
        //std::cout << "res" << iterNum << ": " << res2 << " args: " << val[0] << " " << val[1] << " " << prevDiff << " " << nextDiff << "\n";
        //std::cout << "val: " << val[idx] << " ans: " << res2 << "\n";
    }
    if (iterNum == 1 && prevDiff < nextDiff) {
        return INFINITY;
    }
    return res2;
}

double ImproperIntegral (const std::function<double(double)> &f, double a, double b) {
    return ImproperIntegral(f, a, b, getBreakPoints(f, a, b));
}

double ImproperIntegral (const std::function<double(double)> &f, double a, double b, const std::vector<double> &points) {
    double ans, tmp1 = 0, tmp2 = 0;
    if (a == -INFINITY || b == INFINITY) {
        std::cout << "Несобственный интегралл 1го рода\n";
        if (a != -INFINITY || b != INFINITY) {
            tmp1 = ImproperIntegralFirst(f, a, b, 100);
            tmp2 = ImproperIntegralFirst(f, a, b, 200);
            //ans = tmp2 + IntegralRunge(tmp1, tmp2, 0.5, 2);
        } else {
            tmp1 = ImproperIntegralFirst(f, a, 0, 100) + ImproperIntegralFirst(f, 0, b, 100);
            tmp2 = ImproperIntegralFirst(f, a, 0, 200) + ImproperIntegralFirst(f, 0, b, 200);
            //std::cout << "before: " << tmp1 << " " << tmp2 << "\n";
            //ans = tmp2 + IntegralRunge(tmp1, tmp2, 0.5, 2);
        }
    } else if (points.size() > 0) {
        //std::cout << "\nBreak points: ";
        //printVector(points);
        std::cout << "Несобственный интегралл 2го рода\n";
        //ans += ImproperIntegralSecond(f, a, points.front(), 1, 100);
        tmp1 += ImproperIntegralSecond(f, a, points.front(), 1, 100);
        tmp2 += ImproperIntegralSecond(f, a, points.front(), 1, 200);
        for (uint64_t i = 0; i < points.size() - 1; ++i) {
            double a1 = points[i], b1 = points[i + 1], mid = (a1 + b1) / 2;
            //ans += ImproperIntegralSecond(f, a1, mid, 0, 100);
            //ans += ImproperIntegralSecond(f, mid, b1, 1, 100);
            tmp1 += ImproperIntegralSecond(f, a1, mid, 0, 100) + ImproperIntegralSecond(f, mid, b1, 1, 100);
            tmp2 += ImproperIntegralSecond(f, a1, mid, 0, 200) + ImproperIntegralSecond(f, mid, b1, 1, 200);
        }
        //ans += ImproperIntegralSecond(f, points.back(), b, 0, 100);
        tmp1 += ImproperIntegralSecond(f, points.back(), b, 0, 100);
        tmp2 += ImproperIntegralSecond(f, points.back(), b, 0, 200);
    } else {
        tmp1 = IntegralSimpson(f, a, b, (b - a) / 100);
        tmp2 = IntegralSimpson(f, a, b, (b - a) / 200);
    }
    ans = tmp2 + IntegralRunge(tmp1, tmp2, 0.5, 3);
    if (ans != ans || std::abs(ans) > std::pow(10, 30)) {
        ans = INFINITY;
    }
    return ans;
}