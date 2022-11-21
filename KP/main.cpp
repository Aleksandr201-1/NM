#include <iostream>
#include "FuncMaker.hpp"
#include "ImproperIntegral.hpp"

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

std::tuple<double, double> getValues (const std::string &a_str, const std::string &b_str) {
    double a, b;
    a = a_str == "-inf" ? -INFINITY : std::atof(a_str.c_str());
    b = b_str == "inf"  ?  INFINITY : std::atof(b_str.c_str());
    return std::make_tuple(a, b);
}

int main () {
    std::cout << "=====Несобственный интеграл=====\n";
    std::string func_str;
    FunctionalTree func;
    double a, b;
    std::string a_str, b_str;
    std::cout << "Введите функцию:\n";
    func_str = readLine();
    std::cout << "Введите границы интегрирования:\n";
    std::cin >> a_str >> b_str;
    std::tie(a, b) = getValues(a_str, b_str);

    func.reset(func_str, {"x"});
    auto f = [&] (double x) -> double {
        return func(x);
    };
    // FunctionalTree fi_tree = func.getDiv();
    // auto fi = [&] (double x) -> double {
    //     return fi_tree(x);
    // };
    //printVector(getBreakPointsNewton(fi, a, b));
    //return 0;
    //double ans = ImproperIntegral(f, a, b);
    double ans = ImproperIntegral(f, a, b, getBreakPoints(f, a, b));
    std::cout << "Ответ: " << ans << "\n";
    if (std::abs(ans) == INFINITY) {
        std::cout << "Интеграл расходится\n";
    }
    //std::cout << "Integral: " << IntegralSimpson(f, 1, INFINITY, 1) << "\n";
    return 0;
}