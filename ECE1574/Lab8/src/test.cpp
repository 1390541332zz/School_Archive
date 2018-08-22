/*
 * Purpose for program: This program calls the read2D_Data function.
 *
 * Programmer: Jacob Abel
 * Date: March 20, 2017
 *
 * Honor Code: I have neither given nor received any unauthorized assistance
 * with this program.
 */

#ifndef LAB8_H
#define LAB8_H
#include <iostream>
#include "lab8.h"

int main(int argc, char const *argv[]);

#endif /* LAB8_H */

int main(int argc, char const *argv[]) {
    if (argc < 3) {
        std::cerr << "ERROR: Missing Arguments!" << std::endl;
    } else if (argc > 3) {
        std::cerr << "ERROR: Unexpected Arguments!" << argc << std::endl;
    } else {
        return read2D_Data(argv[1], argv[2]);
    }
}