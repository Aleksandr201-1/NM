#ifndef A_HPP
#define A_HPP

#include "General.hpp"
#include "RUN.hpp"

enum class Method {
    EXPLICIT,
    NOT_EXPLICIT,
    KRANK_NICOLAS
};

enum class ApproxLevel {
    POINT2_ORDER1,
    POINT3_ORDER2,
    POINT2_ORDER2
};

std::vector<std::vector<double>> SolveIBVP (const Task &task, double xh, double th, Method method);

#endif