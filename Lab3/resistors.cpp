/*
 * Purpose for program: This program provides a function for calculating the
 * resistance of a circuit.
 *
 * Programmer: Jacob Abel
 * Date: Febuary 6, 2017
 *
 * Honor Code: I have neither given nor received any unauthorized assistance
 * with this program.
 */

#include "resistors.h"

using std::endl;
using std::ifstream;
using std::ofstream;
using std::string;

int computeResistance() {
    ifstream input("input.txt");
    ofstream output("output.txt");
    double r1 = 0;
    double r2 = 0;
    double r3 = 0;

    input >> r1 >> r2 >> r3;
    while (!input.fail()) {
        if (r1 && r2 && r3) {
            output << 1/(1/r1 + 1/r2 + 1/r3) << endl;
        } else {
            output << "--error--" << endl;
        }
        input >> r1 >> r2 >> r3;
    }

    input.close();
    output.close();

    return 0;
}
