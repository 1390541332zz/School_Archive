/*
 * Purpose for program: This program test the mailbox program.
 *
 * Programmer: Jacob Abel
 * Date: April 10, 2017
 *
 * Honor Code: I have neither given nor received any unauthorized assistance
 * with this program.
 */

#include "mailbox.h"
#include <gtest/gtest.h>

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}