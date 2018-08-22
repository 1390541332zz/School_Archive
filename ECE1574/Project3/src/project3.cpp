/*
 * Purpose for program: This program executes the map navigation program.
 *
 * Programmer: Jacob Abel
 * Date: March 23, 2017
 *
 * Honor Code: I have neither given nor received any unauthorized assistance
 * with this program.
 */

#include "project3.h"

int main(int argc, char *argv[]) {
    if (argc < 3) {
        std::cerr << "ERROR: Missing Arguments!" << std::endl;
    } else if (argc > 3) {
        std::cerr << "ERROR: Unexpected Arguments!" << argc << std::endl;
    } else {
        return mapWalk(argv[1], argv[2]);
    }
}
