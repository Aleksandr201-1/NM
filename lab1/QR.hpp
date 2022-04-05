#ifndef QR_HPP
#define QR_HPP

#include "General.hpp"

template <class T>
T getMainEl (const Matrix<T> &matrix, uint64_t i) {
    T ans = matrix(i, i), tmp = 0;
    T sign = ans > T(0) ? T(1) : T(-1);
    for (uint64_t j = i; j < matrix.size().n; ++j) {
        tmp += matrix(j, i) * matrix(j, i);
    }
    return ans + sign * std::sqrt(tmp);
}

template <class T>
std::tuple<Matrix<T>, Matrix<T>> QR (const Matrix<T> &matrix) {
    std::cout << "Matrix A:\n" << matrix << "\n";
    uint64_t n = matrix.size().n;
    Matrix<T> Q(n), R(matrix), v(n, 1);
    std::vector<Matrix<T>> HouseHolder;

    std::cout << "Iteration 0:\nA(0) = A\n";
    for (uint64_t i = 0; i < n - 1; ++i) {
        std::cout << "Iteration " << i << ":\n";
        for (uint64_t j = 0; j < i; ++j) {
            v(j, 0) = 0;
        }
        v(i, 0) = getMainEl(R, i);
        for (uint64_t j = i + 1; j < n; ++j) {
            v(j, 0) = R(j, i);
        }
        std::cout << "Vector v(" << i << "):\n" << v << "\n";
        std::cout << "v transp:" << v.transp() << "\n";
        std::cout << "ABOA: " << (v.transp() * v) << "\n";
        std::cout << "v * vT:\n" << v * v.transp() << "\n";

        Matrix<T> H = Matrix<T>(n) - 2 * ((v * v.transp()) / (v.transp() * v)(0, 0));
        std::cout << "Matrix H(" << i << "):\n" << H << "\n";
        R = H * R;
        std::cout << "Matrix A(" << i << "):\n" << R << "\n";
        HouseHolder.push_back(H);
    }
    for (auto el : HouseHolder) {
        Q = Q * el;
    }
    std::cout << "Matrix R:\n" << R << "\nMatrix Q:\n" << Q << "\n";
    return std::make_tuple(Q, R);
}

template <class T>
void QRsolveSLAE (const Matrix<T> &matrix, T approx) {
    std::cout << "Matrix A:\n" << matrix << "\nEpsilon = " << approx << "\n";
}

#endif