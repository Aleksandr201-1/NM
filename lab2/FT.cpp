#include <iostream>
#include "FuncMaker.hpp"

// return x;
// return std::pow(2.0, x) - std::sin(x);
// return std::pow(2.0, x) - std::sin(x) + (x - 10) / 2;
// return (x - 10) / 2;
// return x + 10 * 10;
// return std::sin(x) + 10;
// return (x + 3*3) * (std::log10(std::sin(x)) + 10);
// return std::sin(std::sin(x));

double realFunky1 (double x) {
    return x;
}

double realFunky2 (double x) {
    return std::pow(2.0, x) - std::sin(x);

}

double realFunky3 (double x) {
    return std::pow(2.0, x) - std::sin(x) + (x - 10) / 2;
}

double realFunky4 (double x) {
    return (x - 10) / 2;
}

double realFunky5 (double x) {
    return x + 10 * 10;
}

double realFunky6 (double x) {
    return std::sin(x) + 10;
}

double realFunky7 (double x) {
    return (x + 3*3) * (std::log10(std::sin(x)) + 10);
}

double realFunky8 (double x) {
    return std::sin(std::sin(x));
}

int main () {
    std::string funky1 = "x";
    std::string funky2 = "2^x - sin(x)";
    std::string funky3 = "2^x - sin(x) + (x - 10) / 2";
    std::string funky4 = "(x - 10) / 2";
    std::string funky5 = "x + 10 * 10";
    std::string funky6 = "sin(x) + 10";
    std::string funky7 = "(x + 3^2) * (log(sin(x)) + 10)";
    std::string funky8 = "sin(sin(x))";
    // FunctionalTree tree1(funky1);
    // FunctionalTree tree2(funky2);
    // FunctionalTree tree3(funky3);
    // FunctionalTree tree4(funky4);
    // FunctionalTree tree5(funky5);
    // FunctionalTree tree6(funky6);
    // FunctionalTree tree7(funky7);
    // FunctionalTree tree8(funky8);
    //FunctionalTree trees[] = {tree1, tree2};
    //std::vector<FunctionalTree> trees = {std::move(FunctionalTree(funky1)), FunctionalTree(funky2), FunctionalTree(funky3), FunctionalTree(funky4) , FunctionalTree(funky5) , FunctionalTree(funky6) , FunctionalTree(funky7) , FunctionalTree(funky8)};
    std::vector<FunctionalTree> trees;
    trees.push_back(std::move(FunctionalTree(funky1)));
    trees.push_back(std::move(FunctionalTree(funky2)));
    trees.push_back(std::move(FunctionalTree(funky3)));
    trees.push_back(std::move(FunctionalTree(funky4)));
    trees.push_back(std::move(FunctionalTree(funky5)));
    trees.push_back(std::move(FunctionalTree(funky6)));
    trees.push_back(std::move(FunctionalTree(funky7)));
    trees.push_back(std::move(FunctionalTree(funky8)));
    std::vector<double (*)(double)> funcs = {realFunky1, realFunky2, realFunky3, realFunky4, realFunky5, realFunky6, realFunky7, realFunky8};
    //std::cout << "-----------\n";
    //tree.printTree();
    //std::cout << "-----------\n";
    double x;
    uint64_t j = 0;
    std::cin >> j;
    while (std::cin >> x) {
        if (j == -1) {
            for (uint64_t i = 0; i < trees.size(); ++i) {
                double a = trees[i].func(x), b = funcs[i](x);
                std::cout << "Test " << i << ": ";
                if (a == b) {
                    std::cout << "OK\n";
                } else {
                    std::cout << "NOT OK\n";
                }
            }
        } else {
            std::cout << "Tree " << j << ": " << trees[j].func(x) << "\n";
            std::cout << "Funky " << j << ": " << funcs[j](x) << "\n";
        }
    }
    
    return 0;
}