/*
 * Purpose for program: This program executes the country info program.
 *
 * Programmer: Jacob Abel
 * Date: Febuary 20, 2017
 *
 * Honor Code: I have neither given nor received any unauthorized assistance
 * with this program.
 */

#include "project2.h"

int main(int argc, char const *argv[]) {
    if (argc < 3) {
        std::cerr << "ERROR: Missing Arguments!" << std::endl;
    } else if (argc > 3) {
        std::cerr << "ERROR: Unexpected Arguments!" << argc << std::endl;
    } else {
        return countryInfo(argv[1], argv[2]);
    }
}
