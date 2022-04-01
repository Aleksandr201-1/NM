#ifndef MATRIX_FUNC_HPP
#define MATRIX_FUNC_HPP

#include "LU.hpp"
#include "RUN.hpp"
#include "SimpleIteration.hpp"

enum Method {
    LU_METHOD,
    RUN_METHOD,
    SIMPLE_ITERATION_METHOD,
    ZEIDEL_METHOD,
    SPIN_METHOD,
    QR_METHOD
};

bool is_equal(double x, double y) {
    return std::fabs(x - y) < std::numeric_limits<double>::epsilon();
}

template <class T>
void solveSLAE (Method method, const Matrix<T> &matrix, const std::vector<T> &b) {
    std::cout << "----------SOLVING SLAE----------\n";
    switch (method) {
        case LU_METHOD:
            LUsolveSLAE(matrix, b);
            break;
        case RUN_METHOD:
            RUNsolveSLAE(matrix, b);
            break;
        default:
            break;
    }
    std::cout << "--------------DONE--------------\n";
}

#endif