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

uint64_t ITERATION_LIMIT = 50, PRECISION = 2;;

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

template <class T>
void roundMatrix (Matrix<T> &A) {
    T min = 1;
    for (uint64_t i = 0; i < PRECISION; ++i) {
        min /= T(10);
    }
    for (uint64_t i = 0; i < A.size().n; ++i) {
        for (uint64_t j = 0; j < A.size().m; ++j) {
            if (std::abs(A(i, j)) < min) {
                A(i, j) = T(0);
            }
        }
    }
}

#endif