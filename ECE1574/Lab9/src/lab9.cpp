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

void readData(std::string inputFile, std::string outputFile) {
    std::ifstream is(inputFile);
    std::ofstream os(outputFile);
    basicStruct arr[ARRSIZE];
    int i = 0;
    while (i < ARRSIZE && is >> arr[i].name >> arr[i].number) i++;
    os     << std::left;
    os     << std::setw(6) << "Index"       << std::setw(10) << "Name" \
           << std::setw(7) << "Number"      << std::endl;
    for (size_t i = 0; i < ARRSIZE; i++) {
        os << std::setw(6) << i             << std::setw(10) << arr[i].name \
           << std::setw(7) << arr[i].number << std::endl;
    }
    is.close();
    os.close();
}