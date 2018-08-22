/*
 * Purpose for program: This program performs basic integer arithmetic such as
 * addition, subtraction, multiplication, division, and computing the remainder.
 *
 * Programmer: Jacob Abel
 * Date: Febuary 20, 2017
 *
 * Honor Code: I have neither given nor received any unauthorized assistance
 * with this program.
 */



#include "compute.h"

int compute(std::string inputFile, std::string outputFile) {
    std::ifstream input(inputFile);
    std::ofstream output(outputFile);

    std::string op = "";
    int n1 = 0;
    int n2 = 0;
    int result = 0;

    output << std::left    << std::setw(9) << "Operand1" << std::setw(10) \
           << "Operation"  << std::setw(9) << "Operand2" << std::setw(6) \
           << "Answer" << std::endl;

    while (input >> op >> n1 >> n2) {
        if (op == "add") {
            result = add(n1, n2);
            op = "+";
        } else if (op == "subtract") {
            result = subtract(n1, n2);
            op = "-";
        } else if (op == "multiply") {
            result = multiply(n1, n2);
            op = "*";
        }else if (op == "divide") {
            result = divide(n1, n2);
            op = "/";
        } else if (op == "remainder") {
            result = remainder(n1, n2);
            op = "%";
        } else {
            return -1;
        }

        output << std::left << std::setw(9) << n1 << std::setw(10) \
               << op        << std::setw(9) << n2 << std::setw(6) \
               << result    << std::endl;
    }

    input.close();
    output.close();
    return 0;
}

int add(int n1, int n2){
    return n1 + n2;
}

int subtract(int n1, int n2){
    return n1 - n2;
}

int multiply(int n1, int n2){
    return n1 * n2;
}

int divide(int n1, int n2){
    return n1 / n2;
}

int remainder(int n1, int n2){
    return n1 % n2;
}
