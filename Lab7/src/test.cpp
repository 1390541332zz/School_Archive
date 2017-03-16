/*
 * Purpose for program: This program calls the readInt function.
 *
 * Programmer: Jacob Abel
 * Date: March 13, 2017
 *
 * Honor Code: I have neither given nor received any unauthorized assistance
 * with this program.
 */

#ifndef LAB7_H
#define LAB7_H
#include <iostream>
#include "lab7.h"

int main(int argc, char const *argv[]);

#endif /* LAB7_H */

int main(int argc, char const *argv[]) {
    if (argc < 3) {
        std::cerr << "ERROR: Missing Arguments!" << std::endl;
    } else if (argc > 3) {
        std::cerr << "ERROR: Unexpected Arguments!" << argc << std::endl;
    } else {
        return readInts(argv[1], argv[2]);
    }
}