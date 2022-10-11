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

int main () {
    std::cout << "=====4.1=====\n";
    std::cout << "=====4.2=====\n";
    //auto X = {0.1, 0.5, 0.9, 1.3, 1.7, 2.1};
    //auto Y = {100.0, 4.0, 1.2346, 0.59172, 0.34602, 0.22676};
    //double a = 0, b = 0, X1 = 0.0, X2 = 1, h = 0.1;
    // auto func = Euler(y, 0, 0, 0.1, 2.1, 0.4);
    //FunctionalTree funky("cos(x) + 11/8 * sin(x) - sin(3 * x) / (8 + 0)", {"x"});
    //funky.printFunc();
    //std::cout << "\n";
    //FunctionalTree funky("x * (x - 1) * y'' - x * y'+ y", {"x", "y''", "y'", "y"});
    //FunctionalTree funky("y'' - x * y'- y", {"x", "y''", "y'", "y"});
    //FunctionalTree funky ("x + 7 / 2 + 1 / x + (x / 2 + 1) * ln(abs(x))", {"x"});
    FunctionalTree funky("x * (-1)", {"x"});
        // funky.printTree();
        // funky.printFunc();
        // std::cout << "\n";
        // std::cout << "y'' coeff: ";
        // funky.getCoeff(1).printFunc();
        // std::cout << "\n";
        // std::cout << "y' coeff: ";
        // funky.getCoeff(2).printFunc();
        // //funky = funky.getCoeff(2);
        // std::cout << "\n";
        // std::cout << "y coeff: ";
        // funky.getCoeff(3).printFunc();
        // std::cout << "\n";
        // std::cout << "func ans: " << funky.getCoeff(2)(2) << "\n";
    //funky.printTree();
    funky.printFunc();
    std::cout << "\n";
    //return 0;
    //FunctionalTree funky("cos(x)", {"x"});
    double x = 0;
    //while (std::cin >> x) {
        std::cout << "Wise mystical tree(" << x << ") = " << funky.func(x) << "\n";
        std::cout << "Real Func(" << x << ") = " << cc(x) << "\n";
    //}
        // auto ans = Euler(f, a, b, X1, X2, h);
        // printVector(ans.first);
        // printVector(ans.second);
        // ans = Runge(f, a, b, X1, X2, h);
        // printVector(ans.first);
        // printVector(ans.second);
        // ans = Adams(f, a, b, X1, X2, h);
        // printVector(ans.first);
        // printVector(ans.second);

    std::cout << "=====SUS=====\n";
    // auto l1 = [] (double x) -> double {
    //     return x;
    // };
    // auto l2 = [] (double x) -> double {
    //     return x - x - 1;
    // };
    // auto l3 = [] (double x) -> double {
    //     return x - x;
    // };
    //auto aaaa = FiniteDifference({l1, l2, l3}, 1, 1, 0, 1, 0.2);
    //system.push_back("y''-x*y'-y = 0");
    //system.push_back("y(0) = 1");
    //system.push_back("y'(1) + 2*y(1) = 0");
    std::vector<std::string> system;

    system.push_back("x*(x+1)*y''+(x+2)*y'-y = x+1/x");
    system.push_back("y'(1) = 3/2");
    system.push_back("4*y'(2) + y(2) = 13+4*ln(2)");
    std::string checkSTR = "x + 7 / 2 + 1 / x + (x / 2 + 1) * log(abs(x))";
    FunctionalTree check(checkSTR, {"x"});

    // system.push_back("(x**2-1)*y''+(x-3)*y'-y=0");
    // system.push_back("y(0)=-18");
    // system.push_back("y(3)= 0");
    // std::string checkSTR = "6*x - 18";
    // FunctionalTree check(checkSTR, {"x"});

    // system.push_back("x*y''-(2*x+1)*y'+2*y=0");
    // system.push_back("y'(0)=2");
    // system.push_back("y(1)= exp(2)");
    // std::string checkSTR = "exp(2*x)";
    // FunctionalTree check(checkSTR, {"x"});

    // system.push_back("y''- 2 * (1+(tan(x))**2)*y=0");
    // system.push_back("y(0)=0");
    // system.push_back("y(0.52359)=-0.57735");
    // std::string checkSTR = "0 - tan(x)";
    // FunctionalTree check(checkSTR, {"x"});

    // system.push_back("(x**2+1)*y''-2*y = 0"); //мой вариант
    // system.push_back("y'(0) = 2");
    // system.push_back("y(1) = 3+3.14/2");
    // std::string checkSTR = "x**2 + x + 1 + (x**2 + 1) * atan(x)";
    // FunctionalTree check(checkSTR, {"x"});

    auto aaaa = FiniteDifference(system, 0.1);
    auto bbbb = LeastSquareMethod(aaaa.first, aaaa.second, 4);
     plot({LSMToText(bbbb), checkSTR}, aaaa.first[0], aaaa.first.back());
    while (std::cin >> x) {
        std::cout << "Real Func(" << x << ") = " << check.func(x) << "\n";
        std::cout << "Wise mystical tree(" << x << ") = " << LSMFunc(bbbb, x) << "\n";
    }
    return 0;
}