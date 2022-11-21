#include <iostream>
#include <cmath>
#include <vector>
#include <functional>
#include "gnuplot-iostream.h"
#include "FuncMaker.hpp"
#include "3-1.hpp"
#include "3-2.hpp"
#include "3-3.hpp"
#include "3-4.hpp"
#include "3-5.hpp"
//24

std::vector<double> getY (const std::vector<double> &X, const std::function<double(double)> &func) {
    std::vector<double> Y;
    for (uint64_t i = 0; i < X.size(); ++i) {
        Y.push_back(func(X[i]));
    }
    return Y;
}

void plot (const std::vector<std::string> &func, const std::vector<double> points) {
    static std::vector<std::string> colors = {"red", "green", "blue"};
    Gnuplot gp;

    gp << "set xlabel \"X\"\n";
    gp << "set ylabel \"Y\"\n";
    gp << "set xzeroaxis lw 1\n";
    gp << "set yzeroaxis lw 1\n";
    gp << "set grid\n";
    gp << "set title \"Plot\" font \"Helvetica Bold, 20\"\n";
    
    gp << "plot ";
    for (uint64_t i = 0; i < func.size(); ++i) {
        gp << func[i] << " title \"polynom " << i + 1 << "\"  lc rgb \"" << colors[i % colors.size()] << "\"";
        if (i == func.size() - 1) {
            if (points.size()) {
                gp << ", '-' " << " title \"our func\n";
                for (uint64_t j = 0; j < points.size(); j += 2) {
                    gp << points[j] << " " << points[j + 1] << "\n";
                }
                gp << "e\n";
            }
            gp << "\n";
        } else {
            gp << ",";
        }
    }
}

void plotCube (const std::vector<std::string> &func, const std::vector<std::pair<double, double>> points) {
    static std::vector<std::string> colors = {"red"};
    Gnuplot gp;

    gp << "set xlabel \"X\"\n";
    gp << "set ylabel \"Y\"\n";
    gp << "set xzeroaxis lw 1\n";
    gp << "set yzeroaxis lw 1\n";
    gp << "plot_if_in_range(y,x,lower,upper) = (x>=lower && x<=upper)?(y):(1.0/0)\n";
    //gp << "set yrange[-10:10]\n";
    //gp << "set xrange[0.1:1.7]\n";
    gp << "set xrange[" << points.front().first - 0.5 << ":" << points.back().first + 0.5 << "]\n";
    gp << "set grid\n";
    gp << "set title \"Plot\" font \"Helvetica Bold, 20\"\n";
    
    gp << "plot ";
    for (uint64_t i = 0; i < func.size(); ++i) {
        gp << "plot_if_in_range(" << func[i] << ", x, " << points[i].first - 0.05 << ", " << points[i + 1].first + 0.05 << ")";
        //gp << "[" << points[i] << ":" << points[i+1] << "]" << func[i] << " title \"polynom " << i + 1 << "\"  lc rgb \"" << colors[i % colors.size()] << "\"";
        if (i == func.size() - 1) {
            if (points.size()) {
                gp << ", '-' " << " title \"our func\n";
                for (uint64_t j = 0; j < points.size(); j += 1) {
                    gp << points[j].first << " " << points[j].second << "\n";
                    //gp << points[j] << "\n";
                }
                gp << "e\n";
            }
            gp << "\n";
        } else {
            gp << ",";
        }
    }
}

int main () {
    std::cout.precision(PRECISION);
    std::cout.setf(std::ios_base::fixed);

    auto func_maker = [] (FunctionalTree &&f) {
        return [&] (double x) {return f(x);};
    };
    uint64_t n = 0;
    std::string str_func;
    double check;

    //3.1
    std::cout << "=====3.1=====\n";
    std::cout << "Введите функцию для проверки:\n";
    std::getline(std::cin, str_func);
    FunctionalTree func1(str_func, {"x"});
    auto to_poly = func_maker(std::move(func1));
    //std::vector<double> X = {0.1, 0.5, 0.9, 1.3, 1.7, 2.1, 2.5, 2.9, 3.3};
    //std::vector<double> X = {0.1, 0.5, 0.9, 1.3};
    std::cout << "Введите размер векторов:\n";
    std::cin >> n;
    std::vector<double> X, Y;
    for (uint64_t i = 0; i < 2; ++i) {
        X.clear();
        std::cout << "Введите " << i + 1 << "-й вектор:\n";
        for (uint64_t i = 0; i < n; ++i) {
            double tmp;
            std::cin >> tmp;
            X.push_back(tmp);
        }
        Y = getY(X, to_poly);
        std::vector<double> L = Lagrange(X, Y);
        std::vector<double> N = Newton(X, to_poly);
        std::cout << "Введите точку для проверки:\n";
        std::cin >> check;
        std::string poly = printPolynom(L, X, Method::LAGRANGE);
        std::cout << "Полином Лагранжа: " << poly << "\n";
        poly = printPolynom(N, X, Method::NEWTON);
        std::cout << "Полином Ньютона: " << poly << "\n";
        //std::cout << LagrangeFunc(X, L, check) << " " << to_poly(check) << "\n";
        //std::cout << NewtonFunc(X, N, check) << " " << to_poly(check) << "\n";
        std::cout << "\nПогрешность Лагранжа: " << std::abs(LagrangeFunc(X, L, check) - to_poly(check)) << "\n";
        std::cout << "\nПогрешность Ньютона: " << std::abs(NewtonFunc(X, N, check) - to_poly(check)) << "\n";
        plot({printNewton(N, X), printLagrange(L, X)}, {});
    }
    //3.2
    std::cout << "=====3.2=====\n";
    std::cout << "Введите размер векторов и векторы:\n";
    std::cin >> n;
    X.clear();
    Y.clear();
    for (uint64_t i = 0; i < n; ++i) {
        double tmp;
        std::cin >> tmp;
        X.push_back(tmp);
    }
    for (uint64_t i = 0; i < n; ++i) {
        double tmp;
        std::cin >> tmp;
        Y.push_back(tmp);
    }
    std::cout << "Введите точку для проверки:\n";
    std::cin >> check;
    //X = {0.1, 0.5, 0.9, 1.3, 1.7};
    //Y = {100.00, 4.0, 1.2346, 0.59172, 0.34602};

    auto CS = CubeSpline(X, Y);
    std::cout << "Функция кубического сплайна Func(" << check << "): " << CubeSplineFunc(X, CS, check) << "\n";
    std::cout << "Настоящая Func(" << check << "): " << to_poly(check) << "\n";
    std::vector<std::string> cube;
    std::vector<std::pair<double, double>> p;
    for (uint64_t i = 0; i < X.size() - 1; ++i) {
        double tmp = (X[i + 1] + X[i]) / 2;
        cube.push_back(CubeSplineToText(X, CS, tmp));
        p.push_back(std::make_pair(X[i], Y[i]));
    }
    p.push_back(std::make_pair(X.back(), Y.back()));
    plotCube(cube, p);

    //3.3
    std::cout << "=====3.3=====\n";
    std::cout << "Введите размер векторов и векторы:\n";
    std::cin >> n;
    X.clear();
    Y.clear();
    for (uint64_t i = 0; i < n; ++i) {
        double tmp;
        std::cin >> tmp;
        X.push_back(tmp);
    }
    for (uint64_t i = 0; i < n; ++i) {
        double tmp;
        std::cin >> tmp;
        Y.push_back(tmp);
    }
    //X = {0.1, 0.5, 0.9, 1.3, 1.7, 2.1};
    //Y = {100.0, 4.0, 1.2346, 0.59172, 0.34602, 0.22676};
    std::vector<double> ann1 = LeastSquareMethod(X, Y, 1);
    std::vector<double> ann2 = LeastSquareMethod(X, Y, 2);
    std::vector<double> ann3 = LeastSquareMethod(X, Y, 5);

    std::cout << "МНК полином степени 1: " << LSMToText(ann1) << "\n";
    std::cout << "МНК полином степени 2: " << LSMToText(ann2) << "\n";
    std::cout << "МНК полином степени 5: " << LSMToText(ann3) << "\n";
    std::cout << "Сумма квадратов ошибок 1: " << ErrorSquareSum(X, Y, ann1) << "\n";
    std::cout << "Сумма квадратов ошибок 2: " << ErrorSquareSum(X, Y, ann2) << "\n";
    std::cout << "Сумма квадратов ошибок 5: " << ErrorSquareSum(X, Y, ann3) << "\n\n";
    std::vector<double> points;
    for (uint64_t i = 0; i < X.size(); ++i) {
        points.push_back(X[i]);
        points.push_back(Y[i]);
    }
    plot({LSMToText(ann1), LSMToText(ann2), LSMToText(ann3)}, points);

    //3.4
    std::cout << "\n=====3.4=====\n";
    std::cout << "Введите размер векторов и векторы:\n";
    std::cin >> n;
    X.clear();
    Y.clear();
    for (uint64_t i = 0; i < n; ++i) {
        double tmp;
        std::cin >> tmp;
        X.push_back(tmp);
    }
    for (uint64_t i = 0; i < n; ++i) {
        double tmp;
        std::cin >> tmp;
        Y.push_back(tmp);
    }
    //X = {1.0, 1.2, 1.4, 1.6, 1.8};
    //Y = {2.0, 2.1344, 2.4702, 2.9506, 3.5486};
    std::cout << "Производная 1: " << derirative1(X, Y, 1.4) << "\n";
    std::cout << "Производная 2: " << derirative2(X, Y, 1.4) << "\n";

    //3.5
    std::cout << "=====3.5=====\n";
    std::cout << "Введите функцию:\n";
    std::cin.ignore();
    std::cin.ignore();
    std::getline(std::cin, str_func);
    double X1 = -2, X2 = 2, h1 = 1, h2 = 0.5;
    std::cout << "Введите левую и правую границы интегрирования и размеры шагов:\n";
    std::cin >> X1 >> X2 >> h1 >> h2;
    //str_func = "sqrt(16 - x**2)";
    FunctionalTree func2(str_func, {"x"});
    auto to_integ = func_maker(std::move(func2));
    double r1, r2, t1, t2, s1, s2;
    r1 = IntegralRectangle(to_integ, X1, X2, h1);
    std::cout << "Метод прямоугольника (шаг " << h1 << "): " << r1 << "\n";
    r2 = IntegralRectangle(to_integ, X1, X2, h2);
    std::cout << "Метод прямоугольника (шаг " << h2 << "): " << r2 << "\n";
    t1 = IntegralTrapeze(to_integ, X1, X2, h1);
    std::cout << "Метод трапеции(шаг " << h1 << "): " << t1 << "\n";
    t2 = IntegralTrapeze(to_integ, X1, X2, h2);
    std::cout << "Метод трапеции(шаг " << h2 << "): " << t2 << "\n";
    s1 = IntegralSimpson(to_integ, X1, X2, h1);
    std::cout << "Метод Симпсона(шаг " << h1 << "): " << s1 << "\n";
    s2 = IntegralSimpson(to_integ, X1, X2, h2);
    std::cout << "Метод Симпсона(шаг " << h2 << "): " << s2 << "\n";

    std::cout << "Погрешность метода прямоугольника: " << IntegralRunge(r1, r2, h2 / h1, 1) << "\n";
    std::cout << "Погрешность метода трапеции: " << IntegralRunge(t1, t2, h2 / h1, 1) << "\n";
    std::cout << "Погрешность метода Симпсона: " << IntegralRunge(s1, s2, h2 / h1, 2) << "\n";

    return 0;
}