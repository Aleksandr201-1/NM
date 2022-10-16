#include <iostream>
#include "gnuplot-iostream.h"
#include "FuncMaker.hpp"
#include "4-1.hpp"
#include "4-2.hpp"
#include "3-3.hpp"

double y (double x) {
    return 1.0 / (x * x);
}

double f (double x, double y) {
    return (x + y) * (x + y);
}

double cc (double x) {
    //return std::cos(x) + 11.0/8.0 * std::sin(x) - std::sin(3.0 * x) / 8.0;
    return x + 7.0 / 2.0 + 1.0 / x + (x / 2 + 1) * std::log(std::abs(x));
}

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
        gp << func[i] << " title \"func " << i + 1 << "\"  lc rgb \"" << colors[i % colors.size()] << "\"";
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
    // FunctionalTree tree("-1", {});
    // std::cout << tree(10) << "\n";
    // tree.reset("-x", {"x"});
    // std::cout << tree(10) << "\n";
    // std::vector<std::string> sys = {
    //     "(x**2 + 1) * y'' = 2 * x * y'",
    //     "y(0) = 1",
    //     "y'(1) = 3"
    // };
    // std::string checkSTR = "x**3 + 3*x + 1";
    // std::vector<std::string> system = {
    //     "x**4 * y'' = y - (x + 1) * y'",
    //     "y(1) = 2 + exp(1)",
    //     "y'(2) = 1"
    // };
    // std::string checkSTR = "x + 1 + x * exp(1.0 / x)";
    std::vector<std::string> system;
    std::string checkSTR;
    double h;
    std::pair<std::vector<double>, std::vector<double>> res1, res2;
    Task task;
    FunctionalTree check;

    for (uint64_t i = 0; i < 3; ++i) {
        //std::getline(std::cin, checkSTR);
        checkSTR = readLine();
        system.push_back(checkSTR);
    }
    std::cout << "Введите размер шага:\n";
    std::cin >> h;
    std::cout << "Введите функцию для сравнения:\n";
    //std::cin.ignore();
    //std::cin.ignore();
    //std::getline(std::cin, checkSTR);
    checkSTR = readLine();
    task = getTaskInfo(system);

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

    auto func = LeastSquareMethod(res1.first, res1.second, 4);
    //plot({LSMToText(func), checkSTR}, res1.first[0], res1.first.back());

    double x = 0;
    // std::cout << "testing 1\n";
    // check.reset(checkSTR, {"x"});
    // while (std::cin >> x) {
    //     if (x == 15) {
    //         break;
    //     }
    //     std::cout << "Real Func(" << x << ") = " << check.func(x) << "\n";
    //     std::cout << "Wise mystical tree(" << x << ") = " << LSMFunc(func, x) << "\n";
    // }

    std::cout << "=====4.2=====\n";
    std::cout << "Введите вторую задачу:\n";

    system.clear();
    //std::cin.ignore();
    for (uint64_t i = 0; i < 3; ++i) {
        //std::getline(std::cin, checkSTR);
        checkSTR = readLine();
        //std::cout << checkSTR << "\n";
        system.push_back(checkSTR);
    }
    std::cout << "Введите размер шага:\n";
    std::cin >> h;
    std::cout << "Введите функцию для сравнения:\n";
    //std::cin.ignore();
    //std::cin.ignore();
    //std::getline(std::cin, checkSTR);
    checkSTR = readLine();
    //std::cout << checkSTR << "\n" << h << "\n";

    // system.push_back("x*(x+1)*y''+(x+2)*y'-y = x+1/x");
    // system.push_back("y'(1) = 3/2");
    // system.push_back("4*y'(2) + y(2) = 13+4*ln(2)");
    // checkSTR = "x + 7 / 2 + 1 / x + (x / 2 + 1) * log(abs(x))";

    // system.push_back("(x**2-1)*y''+(x-3)*y'-y=0");
    // system.push_back("y(0)=-18");
    // system.push_back("y(3)= 0");
    // checkSTR = "6*x - 18";

    // system.push_back("x*y''-(2*x+1)*y'+2*y=0");
    // system.push_back("y'(0)=2");
    // system.push_back("y(1)= exp(2)");
    // checkSTR = "exp(2*x)";

    // system.push_back("y''- 2 * (1+(tan(x))**2)*y=0");
    // system.push_back("y(0)=0");
    // system.push_back("y(0.52359)=-0.57735");
    // checkSTR = "0 - tan(x)";

    // system.push_back("(x**2+1)*y''-2*y = 0"); //мой вариант
    // system.push_back("y'(0) = 2");
    // system.push_back("y(1) = 3+3.14/2");
    // checkSTR = "x**2 + x + 1 + (x**2 + 1) * atan(x)";

    task = getTaskInfo(system);
    check.reset(checkSTR, {"x"});

    std::cout << "\n=====Метод стрельбы=====\n";
    res1 = Shoot(task, h);
    //res2 = Shoot(task, 2 * h);
    std::cout << "X: ";
    printVector(res1.first);
    std::cout << "Y: ";
    printVector(res1.second);
    //std::cout << "Погрешность: " << RungeRomberg(res1.second[2], res2.second[1]) << "\n";
    func = LeastSquareMethod(res1.first, res1.second, 4);
    //plot({LSMToText(func), checkSTR}, res1.first[0], res1.first.back());

    std::cout << "\n=====Конечно-разностный метод=====\n";
    res1 = FiniteDifference(task, h);
    res2 = FiniteDifference(task, 2 * h);
    std::cout << "X: ";
    printVector(res1.first);
    std::cout << "Y: ";
    printVector(res1.second);
    std::cout << "Погрешность: " << RungeRomberg(res1.second[2], res2.second[1]) << "\n";
    //func = LeastSquareMethod(res1.first, res1.second, 4);
    //plot({LSMToText(func), checkSTR}, res1.first[0], res1.first.back());

    

    //double x = 0;
    std::cout << "testing 2\n";
    //check
    while (std::cin >> x) {
        if (x == 15) {
            break;
        }
        std::cout << "Real Func(" << x << ") = " << check.func(x) << "\n";
        std::cout << "Wise mystical tree(" << x << ") = " << LSMFunc(func, x) << "\n";
    }
    return 0;
}