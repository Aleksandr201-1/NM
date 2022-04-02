#ifndef LU_HPP
#define LU_HPP

#include "Matrix.hpp"
#include "General.hpp"

template <class T>
void chooseMainEl (Matrix<T> &m, std::vector<T> &b) {
    std::cout << "-------CREATING A' MATRIX-------\n";
    uint64_t n = m.size().first;
    //bool exit = false;
    for (uint64_t i = 0; i < n; ++i) {
        T max = 0;
        uint64_t index = n;
        for (uint64_t j = i; j < n; ++j) {
            if (std::abs(m(j, i)) > std::abs(max)) {
                max = m(j, i);
                index = j;
            }
        }
        if (index == n && i != n - 1) {
            std::cout << "Can't create matrix A'. Stop working\n";
            exit(1);
        }
        if (index != i && i != n - 1) {
            m.swapRows(i, index);
            std::swap(b[i], b[index]);
            std::cout << "Swaping rows " << i << " and " << index << "\n";
        }
        // if (m(i, i) == null) {
        //     uint64_t j = 0;
        //     while (j < n && m(i, j) == null && m(j, i) == null) {
        //         ++j;
        //     }
        //     if (j == n) {
        //         std::cout << "Can't create matrix A'. Stop working\n";
        //         exit(1);
        //     }
        //     m.swapRows(i, j);
        //     std::swap(b[i], b[j]);
        //     std::cout << "Swaping rows " << i << " and " << j << "\n";
        // }
    }
    std::cout << "--------------DONE--------------\n";
}

template <class T>
std::tuple<Matrix<T>, Matrix<T>> LU (const Matrix<T> &m) {
    std::cout << "----CREATING LU DECOMPOSITION---\n";
    if (!m.isSquare() || is_equal(m.det(), T(0))) {
        return std::make_tuple(Matrix<T>(0), Matrix<T>(0));
    }
    uint64_t n = m.size().first;
    Matrix<T> L(n);
    Matrix<T> U(m);
    std::cout << "A = LU\nL = E\nU = A\n\nMatrix L:\n" << L << "\nMatrix U:\n" << U << "\n";//<< "\nIteration 0:\n";
    // for(uint64_t i = 0; i < n; ++i) {
    //     for(uint64_t j = i; j < n; ++j) {
    //         L(j, i) = U(j, i) / U(i, i);
    //         std::cout << "L(" << j << ", " << i << ") = U(" << j << ", " << i << ") / U(" << i << ", " << i << ") = " << L(j, i) << "\n";
    //     }
    // }
    for(uint64_t k = 1; k < n; ++k) {
        std::cout << "Iteration " << k << ":\n";
        for(uint64_t i = k - 1; i < n; ++i) {
            for(uint64_t j = i; j < n; ++j) {
                L(j, i) = U(j, i) / U(i, i);
                std::cout << "L(" << j << ", " << i << ") = U(" << j << ", " << i << ") / U(" << i << ", " << i << ") = " << L(j, i) << "\n";
            }
        }

        for(uint64_t i = k; i < n; ++i) {
            for(uint64_t j = k - 1; j < n; ++j) {
                U(i, j) = U(i, j) - L(i, k - 1) * U(k - 1, j);
                std::cout << "U(" << i << ", " << j << ") = U(" << i << ", " << j << ") - L(" << i << ", " << k - 1 << ") * U(" << k - 1 << ", " << j << ")" << "= " << U(i, j) << "\n";
            }
        }
    }
    std::cout << "--------------DONE--------------\n";
    return std::make_tuple(L, U);
}

template <class T>
void LUsolveSLAE (const Matrix<T> &m, const std::vector<T> &ans) {
    std::cout << "Ax = b\n\nMatrix A:\n" << m << "\nVector b:";
    for (uint64_t i = 0; i < ans.size(); ++i) {
        std::cout << " " << ans[i];
    }
    std::cout << "\n";
    if (!m.isSquare() || m.size().first != ans.size()) {
        std::cout << "Matrix is not square. Stop working.\n";
        return;
    }

    Matrix<T> A(m);
    std::vector<T> b(ans);
    chooseMainEl(A, b);
    std::cout << "Matrix A':\n" << A << "\n";
    std::cout << "Vector b':";
    for (uint64_t i = 0; i < b.size(); ++i) {
        std::cout << " " << b[i];
    }
    std::cout << "\n\n";

    uint64_t n = m.size().first;
    std::vector<T> x(n, T(0)), y(n, T(0));
    Matrix<T> L, U;
    std::tie(L, U) = LU(A);

    std::cout << "\nMatrix L:\n" << L << "\nMatrix U:\n" << U << "\n";

    y[0] = b[0];
    std::cout << "Solving system:\n" << "Ly = b\nUx = y\n\ny[0] = b[0] = " << b[0] << "\n";
    for (uint64_t i = 1; i < n; ++i) {
        y[i] = b[i];
        std::cout << "y[" << i << "] = b[" << i << "]";
        for (uint64_t j = 0; j < i; ++j) {
            y[i] -= y[j] * L(i, j);
            std::cout << " - y[" << j << "] * L(" << i << ", " << j << ")";
        }
        std::cout << " = " << y[i] << "\n";
    }
    std::cout << "\n";

    std::cout << "Vector y:";
    for (uint64_t i = 0; i < y.size(); ++i) {
        std::cout << " " << y[i];
    }
    std::cout << "\n\n";

    x[n - 1] = y[n - 1] / U(n - 1, n - 1);
    std::cout << "x[" << n - 1 << "] = y[" << n - 1 << "] / U(" << n - 1 << ", " << n - 1 << ") = " << x[n - 1] << "\n";
    for (uint64_t i = n - 2; i < n - 1; --i) {
        x[i] = y[i];
        std::cout << "x[" << i << "] = (y[" << i << "] ";
        for (uint64_t j = i + 1; j < n; ++j) {
            x[i] -= x[j] * U(i, j);
            std::cout << "- x[" << j << "] * U(" << i << ", " << j << ")";
        }
        x[i] /= U(i, i);
        std::cout << ") / U(" << i << " ," << i << ") = " << x[i] << "\n";
    }
    std::cout << "\n";

    std::cout << "Vector x:";
    for (uint64_t i = 0; i < x.size(); ++i) {
        std::cout << " " << x[i];
    }
    std::cout << "\n\n";

    std::cout << "det(A) = 1 ";
    T det = 1;
    for (uint64_t i = 0; i < n; ++i) {
        det *= U(i, i);
        std::cout << " * U(" << i << ", " << i << ")";
    }
    std::cout << " = " << det << "\n";
}

#endif