#ifndef LU_HPP
#define LU_HPP

#include "General.hpp"

template <class T>
Matrix<T> createP (const Matrix<T> &matrix) {
    uint64_t n = matrix.size().n;
    Matrix<T> P(n), A(matrix);
    for (uint64_t i = 0; i < n; ++i) {
        uint64_t toSwap = i;
        T max = std::abs(matrix(i, i));
        for (uint64_t j = i + 1; j < n; ++j) {
            if (std::abs(matrix(j, i)) > max) {
                max = std::abs(matrix(j, i));
                toSwap = j;
            }
        }
        if (max == T(0)) {
            std::cout << "Can't create matrix P. Stop working.\n";
            exit(-1);
        }
        if (toSwap != i) {
            P.swapRows(i, toSwap);
            A.swapRows(i, toSwap);
        }
        for (uint64_t j = i + 1; j < n; ++j) {
            T tmp = P(j, i) / P(i, i);
            for (uint64_t k = i + 1; k < n; ++k) {
                A(j, k) -= tmp * A(i, k);
            }
        }
    }
    return P;
}

template <class T>
std::tuple<Matrix<T>, Matrix<T>, Matrix<T>> LU (const Matrix<T> &matrix) {
    std::cout << "====CREATING LU DECOMPOSITION===\n";
    if (!matrix.isSquare() || is_equal(matrix.det(), T(0))) {
        return std::make_tuple(Matrix<T>(0), Matrix<T>(0), Matrix<T>(0));
    }
    uint64_t n = matrix.size().n;
    Matrix<T> L(n), U(matrix), P(n);
    std::cout << "A = LU\nL = E\nU = A\n\nMatrix L:\n" << L << "\nMatrix U:\n" << U << "\n";
    P = createP(matrix);
    U = P * U;
    for(uint64_t k = 1; k < n; ++k) {
        std::cout << "------------\n";
        std::cout << "Step " << k << ":\n";
        for(uint64_t i = k - 1; i < n; ++i) {
            for(uint64_t j = i; j < n; ++j) {
                L(j, i) = U(j, i) / U(i, i);
                std::cout << "L(" << j << ", " << i << ") = U(" << j << ", " << i << ") / U(" << i << ", " << i << ") = " << L(j, i) << "\n";
            }
        }
        for(uint64_t i = k; i < n; ++i) {
            for(uint64_t j = k - 1; j < n; ++j) {
                U(i, j) = U(i, j) - L(i, k - 1) * U(k - 1, j);
                std::cout << "U(" << i << ", " << j << ") = U(" << i << ", " << j << ") - L(" << i << ", " << k - 1 << ") * U(" << k - 1 << ", " << j << ")" << " = " << U(i, j) << "\n";
            }
        }
        std::cout << "Current L:\n" << L << "\nCurrent U:\n" << U << "\n";
    }
    std::cout << "==============DONE==============\n";
    return std::make_tuple(L, U, P);
}

template <class T>
void LUsolveSLAE (const Matrix<T> &matrix, const std::vector<T> &ans) {
    uint64_t n = matrix.size().n;
    std::cout << "Ax = b\n\nMatrix A:\n" <<matrix<< "\n";
    printVector("b", ans);
    std::cout << "\n";

    if (!matrix.isSquare() || n != ans.size()) {
        std::cout << "Matrix is not square. Stop working.\n";
        return;
    }
    if (n != ans.size()) {
        std::cout << "Matrix and vector have different sizes. Stop working.\n";
        return;
    }

    Matrix<T> A(matrix);
    std::vector<T> x(n, T(0)), y(n, T(0));
    Matrix<T> L, U, P;
    std::tie(L, U, P) = LU(A);
    std::vector<T> b = (P * Matrix<T>(n, 1, ans)).toVector();

    std::cout << "Matrix A':\n" << A << "\n";
    printVector("b", b);
    std::cout << "\nPA = LU\n";

    std::cout << "\nMatrix L:\n" << L << "\nMatrix U:\n" << U << "\nPt * L * U:\n" << P.transp() * L * U << "\nMatrix P:\n" << P << "\n";

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
    printVector("y", y);
    std::cout << "\n";

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
    printVector("x", x);
    std::cout << "\n";

    std::cout << "det(A) = 1";
    T det = 1;
    for (uint64_t i = 0; i < n; ++i) {
        det *= U(i, i);
        std::cout << " * U(" << i << ", " << i << ")";
    }
    std::cout << " = " << det << "\n\n";

    std::cout << "Finding reverse matrix Ar\nPr * L * U * Ar = E\nL * Lr = E\nU * Ur = E\nAr = Ur * Lr * P\n\n";
    Matrix<T> Ar(A), Lr(n), Ur(n);
    
    std::cout << "Creating Lr:\n";
    for (uint64_t i = 0; i < n; ++i) {
        Lr(i, i) = 1.0 / L(i, i);
        std::cout << "Lr(" << i << ", " << i << ") = 1.0 / L(" << i << ", " << i << ")\n";
        for (uint64_t j = i + 1; j < n; ++j) {
            T tmp = 0;
            std::cout << "Lr(" << j << ", " << i << ") = (0";
            for (uint64_t k = 0; k < j; ++k) {
                tmp -= L(j, k) * Lr(k, i);
                std::cout << " + L(" << j << ", " << k << ") * Lr(" << k << ", " << i << ")";
            }
            std::cout << ") / L(" << j << ", " << j << ")\n";
            Lr(j, i) = tmp / L(j, j);
        }
    }
    std::cout << "Matrix Lr:\n" << Lr << "\n";

    std::cout << "Creating Ur:\n";
    for (uint64_t i = n - 1; i < n; --i) {
        Ur(i, i) = 1.0 / U(i, i);
        std::cout << "Ur(" << i << ", " << i << ") = 1.0 / U(" << i << ", " << i << ")\n";
        for (uint64_t j = i - 1; j < n; --j) {
            T tmp = 0;
            std::cout << "Ur(" << j << ", " << i << ") = (0";
            for (uint64_t k = i; k > j; --k) {
                tmp -= U(j, k) * Ur(k, i);
                std::cout << " + U(" << j << ", " << k << ") * Ur(" << k << ", " << i << ")";
            }
            std::cout << ") / U(" << j << ", " << j << ")\n";
            Ur(j, i) = tmp / U(j, j);
        }
    }
    std::cout << "Matrix Ur:\n" << Ur << "\n";

    Ar = Ur * Lr * P;
    std::cout << "Matrix Ar:\n" << Ar << "\nAr * A:\n" << Ar * matrix << "\n";
}

#endif