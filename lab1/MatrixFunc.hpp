#ifndef MATRIX_FUNC_HPP
#define MATRIX_FUNC_HPP

#include "LU.hpp"
#include "RUN.hpp"
#include "SI.hpp"

template <class T>
void solveSLAE (Method method, const Matrix<T> &matrix, const std::vector<T> &b) {
    std::cout << "----------SOLVING SLAE----------\n";
    T approx = 1;
    switch (method) {
        case LU_METHOD:
            LUsolveSLAE(matrix, b);
            break;
        case RUN_METHOD:
            RUNsolveSLAE(matrix, b);
            break;
        case SI_YAKOBI_METHOD:
        case SI_ZEIDEL_METHOD:
            std::cout << "Enter approximation: ";
            std::cin >> approx;
            std::cout << "\n";
            SISolveSLAE(matrix, b, approx, method);
            break;
        default:
            break;
    }
    std::cout << "--------------DONE--------------\n";
}

#endif