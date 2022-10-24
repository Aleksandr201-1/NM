#include "ImproperIntegral.hpp"

std::vector<double> getBreakPoints (const std::function<double(double)> &f, double a, double b) {
    std::vector<double> ans;
    double eps = findEpsillon();
    //double tmp;
    if (a == -INFINITY) {
        a = 1;
    }
    if (b == INFINITY) {
        b = 1;
    }
    //ans.push_back(a);
    while (a < b) {
        try {
            f(a);
        } catch (std::exception &exp) {
            ans.push_back(a);
        }
        a += eps;
    }
    //ans.push_back(b);
    return ans;
}

double IntegralSimpson (const std::function<double(double)> &f, double X1, double X2, double step) {
    double ans = 0;
    uint64_t size = (X2 - X1) / step;
    std::cout << "size: " << size << "\n";
    ans += f(X1) + f(X2);
    for (uint64_t i = 1; i < size; ++i) {
        ans += f(X1 + step * i) * (i & 1 ? 4 : 2);
    }
    ans *= step / 3;
    return ans;
}

double ImproperIntegralH (const std::function<double(double)> &f, double a, double b) {
    double eps = findEpsillon();
    return f(a + b + eps);
}

double ImproperIntegral (const std::function<double(double)> &f, double a, double b) {
    auto points = getBreakPoints(f, a, b);
    std::cout << "\nBreak points: ";
    printVector(points);
    double ans = 0;
    if (points.empty()) {
        points.push_back((a + b) / 2);
    }
    for (uint64_t i = 0; i < points.size() - 1; ++i) {
        double a = points[i], b = points[i + 1];
        //ans += ImproperIntegralH(f, points[i], points[i + 1]);
        ans += IntegralSimpson(f, a, b, (b - a) / 10);
    }
    ans += ImproperIntegralH(f, a, points.front());
    ans += ImproperIntegralH(f, points.back(), b);
    return ans;
}