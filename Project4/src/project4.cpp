/*
 * Purpose for program: This program executes the mailbox program.
 *
 * Programmer: Jacob Abel
 * Date: April 10, 2017
 *
 * Honor Code: I have neither given nor received any unauthorized assistance
 * with this program.
 */

#include <iostream>
#include "mailbox.h"

int main(int argc, char *argv[]) {
    if (argc < 3) {
        std::cerr << "ERROR: Missing Arguments!" << std::endl;
    } else if (argc > 3) {
        std::cerr << "ERROR: Unexpected Arguments!" << argc << std::endl;
    } else {
        return mailbox(argv[1], argv[2]);
    }
}
