/*
 * Purpose for program: This program reads data into a dynamically allocated 
 * array in a struct.
 *
 * Programmer: Jacob Abel
 * Date: April 12, 2017
 *
 * Honor Code: I have neither given nor received any unauthorized assistance
 * with this program.
 */

#include "lab11.h"

void readDynamicData(std::string inputFile, std::string outputFile) {
    std::ifstream is(inputFile);
    std::ofstream os(outputFile);
    arrStruct arrStr;
    int tmp = 0;

    while (is >> tmp) {
        if (arrStr.arr == nullptr) {
            arrStr.arr = new int[ARRSIZE * SCALE];
            *arrStr.arr = {0};
        } else if (arrStr.qty == arrStr.size) {
            int* tmpArr = new int[arrStr.size * SCALE];
            *tmpArr = {0};
            for (size_t i = 0; i < arrStr.qty; i++) tmpArr[i] = arrStr.arr[i];
            delete [] arrStr.arr;
            arrStr.arr = tmpArr;
            arrStr.size *= SCALE;
        }
        arrStr.arr[arrStr.qty++] = tmp;
    }
    
    os << "Size: "  << arrStr.size << std::endl;
    os << "Count: " << arrStr.qty  << std::endl;
    os << "Data:"   << std::endl;
    for (size_t i = 0; i < arrStr.qty; i++) os << arrStr.arr[i] << std::endl;
    is.close();
    os.close();
}