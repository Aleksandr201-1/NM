#include "7-1.hpp"

int main () {
    std::cout.precision(PRECISION);
    std::cout.setf(std::ios_base::fixed);

    std::vector<std::string> system;
    std::string str;
    double xh, yh;
    Task task;
    FunctionalTree check;//("uxx + sin(3.14 * x)", {"uxx", "ux", "u", "x"});
    //check.printTree();

    std::cout << "=====7.1=====\n";
    std::cout << "Введите начально-краевую задачу:\n";

    str = readLine();
    system.push_back(str);
    for (uint64_t i = 0; i < 4; ++i) {
        str = readLine();
        system.push_back(str);
    }
    for (uint64_t i = 0; i < system.size(); ++i) {
        std::cout << i << ": " << system[i] << "\n";
    }
    std::cout << "Введите размер шага для \"x\" и для \"y\":\n";
    std::cin >> xh >> yh;
    //std::cout << "Введите значение параметров \"a\" и \"c\":\n";
    //std::cin >> a >> c;
    std::cout << "Введите функцию для сравнения:\n";
    str = readLine();
    task = getTaskInfo(system);
    //std::vector<std::vector<double>> ans;//, mistake;

    auto ans1 = SolveIBVP(task, xh, yh, Method::YAKOBI);
    auto ans2 = SolveIBVP(task, xh, yh, Method::ZEIDEL);
    auto ans3 = SolveIBVP(task, xh, yh, Method::LIBMAN);
    //auto mistake = ans;
    double mistakeSum1 = 0, mistakeSum2 = 0, mistakeSum3 = 0;
    double X0 = task.X[0];
    check.reset(str, {"x", "y"});

    uint64_t xSize = uint64_t(task.X[1] / xh), tSize = uint64_t(task.Y[1] / yh);
    uint64_t S = xSize * tSize; //вычисляем площадь таблицы U
    std::cout << "Размер таблицы функции U: " << xSize << "x" << tSize << "\n";
    for (uint64_t i = 0; i < ans1.size(); ++i) {
        for (uint64_t j = 0; j < ans1[i].size(); ++j) {
            mistakeSum1 += std::abs(ans1[i][j] - check({X0 + j * xh, i * yh}));
            mistakeSum2 += std::abs(ans2[i][j] - check({X0 + j * xh, i * yh}));
            mistakeSum3 += std::abs(ans3[i][j] - check({X0 + j * xh, i * yh}));
        }
    }
    std::cout << "Средняя погрешность метода простых итераций: " << mistakeSum1 / S << "\n";
    std::cout << "Средняя погрешность метода Якоби: " << mistakeSum2 / S << "\n";
    std::cout << "Средняя погрешность метода Либмана: " << mistakeSum3 / S << "\n";

    double x, t;
    while (std::cin >> x >> t) {
        std::cout << "U(" << x << ", " << t << ") = " << check({x, t}) << "\n";
    }

    return 0;
}