#ifndef LAB9_H
#define LAB9_H

#include <string>
#include <fstream>
#include <iomanip>

#define ARRSIZE 5
#define SCALE 2

typedef struct {
    size_t qty = 0;
    size_t size = ARRSIZE;
    int* arr = nullptr;
} arrStruct;

void readDynamicData(std::string inputFile, std::string outputFile);

#endif /* LAB9_H */