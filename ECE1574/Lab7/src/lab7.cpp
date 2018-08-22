/*
 * Purpose for program: This program reads values into an array and prints the
 * array to a file.
 *
 * Programmer: Jacob Abel
 * Date: March 13, 2017
 *
 * Honor Code: I have neither given nor received any unauthorized assistance
 * with this program.
 */

#include "lab7.h"

int readInts(std::string inputFile, std::string outputFile) {
    std::ifstream is(inputFile);
    std::ofstream os(outputFile);
    int arr[ARRSIZE];
    int i = 0;
    
    while(i < ARRSIZE && is >> arr[i]) {
        i++;
    }
    
    os << std::left;
    os << std::setw(6) << "Index" << std::setw(9) << "Value" << std::endl;
    for (size_t i = 0; i < ARRSIZE; i++) {
        os << std::setw(6) << i << std::setw(9) << arr[i] << std::endl;
    }
    
    is.close();
    os.close();
    return 0;
}