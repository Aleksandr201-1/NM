#include "gnuplot-iostream.h"
#include "5-1.hpp"

void plot (const std::vector<std::string> &func, double a, double b) {
    static std::vector<std::string> colors = {"red", "green", "blue"};
    Gnuplot gp;

    gp << "set xlabel \"X\"\n";
    gp << "set ylabel \"Y\"\n";
    gp << "set xzeroaxis lw 1\n";
    gp << "set yzeroaxis lw 1\n";
    gp << "set xrange[" << a << ":" << b << "]\n";
    gp << "set grid\n";
    gp << "set title \"Plot\" font \"Helvetica Bold, 20\"\n";
    
    gp << "plot ";
    for (uint64_t i = 0; i < func.size(); ++i) {
        gp << func[i] << " title \"";
        gp << (i == 0 ? "our func" : "real func");
        gp << "\"  lc rgb \"" << colors[i % colors.size()] << "\"";
        if (i == func.size() - 1) {
            gp << "\n";
        } else {
            gp << ",";
        }
    }
}

int main () {
    std::cout.precision(PRECISION);
    std::cout.setf(std::ios_base::fixed);

    std::vector<std::string> system;
    std::string str;
    double xh, th;
    std::pair<std::vector<double>, std::vector<double>> res1, res2;
    Task task;
    FunctionalTree check;//("uxx + sin(3.14 * x)", {"uxx", "ux", "u", "x"});
    //check.printTree();

    std::cout << "=====5.1=====\n";
    std::cout << "Введите начально-краевую задачу:\n";

    str = readLine();
    system.push_back(str);
    for (uint64_t i = 0; i < 3; ++i) {
        str = readLine();
        system.push_back(str);
    }
    for (uint64_t i = 0; i < system.size(); ++i) {
        std::cout << i << ": " << system[i] << "\n";
    }
    std::cout << "Введите размер шага для \"x\" и для \"t\":\n";
    std::cin >> xh >> th;
    //std::cout << "Введите значение параметров \"a\" и \"c\":\n";
    //std::cin >> a >> c;
    std::cout << "Введите функцию для сравнения:\n";
    str = readLine();
    task = getTaskInfo(system);
    //std::vector<std::vector<double>> ans;//, mistake;

    auto ans1 = SolveIBVP(task, xh, th, Method::EXPLICIT);
    auto ans2 = SolveIBVP(task, xh, th, Method::NOT_EXPLICIT);
    auto ans3 = SolveIBVP(task, xh, th, Method::KRANK_NICOLAS);
    //auto mistake = ans;
    double mistakeSum1 = 0, mistakeSum2 = 0, mistakeSum3 = 0;
    double X0 = task.X[0];
    check.reset(str, {"x", "t"});
    for (uint64_t i = 0; i < ans1.size(); ++i) {
        for (uint64_t j = 0; j < ans1[i].size(); ++j) {
            //mistake[i][j] = std::abs(ans[i][j] - check({j *xh, i * th}));
            //mistakeSum += mistake[i][j];
            mistakeSum1 += std::abs(ans1[i][j] - check({X0 + j * xh, i * th}));
            mistakeSum2 += std::abs(ans2[i][j] - check({X0 + j * xh, i * th}));
            mistakeSum3 += std::abs(ans3[i][j] - check({X0 + j * xh, i * th}));
        }
    }
    // std::cout << "Наша функция:\n";
    // for (uint64_t i = 0; i < ans.size(); ++i) {
    //     printVector(ans[i]);
    // }
    std::cout << "\nПогрешность\n";
    // for (uint64_t i = 0; i < mistake.size(); ++i) {
    //     printVector(mistake[i]);
    // }
    std::cout << "Сумма погрешностей 1: " << mistakeSum1 << "\n";
    std::cout << "Сумма погрешностей 2: " << mistakeSum2 << "\n";
    std::cout << "Сумма погрешностей 3: " << mistakeSum3 << "\n";

    double x, t;
    while (std::cin >> x >> t) {
        std::cout << "U(" << x << ", " << t << ") = " << check({x, t}) << "\n";
    }

    return 0;
}