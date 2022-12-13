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

Task getTaskInfo(const std::vector<std::string> &system) {
    uint64_t idx = 0, size = 0;
    std::string tmp;
    Task task;

    //task.trees.resize(4);
    task.X.resize(2);
    task.coeff = std::vector<double>(4, 0);

    idx = system[0].find('=');
    size = system[0].size();
    //tmp = system[0].substr(0, idx);
    //task.X1 = stringFix(tmp); "ut, uxx, ux, u, x"
    //std::cout << "func: q" << system[0].substr(idx + 1, size - idx) << "q\n";
    task.trees.push_back(std::move(FunctionalTree(system[0].substr(idx + 1, size - idx), {"uxx", "ux", "u", "x"})));
    // task.coeff[0] = task.trees.back().func({1, 0, 0, 0});
    // task.coeff[1] = task.trees.back().func({0, 1, 0, 0});
    // task.coeff[2] = task.trees.back().func({0, 0, 1, 0});
    task.coeff[0] = task.trees[0].getCoeff(0).func(0);
    task.coeff[1] = task.trees[0].getCoeff(1).func(0);
    task.coeff[2] = task.trees[0].getCoeff(2).func(0);
    //task.trees[0].printTree();
    // for (uint64_t i = 0; i < 3; ++i) {
    //     //task.coeff.push_back(task.trees.back().func({1, 0, 0, 0}));
    //     std::cout << "coeff = " << task.coeff[i] << "\n";
    //     std::cout << "real = " << task.trees[0].getCoeff(i).func(0) << "\n";
    //     //std::cout << "real = ";
    //     //task.trees[0].printFunc();
    // }
    for (uint64_t i = 1; i < 3; ++i) {
        idx = system[i].find('=');
        size = system[i].size();
        tmp = system[i].substr(0, idx);
        task.X[i - 1] = stringFix(tmp);
        task.trees.push_back(std::move(FunctionalTree(system[i].substr(idx + 1, size - idx), {"t"})));
    }
    idx = system[3].find('=');
    size = system[3].size();
    tmp = system[3].substr(0, idx);
    task.trees.push_back(std::move(FunctionalTree(system[3].substr(idx + 1, size - idx), {"x"})));

    // for (uint64_t i = 0; i < 3; ++i) {
    //     idx = system[i].find('=');
    //     size = system[i].size();
    //     tmp = system[i].substr(0, idx);
    //     task.trees.push_back(std::move(FunctionalTree(system[i].substr(idx + 1, size - idx), {"t"})));
    // }
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