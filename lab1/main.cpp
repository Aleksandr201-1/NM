#include <iostream>
#include <fstream>
#include "MatrixFunc.hpp"

void usage () {
    std::cout << "Usage:\n\
--help, -h\t\t\tshow the usage\n\
--input, -i [X]\t\t\tuse file X with ready to use data (matrix and vector)\n\
--output, -o [X]\t\tuse file X for output\n\
--method, -m [ARG]\t\tuse method ARG for solution of SLAE\n\
\tLU - \t\t\tsolving SLAE with LU decomposition, finding det and reverse matrix\n\
\tRUN - \t\t\tsolving SLAE with RUN method\n\
\tSI_YAKOBI - \t\tSimple iteration (Yakobi)\n\
\tSI_ZEIDEL - \t\tSimple iteration (Zeidel)\n\
\tSPIN - \t\t\tfinding eigenvalues and eigenvectors with spin method\n\
\tQR - \t\t\tQR decomposition\n\
--precision, -p [N]\t\tcount of nums after point\n\
--iteration-limit, -il [N]\tset limit of iterations\n";
}

int main (int argc, char *argv[]) {
    std::string input, output;
    std::fstream output_file, input_file;
    Method method = LU_METHOD;
    for (uint64_t i = 1; i < argc; ++i) {
        std::string str(argv[i]);
        if (str == "--method" || str =="-m") {
            if (i + 1 >= argc) {
                usage();
                return 2;
            }
            std::string tmp(argv[i + 1]);
            if (tmp == "LU") {
                method = LU_METHOD;
            } else if (tmp == "RUN") {
                method = RUN_METHOD;
            } else if (tmp == "SI_YAKOBI") {
                method = SI_YAKOBI_METHOD;
            } else if (tmp == "SI_ZEIDEL") {
                method = SI_ZEIDEL_METHOD;
            } else if (tmp == "SPIN") {
                method = SPIN_METHOD;
            } else if (tmp == "QR") {
                method = QR_METHOD;
            }
            ++i;
        } else if (str == "--input" || str == "-i") {
            if (i + 1 >= argc) {
                usage();
                return 2;
            } else {
                input = argv[i + 1];
            }
            ++i;
        } else if (str == "--output" || str == "-o") {
            if (i + 1 >= argc) {
                usage();
                return 2;
            } else {
                output = argv[i + 1];
            }
            ++i;
        } else if (str == "--help" || str == "-h") {
            usage();
            return 0;
        } else if (str == "--precision" || str == "-p") {
            if (i + 1 >= argc) {
                usage();
                return 2;
            } else {
                PRECISION = std::stoi(argv[i + 1]);
            }
            ++i;
        } else if (str == "--iteration-limit" || str == "-il") {
            if (i + 1 >= argc) {
                usage();
                return 2;
            } else {
                ITERATION_LIMIT = std::stoi(argv[i + 1]);
            }
            ++i;
        } else {
            std::cout << "Unknown key \"" << argv[i] << "\"\n";
            usage();
            return 1;
        }
    }
    std::cout.precision(PRECISION);
    std::cout.setf(std::ios_base::fixed);

    if (input != "") {
        input_file.open(input, std::ios::in);
        std::cin.rdbuf(input_file.rdbuf());
    }
    if (output != "") {
        output_file.open(output, std::ios::out);
        std::cout.rdbuf(output_file.rdbuf());
    }

    uint64_t n = 0;
    std::cout << "Enter matrix size: ";
    std::cin >> n;
    std::cout << "\n";

    Matrix<long double> matrix(n, n);

    std::cout << "Enter matrix " << n << "x" << n << ":\n";
    std::cin >> matrix;
    solveSLAE(method, matrix);

    if (input != "") {
        input_file.close();
    }
    if (output != "") {
        output_file.close();
    }

    return 0;
}