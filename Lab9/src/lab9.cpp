/*
 * Purpose for program: This program reads data into a struct.
 *
 * Programmer: Jacob Abel
 * Date: March 30, 2017
 *
 * Honor Code: I have neither given nor received any unauthorized assistance
 * with this program.
 */

#include "lab9.h"

void readData(std::string& inputFile, std::string& outputFile) {
    std::ifstream is(inputFile);
    std::ofstream os(outputFile);
    basicStruct arr[ARRSIZE];
    int i = 0;
    while (is >> arr[i].name >> arr[i].number);
    os     << std::setw(5) << "Index"       << std::setw(5) << "Name" \
           << std::setw(7) << "Number"      << std::endl;
    for (size_t i = 0; i < ARRSIZE; i++) {
        os << std::setw(5) << i             << std::setw(5) << arr[i].name \
           << std::setw(7) << arr[i].number << std::endl;
    }
}