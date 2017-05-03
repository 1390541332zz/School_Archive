/*
 * Purpose for program: This program tests the ToDoList API.
 *
 * Programmer: Jacob Abel
 * Date: May 02, 2017
 *
 * Honor Code: I have neither given nor received any unauthorized assistance
 * with this program.
 */

#include "ToDoList.h"
#include <gtest/gtest.h>

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
