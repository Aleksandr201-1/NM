#ifndef GENERAL_HPP
#define GENERAL_HPP

#include <iostream>
#include <tuple>
#include <limits>
#include <cmath>

enum Method {
    LU_METHOD,
    RUN_METHOD,
    SI_YAKOBI_METHOD,
    SI_ZEIDEL_METHOD,
    SPIN_METHOD,
    QR_METHOD
};

bool is_equal(double x, double y) {
    return std::fabs(x - y) < std::numeric_limits<double>::epsilon();
}

template <class T>
void printVector (const std::string &name, const std::vector<T> &vec) {
    std::cout << "Vector " << name << ":";
    for (uint64_t i = 0; i < vec.size(); ++i) {
        std::cout << " " << vec[i];
    }
    std::cout << "\n";
}

#endif