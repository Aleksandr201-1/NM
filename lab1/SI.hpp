#ifndef SIMPLE_ITERATION_HPP
#define SIMPLE_ITERATION_HPP

#include "General.hpp"

template <class T>
T SINormal (const Matrix<T> &matrix) {
    std::cout << "=====Simple Iteration Normal====\n";
    uint64_t n = matrix.size().n;
    T max = 0;
    for (uint64_t i = 0; i < n; ++i) {
        T tmp = 0;
        for (uint64_t j = 0; j < n; ++j) {
            tmp += std::abs(matrix(i, j));
        }
        std::cout << "Line " << i << ", Sum " << tmp << "\n";
        if (tmp > max) {
            max = tmp;
        }
    }
    std::cout << "Choosing " << max << "\n";
    std::cout << "==============DONE==============\n";
    return max;
}

template <class T>
T FindEpsilon (const std::vector<T> &oldX, const std::vector<T> &newX, T a) {
    T eps = 0;
    for (uint64_t i = 0; i < oldX.size(); ++i) {
        T tmp = std::abs(oldX[i] - newX[i]);
        if (tmp > eps) {
            eps = tmp;
        }
    }
    return eps * a / (T(1) - a);
}

template <class T>
void SISolveSLAE (const Matrix<T> &matrix, const std::vector<T> &b, T approx, Method method) {
    uint64_t n = matrix.size().n;
    std::vector<T> beta(n), x(n);
    Matrix<T> alpha(n, n);

    std::cout << "Ax = b\n\nMatrix A:\n" << matrix << "\n";
    printVector("b", b);
    std::cout << "\nEpsilon = " << approx << "\n";

    if (!matrix.isSquare() || n != b.size()) {
        std::cout << "Matrix is not square. Stop working.\n";
        return;
    }
    if (n != b.size()) {
        std::cout << "Matrix and vector have different sizes. Stop working.\n";
        return;
    }

    std::cout << "Creating matrix 'alpha' and vector 'beta'\n";
    for (uint64_t i = 0; i < n; ++i) {
        for (uint64_t j = 0; j < i; ++j) {
            alpha(i, j) = -matrix(i, j) / matrix(i, i);
            std::cout << "alpha(" << i << ", " << j << ") = -A(" << i << ", " << j << ") / A(" << i << ", " << i << ")\n";
        }
        for (uint64_t j = i + 1; j < n; ++j) {
            alpha(i, j) = -matrix(i, j) / matrix(i, i);
            std::cout << "alpha(" << i << ", " << j << ") = -A(" << i << ", " << j << ") / A(" << i << ", " << i << ")\n";
        }
        beta[i] = b[i] / matrix(i, i);
        std::cout << "beta[" << i << "] = b[" << i << "] / A(" << i << ", " << i << ")\n";
        x[i] = beta[i];
    }
    std::cout << "Matrix alpha:\n" << alpha;
    printVector("beta", beta);
    T a = SINormal(alpha);
    uint64_t iteration = 0;
    T epsilon = T(0);
    if (a > T(1)) {
        std::cout << "Normal greater than 1. Stop working\n";
        return;
    }

    std::cout << "\n";
    std::cout << "Iteration 0:\n";
    printVector("x", x);
    while (1) {
        ++iteration;
        std::cout << "Iteration " << iteration << ":\n";
        std::vector<T> newX(x);
        for (uint64_t i = 0; i < n; ++i) {
            newX[i] = beta[i];
            std::cout << "x(" << iteration << ")[" << i << "] = beta[" << i << "]";
            if (method == SI_ZEIDEL_METHOD) {
                for (uint64_t j = 0; j < i; ++j) {
                    newX[i] += alpha(i, j) * newX[j];
                    std::cout << " + alpha(" << i << ", " << j << ") * x(" << iteration << ")[" << j << "]";
                }
                for (uint64_t j = i; j < n; ++j) {
                    newX[i] += alpha(i, j) * x[j];
                    std::cout << " + alpha(" << i << ", " << j << ") * x(" << iteration - 1 << ")[" << j << "]";
                }
            } else {
                for (uint64_t j = 0; j < n; ++j) {
                    newX[i] += alpha(i, j) * x[j];
                    std::cout << " + alpha(" << i << ", " << j << ") * x(" << iteration - 1 << ")[" << j << "]";
                }
            }
            std::cout << "\n";
        }
        epsilon = FindEpsilon(x, newX, a);
        x = newX;
        printVector("x", x);
        std::cout << "E = " << epsilon << "\n";
        if (epsilon < approx) {
            break;
        }
    }
    std::cout << "Final answer:\n";
    printVector("x", x);
    std::cout << "Count of iterations: " << iteration << "\n";
}

#endif