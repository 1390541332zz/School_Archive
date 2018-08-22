#ifndef LAB9_H
#define LAB9_H

#include <string>
#include <fstream>
#include <iomanip>

#define ARRSIZE 10

typedef struct {
    std::string name;
    double number;
} basicStruct;

void readData(std::string inputFile, std::string outputFile);

#endif /* LAB9_H */