#ifndef SPIN_HPP
#define SPIN_HPP

#include "General.hpp"

template <class T>
T SqrtSqrSum (const Matrix<T> &matrix) {
    T sum = 0;
    for (uint64_t i = 0; i < matrix.size().n; ++i) {
        for (uint64_t j = i + 1; j < matrix.size().n; ++j) {
            sum += matrix(i, j) * matrix(i, j);
        }
    }
    return std::sqrt(sum);
}

template <class T>
std::tuple<T, uint64_t, uint64_t> MaxNonDiagonalEl (const Matrix<T> &matrix) {
    T max = 0;
    uint64_t im = 0, jm = 0;
    for (uint64_t i = 0; i < matrix.size().n; ++i) {
        for (uint64_t j = i + 1; j < matrix.size().n; ++j) {
            if (std::abs(matrix(i, j)) > max) {
                max = matrix(i, j);
                im = i;
                jm = j;
            }
        }
    }
    return std::make_tuple(max, im, jm);
}

template <class T>
void SPINsolveSLAE (const Matrix<T> &matrix, T approx) {
    uint64_t n = matrix.size().n;
    Matrix<T> A(matrix), Ufin(n);
    std::vector<T> lambda(n);
    std::cout << "Matrix A:\n" << matrix << "\nEpsilon = " << approx << "\n";

    if (!matrix.isSymmetric()) {
        std::cout << "Matrix is symmetrical. Stop working.\n";
        return;
    }

    std::cout << "------------\n";
    std::cout << "Iteration 0:\nA(0) = A\n";
    uint64_t iteration = 0;
    while (1) {
        ++iteration;
        std::cout << "------------\n";
        std::cout << "Iteration " << iteration << ":\n";
        std::cout << "1. Finding max non-diagonal element\n";
        T aij;
        Matrix<T> Uk(n);
        uint64_t im, jm;
        std::tie(aij, im, jm) = MaxNonDiagonalEl(A);
        std::cout << "Max element: " << aij << " at cell (" << im << ", " << jm << ")\n\n"; 
        T phi = (1.0 / 2.0) * std::atan(2 * aij / (A(im, im) - A(jm, jm)));
        Uk(im, im) = Uk(jm, jm) = std::cos(phi);
        Uk(im, jm) = -std::sin(phi);
        Uk(jm, im) = std::sin(phi);
        A = Uk.transp() * A * Uk;
        T epsilon = SqrtSqrSum(A);
        std::cout << "2. Finding matrix U(" << iteration << ")\n";
        std::cout << "phi = 1 / 2 * arctg(2 * A(" << im << ", " << jm << ") / A(" << im << ", " << im << ") - A(" << jm << ", " << jm << ") = " << phi << "\n"; 
        std::cout << "Matrix U(" << iteration << "):\n" << Uk << "\n";
        std::cout << "3. Finding A(" << iteration << ")\n";
        std::cout << "A(" << iteration << ") = Tr(U(" << iteration << ")) * A(" << iteration - 1 << ") * U(" << iteration << ")\n";
        std::cout << "Matrix A:\n" << A << "\n";
        std::cout << "Epsilon = " << epsilon << "\n";
        Ufin = Ufin * Uk;
        if (epsilon < approx || iteration > ITERATION_LIMIT) {
            break;
        }
    }
    for (uint64_t i = 0; i < n; ++i) {
        lambda[i] = A(i, i);
    }
    std::cout << "Final answer:\n";
    printVector("lambda", lambda);
    std::cout << "\n";
    for (uint64_t i = 0; i < n; ++i) {
        std::cout << "Vector x" << i << ":";
        for (uint64_t j = 0; j < n; ++j) {
            std::cout << " " << Ufin(j, i);
        }
        std::cout << "\n";
    }
}

#endif