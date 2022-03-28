#ifndef MATRIX_FUNC_HPP
#define MATRIX_FUNC_HPP

#include <tuple>
#include "Matrix.hpp"

enum Method {
    LU_METHOD
};

enum ReportRate {
    NONE,
    REPORT_LOW,
    REPORT_HIGH
};

template <class T>
std::tuple<Matrix<T>, Matrix<T>> LU (const Matrix<T> &m, ReportRate levelOfRep) {
    if (levelOfRep != NONE) {
        std::cout << "----CREATING LU DECOMPOSITION---\n";
    }
    if (!m.isSquare()) {
        return std::make_tuple(Matrix<T>(0), Matrix<T>(0));
    }
    uint64_t n = m.size().first;
    Matrix<T> L(n);
    Matrix<T> U(m);
    if (levelOfRep == REPORT_HIGH) {
        std::cout << "A = LU\nL = E\nU = A\n\nMatrix L:\n" << L << "\nMatrix U:\n" << U << "\nIteration 0:\n";
    }
    for(uint64_t i = 0; i < n; ++i) {
		for(uint64_t j = i; j < n; ++j) {
		    L(j, i) = U(j, i) / U(i, i);
            if (levelOfRep == REPORT_HIGH) {
                std::cout << "L(" << j << ", " << i << ") = U(" << j << ", " << i << ") / U(" << i << ", " << i << ") = " << L(j, i) << "\n";
            }
        }
    }
    for(uint64_t k = 1; k < n; ++k) {
        if (levelOfRep == REPORT_HIGH) {
            std::cout << "Iteration " << k << ":\n";
        }
		for(uint64_t i = k - 1; i < n; ++i) {
			for(uint64_t j = i; j < n; ++j) {
				L(j, i) = U(j, i) / U(i, i);
                if (levelOfRep == REPORT_HIGH) {
                    std::cout << "L(" << j << ", " << i << ") = U(" << j << ", " << i << ") / U(" << i << ", " << i << ") = " << L(j, i) << "\n";
                }
            }
        }

		for(uint64_t i = k; i < n; ++i) {
			for(uint64_t j = k - 1; j < n; ++j) {
				U(i, j) = U(i, j) - L(i, k - 1) * U(k - 1, j);
                if (levelOfRep == REPORT_HIGH) {
                    std::cout << "U(" << i << ", " << j << ") = U(" << i << ", " << j << ") - L(" << i << ", " << k - 1 << ") * U(" << k - 1 << ", " << j << ")" << "= " << U(i, j) << "\n";
                }
            }
        }
	}
    if (levelOfRep != NONE) {
        std::cout << "--------------DONE--------------\n";
    }
    return std::make_tuple(L, U);
}

template<class T>
std::vector<T> LUsolveSLAE (const Matrix<T> &m, std::vector<T> ans, ReportRate levelOfRep) {
    if (levelOfRep != NONE) {
        std::cout << "----------SOLVING SLAE----------\n";
            if (levelOfRep == REPORT_HIGH) {
            std::cout << "Ax = b\n\nMatrix A:\n" << m << "\nVector b:";
            for (uint64_t i = 0; i < ans.size(); ++i) {
                std::cout << " " << ans[i];
            }
            std::cout << "\n";
        }
    }
    if (!m.isSquare() || m.size().first != ans.size()) {
        if (levelOfRep != NONE) {
            std::cout << "Matrix is not square. Stop working.\n";
        }
        return std::vector<T>(0);
    }
    uint64_t n = m.size().first;
    std::vector<T> x(n, T(0)), y(n, T(0));
    Matrix<T> L, U;
    std::tie(L, U) = LU(m, levelOfRep);

    if (levelOfRep != NONE) {
        std::cout << "\nMatrix L:\n" << L << "\nMatrix U:\n" << U << "\n";
    }

    y[0] = ans[0];
    if (levelOfRep == REPORT_HIGH) {
        std::cout << "Solving system:\n" << "Ly = b\nUx = y\n\ny[0] = b[0] = " << ans[0] << "\n";
    }
    for (uint64_t i = 1; i < n; ++i) {
        y[i] = ans[i];
        if (levelOfRep == REPORT_HIGH) {
            std::cout << "y[" << i << "] = b[" << i << "]";
        }
        for (uint64_t j = 0; j < i; ++j) {
            y[i] -= y[j] * L(i, j);
            if (levelOfRep == REPORT_HIGH) {
                std::cout << " - y[" << j << "] * L(" << i << ", " << j << ")";
            }
        }
        if (levelOfRep == REPORT_HIGH) {
            std::cout << " = " << y[i] << "\n";
        }
    }

    if (levelOfRep != NONE) {
        std::cout << "\nVector y: ";
        for (uint64_t i = 0; i < y.size(); ++i) {
            std::cout << y[i] << " ";
        }
        std::cout << "\n";
    }

    x[n - 1] = y[n - 1] / U(n - 1, n - 1);
    if (levelOfRep == REPORT_HIGH) {
        std::cout << "\nx[" << n - 1 << "] = y[" << n - 1 << "] / U(" << n - 1 << ", " << n - 1 << ") = " << x[n - 1] << "\n";
    }
    for (uint64_t i = n - 2; i < n - 1; --i) {
        x[i] = y[i];
        if (levelOfRep == REPORT_HIGH) {
            std::cout << "x[" << i << "] = y[" << i << "] - (0";
        }
        for (uint64_t j = i + 1; j < n; ++j) {
            x[i] -= x[j] * U(i, j);
            if (levelOfRep == REPORT_HIGH) {
                std::cout << " + x[" << j << "] * U(" << i << ", " << j << ")";
            }
        }
        x[i] /= U(i, i);
        if (levelOfRep == REPORT_HIGH) {
            std::cout << ") / U(" << i << " ," << i << ") = " << x[i] << "\n";
        }
    }
    return x;
}

template<class T>
std::vector<T> solveSLAE (Method method, const Matrix<T> &matrix, std::vector<T> b, ReportRate levelOfRep) {
    switch (method) {
        case LU_METHOD:
            return LUsolveSLAE(matrix, b, levelOfRep);
        default:
            return std::vector<T>(0);
    }
}

#endif