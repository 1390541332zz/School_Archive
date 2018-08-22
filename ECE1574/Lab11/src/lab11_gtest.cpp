/*
 * Purpose for program: Google Unit Tests for lab9.cpp
 *
 * Programmer: Jacob Abel
 * Date: March 30, 2017
 *
 * Honor Code: I have neither given nor received any unauthorized assistance
 * with this program.
 */

#include "lab11.h"
#include <gtest/gtest.h>
#include <string>

int main(int argc, char *argv[]) {
 ::testing::InitGoogleTest(&argc, argv);
 return RUN_ALL_TESTS();
}

TEST(ReadData, Verify) {
    std::string in = "test/samples/test0.in";
    std::string out = "test/generated/test0.out";
    readDynamicData(in, out);
}