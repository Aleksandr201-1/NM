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

int main () {
    std::cout << "=====Несобственный интеграл=====\n";
    std::string str;
    FunctionalTree tree;
    double a, b;
    std::cout << "Введите функцию:\n";
    str = readLine();
    std::cout << "Введите границы интегрирования:\n";
    std::cin >> a >> b;

    tree.reset(str, {"x"});
    auto f = [&] (double x) -> double {
        return tree(x);
    };
    std::cout << "Integral: " << ImproperIntegral(f, a, b) << "\n";
    std::cout << "Integral: " << IntegralSimpson(f, 1, INFINITY, 1) << "\n";
    return 0;
}