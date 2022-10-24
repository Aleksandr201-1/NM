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

std::string toString (double val, uint64_t precision) {
    return std::to_string(val).substr(0, std::to_string(val).find(".") + precision + 1);
}

double stringFix (std::string &str) {
    double val = 0;
    std::string tmp(str);
    str = "";
    //str.erase(0, 1);
    for (uint64_t i = 0; i < tmp.size(); ++i) {
        if (tmp[i] == 'u') {
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

// std::tuple<uint64_t, double, uint64_t> getStrInfo (const std::string &str) {
//     uint64_t i = 0, j = 0;
//     while (1) {

//     }
//     return std::make_tuple(1, 1.0, 1);
// }

Task getTaskInfo(const std::vector<std::string> &system, double a, double c) {
    uint64_t idx = 0, size = 0;
    std::string tmp;
    Task task;

    idx = system[0].find('=');
    size = system[0].size();
    tmp = system[0].substr(0, idx);
    task.X1 = stringFix(tmp);
    task.trees.push_back(std::move(FunctionalTree(system[0].substr(idx + 1, size - idx), {"t"})));

    idx = system[1].find('=');
    size = system[1].size();
    tmp = system[1].substr(0, idx);
    task.X2 = stringFix(tmp);
    task.trees.push_back(std::move(FunctionalTree(system[1].substr(idx + 1, size - idx), {"t"})));

    idx = system[2].find('=');
    size = system[2].size();
    tmp = system[2].substr(0, idx);
    task.trees.push_back(std::move(FunctionalTree(system[2].substr(idx + 1, size - idx), {"x"})));

    // for (uint64_t i = 0; i < 3; ++i) {
    //     idx = system[i].find('=');
    //     size = system[i].size();
    //     tmp = system[i].substr(0, idx);
    //     task.trees.push_back(std::move(FunctionalTree(system[i].substr(idx + 1, size - idx), {"t"})));
    // }

    task.a = a;
    task.c = c;

    return task;
}

std::string readLine () {
    std::string str;
    while (str.empty()) {
        std::getline(std::cin, str);
        if (!str.empty() && str[0] == '#') {
            str = "";
        }
    }
    return str;
}