#ifndef GENERAL_HPP
#define GENERAL_HPP

#include <iostream>
#include <tuple>
#include <limits>
#include <cmath>
#include "Matrix.hpp"

enum Method {
    LU_METHOD,
    RUN_METHOD,
    SI_YAKOBI_METHOD,
    SI_ZEIDEL_METHOD,
    SPIN_METHOD,
    QR_METHOD
};

template <class T>
bool is_equal(T x, T y) {
    return std::fabs(x - y) < std::numeric_limits<T>::epsilon();
}

template <class T>
void printVector (const std::string &name, const std::vector<T> &vec) {
    std::cout << "Vector " << name << ":";
    for (auto el : vec) {
        std::cout << " " << el;
    }
    std::cout << "\n";
}

#endif