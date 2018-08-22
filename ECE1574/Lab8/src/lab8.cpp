/*
 * Purpose for program: This program reads values into an array and prints the
 * values at coordinates in the array.
 *
 * Programmer: Jacob Abel
 * Date: March 20, 2017
 *
 * Honor Code: I have neither given nor received any unauthorized assistance
 * with this program.
 */

#include "lab8.h"

int read2D_Data(std::string inputFile, std::string outputFile) {
    std::ifstream cmds(inputFile);
    std::ofstream os(outputFile);
    std::string cmd, mapFile;
    int argA;
    int argB;
    char map[ROW][COL] = {0};

    if (cmds >> mapFile && mapFile == "load") {
        cmds >> mapFile;
    } else {
        std::cerr << "ERROR: Missing Data File!" << std::endl;
        cmds.close();
        os.close();
        return -1;
    }

    std::ifstream is(mapFile);
    for (size_t i = 0; i < ROW; i++) {
        for (size_t j = 0; j < COL; j++) {
            is >> map[i][j];
        }
    }
    is.close();

    while (cmds >> cmd >> argA >> argB) {
        os << std::right;
        os << std::setw(3) << argA << ',' \
           << std::setw(3) << argB << ':' << ' ';
        if (argA >= 0 && argA < ROW && argB >= 0 && argB < COL) {
            os << std::left << map[argA][argB] << std::endl;
        } else {
            os << std::left << "bad location" << std::endl;
        }
    }

    cmds.close();
    os.close();
    return 0;
}