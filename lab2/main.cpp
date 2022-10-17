#include <string>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <thread>
#include "FuncMaker.hpp"
#include "gnuplot-iostream.h"
#include "2-1.hpp"
#include "2-2.hpp"

FunctionalTree tree_func1, tree_func2, tree_func3, tree_fi1, tree_fi2, tree_fi3;

template <class T>
void printVector(const std::vector<T> &vec) {
    for (uint64_t i = 0; i < vec.size(); ++i) {
        std::cout << vec[i];
        if (i != vec.size() - 1) {
            std::cout << " ";
        }
    }
}

//2.1
double function (double x) {
    return tree_func1(x);
}

double fi (double x) {
    return tree_fi1(x);
}

//2.2
double f1(const std::vector<double> &x) {
    return tree_func2(x);
}

double f2(const std::vector<double> &x) {
    return tree_func3(x);
}

double fi1(const std::vector<double> &x) {
    return -(f1(x) - x[0]);
}

double fi2(const std::vector<double> &x) {
    return -(f2(x) - x[1]);
}

void plot (const std::vector<std::string> &func) {
    static std::vector<std::string> colors = {"red", "green", "blue"};
    Gnuplot gp;
    gp << "set xlabel \"X\"\n";
    gp << "set ylabel \"Y\"\n";
    gp << "set xzeroaxis lw 1\n";
    gp << "set yzeroaxis lw 1\n";
    gp << "set grid\n";
    gp << "set yrange [-1:5]\n";
    gp << "set xrange[-1:5]\n";
    gp << "set title \"Plot\" font \"Helvetica Bold, 20\"\n";
    
    gp << "plot ";
    for (uint64_t i = 0; i < func.size(); ++i) {
        gp << func[i] << " title \"function " << i + 1 << "\"  lc rgb \"" << colors[i] << "\"";
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
    //2.1
    std::cout << "=====2.1=====\n";
    std::cout.setf(std::ios_base::fixed);
    std::vector<std::string> stringFunc;
    std::string str;

    std::cout << "Enter function:\n";
    str = readLine();
    tree_func1.reset(str, {"x"});
    stringFunc.push_back(str);

    std::cout << "Enter function fi:\n";
    str = readLine();
    tree_fi1.reset(str, {"x"});

    plot(stringFunc);
    double approx, x0, y0, a, b;
    std::cout << "\nEnter approximation:\n";
    std::cin >> approx;
    std::cout << "Enter begining point:\n";
    std::cin >> x0;
    std::cout << "Enter graph boundaries:\n";
    std::cin >> a >> b;

    try {
        auto N1ans = Newton(x0, approx, function);
        std::cout << "\nNewton answer: " << N1ans.first << "\nIterations: " << N1ans.second << "\nCheck: f(" << N1ans.first << ") = " << function(N1ans.first) << "\n";
    } catch (std::exception &exp) {
        std::cerr << exp.what() << "\n";
    }

    try {
        auto SI1ans = SI(x0, a, b, approx, fi);
        std::cout << "\nSimple iterations answer: " << SI1ans.first << "\nIterations: " << SI1ans.second << "\nCheck: f(" << SI1ans.first << ") = " << function(SI1ans.first) << "\n\n";
    } catch (std::exception &exp) {
        std::cerr << exp.what() << "\n";
    }

    //2.2
    std::cout << "=====2.2=====\n";
    std::cout << "Enter system:\n";
    str = readLine();
    tree_func2.reset(str, {"x", "y"});
    str = readLine();
    tree_func3.reset(str, {"x", "y"});

    std::cout << "Enter system fi:\n";
    str = readLine();
    tree_fi2.reset(str, {"x", "y"});
    str = readLine();
    tree_fi3.reset(str, {"x", "y"});
    std::vector<std::string> systemOfFunc = {"tan(x)", "sqrt(x + 1 - 3.0*x**2)"}; //24
    //std::vector<std::string> systemOfFunc = {"8 / (x**2 + 4)", "-sqrt(4 - (x - 1)**2) + 1"}; //1
    //std::vector<std::string> systemOfFunc = {"acos(-x - 0.9)", "log10(x + 1) + 3"}; //2
    //std::vector<std::string> systemOfFunc = {"sqrt(9 - x**2)", "log(x + 3)"}; //3
    plot(systemOfFunc);

    std::cout << "\nEnter approximation:\n";
    std::cin >> approx;
    std::cout << "Enter begining points:\n";
    std::cin >> x0 >> y0;
    std::cout << "\n";

    try {
        auto N2ans = Newton({f1, f2}, {x0, y0}, approx);
        std::cout << "Newton answer: (";
        printVector(N2ans.first);
        std::cout << ")\nIterations: " << N2ans.second << "\nCheck: f1(";
        printVector(N2ans.first);
        std::cout << ") = " << f1(N2ans.first) << "\nf2(";
        printVector(N2ans.first);
        std::cout << ") = " << f2(N2ans.first) << "\n\n";
    } catch (std::exception &exp) {
        std::cerr << exp.what() << "\n\n";
    }

    try {
        auto SI2ans = SI({fi1, fi2}, {x0, y0}, approx);
        std::cout << "Simple iterations answer: (";
        printVector(SI2ans.first);
        std::cout << ")\nIterations: " << SI2ans.second << "\nCheck: f1(";
        printVector(SI2ans.first);
        std::cout << ") = " << f1(SI2ans.first) << "\nf2(";
        printVector(SI2ans.first);
        std::cout << ") = " << f2(SI2ans.first) << "\n";
    } catch (std::exception &exp) {
        std::cerr << exp.what() << "\n";
    }

    return 0;
}