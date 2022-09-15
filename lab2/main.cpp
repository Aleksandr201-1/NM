#include <string>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <thread>
#include "gnuplot-iostream.h"
#include "2-1.hpp"
#include "2-2.hpp"

template <class T>
void printVector(const std::vector<T> &vec) {
    for (T el : vec) {
        std::cout << el << " ";
    }
    std::cout << "\n";
}

//x^6 - 5*x - 2
double function (double x) {
    return std::pow(x, 6) - 5 * x - 2;
    //return std::sqrt(x + 2) - 2 * std::cos(x);
}

//(5x + 2)^(1/6)
double fi (double x) {
    //return (std::pow(x, 6) - 2.0) / 5.0;
    return std::pow(5.0 * x + 2.0, 1.0 / 6.0);
    //return std::pow(x, 6) - 4 * x - 2;
    //return std::acos(0.5*std::sqrt(x + 2));
}

double f1(const std::vector<double> &x) {
    return 0.1 * x[0] * x[0] + x[0] + 0.2 * x[1] * x[1] - 0.3;
}

double f2(const std::vector<double> &x) {
    return 0.2 * x[0] * x[0] + x[1] - 0.1 * x[0] * x[1] - 0.7;
}

double fi1(const std::vector<double> &x) {
    return 0.3 - 0.1 * x[0] * x[0] - 0.2 * x[1] * x[1];
}

double fi2(const std::vector<double> &x) {
    return 0.7 - 0.2 * x[0] * x[0] + 0.1 * x[0] * x[1];
}

void plot () {
    Gnuplot gp;
    gp << "set xlabel \"X\"\n";
    gp << "set ylabel \"Y\"\n";
    gp << "set grid\n";
    gp << "set yrange [-10:10]\n";
    gp << "set xrange[-3:3]\n";
    gp << "set title \"Plot\" font \"Helvetica Bold, 20\"\n";
    gp << "plot x**6 - 5*x - 2 title \"our function\"  lc rgb \"red\"\n";
}

int main () {
    //std::vector<double> ans = Newton({f1, f2}, {0.25, 0.75}, 0.01);
    std::vector<double> ans = SI({fi1, fi2}, {0.25, 0.75}, 0.01);
    std::cout << "System solve: ";
    printVector(ans);
    return 0;
    std::cout.setf(std::ios_base::fixed);
    std::thread thr(plot);

    double approx, x0, a, b;
    std::string func;
    std::cout << "Enter approximation: ";
    std::cin >> approx;
    std::cout << "Enter begining point: ";
    std::cin >> x0;
    if (!checkNewton(x0, function)) {
        std::cout << "Incorrect begining point\n";
        return 0;
    }
    std::cout << "Enter graph boundaries: ";
    std::cin >> a >> b;

    auto Nans = Newton(x0, approx, function), SIans = simple_iteration(x0, a, b, approx, fi);

    std::cout << "\nSimple iterations\nAnswer: " << SIans.first << "\nIterations: " << SIans.second << "\nCheck: f(" << SIans.first << ") = " << function(SIans.first) << "\n";
    std::cout << "\nNewton\nAnswer: " << Nans.first << "\nIterations: " << Nans.second << "\nCheck: f(" << Nans.first << ") = " << function(Nans.first) << "\n";

    thr.join();
    return 0;
}