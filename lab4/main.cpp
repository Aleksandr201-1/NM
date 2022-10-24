#include <iostream>
#include "gnuplot-iostream.h"
#include "FuncMaker.hpp"
#include "4-1.hpp"
#include "4-2.hpp"
#include "3-3.hpp"

void plot (const std::vector<std::string> &func, double a, double b) {
    static std::vector<std::string> colors = {"red", "green", "blue"};
    Gnuplot gp;

    gp << "set xlabel \"X\"\n";
    gp << "set ylabel \"Y\"\n";
    gp << "set xzeroaxis lw 1\n";
    gp << "set yzeroaxis lw 1\n";
    gp << "set xrange[" << a << ":" << b << "]\n";
    gp << "set grid\n";
    gp << "set title \"Plot\" font \"Helvetica Bold, 20\"\n";
    
    gp << "plot ";
    for (uint64_t i = 0; i < func.size(); ++i) {
        gp << func[i] << " title \"";
        gp << (i == 0 ? "our func" : "real func");
        gp << "\"  lc rgb \"" << colors[i % colors.size()] << "\"";
        if (i == func.size() - 1) {
            gp << "\n";
        } else {
            gp << ",";
        }
    }
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

int main () {
    std::cout << "=====4.1=====\n";
    std::cout << "Введите первую задачу:\n";
    std::vector<std::string> system;
    std::string checkSTR;
    double h;
    std::pair<std::vector<double>, std::vector<double>> res1, res2;
    Task task;
    FunctionalTree check;

    for (uint64_t i = 0; i < 3; ++i) {
        checkSTR = readLine();
        system.push_back(checkSTR);
    }
    std::cout << "Введите размер шага:\n";
    std::cin >> h;
    std::cout << "Введите функцию для сравнения:\n";
    checkSTR = readLine();
    task = getTaskInfo(system);
    task.X2 = task.X1 + 1;

    std::cout << "\n=====Эйлер=====\n";
    res1 = Euler(task, h);
    res2 = Euler(task, 2 * h);
    std::cout << "X: ";
    printVector(res1.first);
    std::cout << "Y: ";
    printVector(res1.second);
    std::cout << "Погрешность: " << RungeRomberg(res1.second[2], res2.second[1]) << "\n";

    std::cout << "=====Рунге=====\n";
    res1 = Runge(task, h);
    res2 = Runge(task, 2 * h);
    std::cout << "X: ";
    printVector(res1.first);
    std::cout << "Y: ";
    printVector(res1.second);
    std::cout << "Погрешность: " << RungeRomberg(res1.second[2], res2.second[1]) << "\n";

    std::cout << "\n=====Адамс=====\n";
    res1 = Adams(task, h);
    res2 = Adams(task, 2 * h);
    std::cout << "X: ";
    printVector(res1.first);
    std::cout << "Y: ";
    printVector(res1.second);
    std::cout << "Погрешность: " << RungeRomberg(res1.second[2], res2.second[1]) << "\n";

    auto func = LeastSquareMethod(res1.first, res1.second, 3);
    plot({LSMToText(func), checkSTR}, res1.first[0], res1.first.back());

    std::cout << "=====4.2=====\n";
    std::cout << "Введите вторую задачу:\n";

    system.clear();
    for (uint64_t i = 0; i < 3; ++i) {
        checkSTR = readLine();
        system.push_back(checkSTR);
    }
    std::cout << "Введите размер шага:\n";
    std::cin >> h;
    std::cout << "Введите функцию для сравнения:\n";

    checkSTR = readLine();
    task = getTaskInfo(system);
    check.reset(checkSTR, {"x"});

    std::cout << "\n=====Метод стрельбы=====\n";
    res1 = Shoot(task, h);
    res2 = Shoot(task, 2 * h);
    if (res1.first.size()) {
        std::cout << "X: ";
        printVector(res1.first);
        std::cout << "Y: ";
        printVector(res1.second);
        std::cout << "Погрешность: " << RungeRomberg(res1.second[2], res2.second[1]) << "\n";
    } else {
        std::cout << "Не получается решить задачу методом стрельбы\n";
    }
    auto func2 = LeastSquareMethod(res1.first, res1.second, 3);

    std::cout << "\n=====Конечно-разностный метод=====\n";
    res1 = FiniteDifference(task, h);
    res2 = FiniteDifference(task, 2 * h);
    std::cout << "X: ";
    printVector(res1.first);
    std::cout << "Y: ";
    printVector(res1.second);
    std::cout << "Погрешность: " << RungeRomberg(res1.second[2], res2.second[1]) << "\n";
    func = LeastSquareMethod(res1.first, res1.second, 3);
    //plot({LSMToText(func), checkSTR, LSMToText(func2)}, res1.first[0], res1.first.back());
    plot({LSMToText(func), checkSTR}, res1.first[0], res1.first.back());

    //double x = 0;
    //std::cout << "testing output\n";
    //check
    // while (std::cin >> x) {
    //     if (x == 15) {
    //         break;
    //     }
    //     std::cout << "Real Func(" << x << ") = " << check.func(x) << "\n";
    //     std::cout << "Our Func(" << x << ") = " << LSMFunc(func, x) << "\n";
    // }
    return 0;
}