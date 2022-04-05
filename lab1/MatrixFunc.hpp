#ifndef MATRIX_FUNC_HPP
#define MATRIX_FUNC_HPP

#include "LU.hpp"
#include "RUN.hpp"
#include "SI.hpp"
#include "SPIN.hpp"
#include "QR.hpp"

template <class T>
void solveSLAE (Method method, const Matrix<T> &matrix) {
    std::cout << "==========SOLVING SLAE==========\n";
    T approx = 1;
    std::vector<T> b(matrix.size().n);

    if (method <= SI_ZEIDEL_METHOD) {
        std::cout << "Enter vector b: ";
        for (uint64_t i = 0; i < b.size(); ++i) {
            std::cin >> b[i];
        }
        std::cout << "\n";
    }
    if (method >= SI_YAKOBI_METHOD) {
        std::cout << "Enter approximation: ";
        std::cin >> approx;
        std::cout << "\n";
    }

    switch (method) {
        case LU_METHOD:
            LUsolveSLAE(matrix, b);
            break;
        case RUN_METHOD:
            RUNsolveSLAE(matrix, b);
            break;
        case SI_YAKOBI_METHOD:
        case SI_ZEIDEL_METHOD:
            SISolveSLAE(matrix, b, approx, method);
            break;
        case SPIN_METHOD:
            SPINsolveSLAE(matrix, approx);
            break;
        case QR_METHOD:
            QRsolveSLAE(matrix, approx);
            break;
        default:
            break;
    }
    std::cout << "==============DONE==============\n";
}

#endif