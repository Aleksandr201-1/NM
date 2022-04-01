#ifndef SIMPLE_ITERATION_HPP
#define SIMPLE_ITERATION_HPP

#include <iostream>
#include "Matrix.hpp"

template <class T>
bool SimpleIterationCheck (const Matrix<T> &matrix, const std::vector<T> &b) {
    return false;
}

template <class T>
void SimpleIterationSolveSLAE (const Matrix<T> &matrix, const std::vector<T> &b, uint64_t approx = 0) {
    uint64_t n = matrix.size().first;
    std::vector<T> beta(n), x(n);
    Matrix<T> alpha(n, n);
    for (uint64_t i = 0; i < n; ++i) {
        for (uint64_t j = 0; i < i; ++j) {
            alpha(i, j) = matrix(i, j) / matrix(i, i);
        }
        for (uint64_t j = i + 1; i < n; ++j) {
            alpha(i, j) = matrix(i, j) / matrix(i, i);
        }
        beta[i] = b[i] / matrix(i, i);
    }
    std::cout << "Vector x:\n";
}

#endif