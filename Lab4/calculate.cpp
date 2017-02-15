/*
 * Purpose for program: This program provides a function for performing
 * trigonometric operations on data.
 *
 * Programmer: Jacob Abel
 * Date: Febuary 13, 2017
 *
 * Honor Code: I have neither given nor received any unauthorized assistance
 * with this program.
 */

#include "calculate.h"

int calculate(std::string fileIn, std::string fileOut) {
    std::ifstream input(fileIn);
    std::ofstream output(fileOut);

    std::string op;
    int degrees;
    double radians;
    double solution;

    output << std::left     << std::setw(14) << "Operation" \
           << std::setw(10) << "Angle"       << "Answer"    << std::endl;

    while (input >> op >> degrees) {
        radians = degrees * M_PI / 180;
        if(op == "sin") {
            solution = sin(radians);
        } else if (op == "cos") {
            solution = cos(radians);
        } else if (op == "tan") {
            solution = tan(radians);
        } else {
            return -1;
        }
        output << std::left << std::setw(14) << op << std::setw(10) << degrees \
               << std::fixed << std::setprecision(10) << solution << std::endl;
    }

    input.close();
    output.close();

    return 0;
}
