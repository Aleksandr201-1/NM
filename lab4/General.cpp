#include "General.hpp"

void printVector(const std::vector<double> &vec) {
    for (double el : vec) {
        std::cout << el << " ";
    }
    std::cout << "\n";
}

double findEpsillon () {
    return std::pow(__DBL_EPSILON__, 1.0 / 3) * 10;
}

bool isEqual(double x, double y) {
    return std::fabs(x - y) < std::numeric_limits<double>::epsilon();
}

double derivative (const std::function<double(double)> &f, double x, uint64_t degree) {
    static double eps = findEpsillon();
    if (degree == 1) {
        return (f(x + eps) - f(x - eps)) / (2 * eps);
    }
    return (derivative(f, x + eps, degree - 1) - derivative(f, x - eps, degree - 1)) / (2 * eps);
}

double derivative (const std::function<double(const std::vector<double> &)> &f, const std::vector<double> &x, uint64_t i) {
    static double eps = findEpsillon();
    std::vector<double> tmp = x;
    double f1 = 0, f2 = 0;
    tmp[i] += eps;
    f1 = f(tmp);
    tmp[i] -= 2 * eps;
    f2 = f(tmp);
    //if (degree == 1) {
    return (f1 - f2) / (2 * eps);
    //}
    //return (derivative(f, x, degree - 1) - derivative(f, x, degree - 1)) / (2 * eps);
}

std::string toString (double val, uint64_t precision) {
    return std::to_string(val).substr(0, std::to_string(val).find(".") + precision + 1);
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

Task getTaskInfo(const std::vector<std::string> &system) {
    uint64_t idx = 0, size = 0;
    Task task;
    //double a, b, X1, X2;
    //std::vector<FunctionalTree> trees;

    idx = system[0].find('=');
    size = system[0].size();
    task.trees.push_back(std::move(FunctionalTree(system[0].substr(0, idx), {"x", "y''", "y'", "y"})));
    task.trees.push_back(std::move(FunctionalTree(system[0].substr(idx + 1, size - idx), {"x", "y''", "y'", "y"})));

    idx = system[1].find('=');
    size = system[1].size();
    std::string tmp = system[1].substr(0, idx);
    task.X1 = stringFix(tmp);
    task.a = FunctionalTree(system[1].substr(idx + 1, size - idx), {}).func(0);
    task.trees.push_back(std::move(FunctionalTree(tmp, {"y'", "y"})));

    idx = system[2].find('=');
    size = system[2].size();
    tmp = system[2].substr(0, idx);
    task.X2 = stringFix(tmp);
    task.b = FunctionalTree(system[2].substr(idx + 1, size - idx), {}).func(0);
    task.trees.push_back(std::move(FunctionalTree(tmp, {"y'", "y"})));

    return task;
}

double RungeRomberg (double X1, double X2) {
    return std::abs((X1 - X2) / 15);
}