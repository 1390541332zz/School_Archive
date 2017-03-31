/*
 * Purpose for program: Google Unit Tests for lab9.cpp
 *
 * Programmer: Jacob Abel
 * Date: March 30, 2017
 *
 * Honor Code: I have neither given nor received any unauthorized assistance
 * with this program.
 */

#include "lab9.h"
#include <gtest/gtest.h>

int main(int argc, char *argv[]) {
 ::testing::InitGoogleTest(&argc, argv);
 return RUN_ALL_TESTS();
}

TEST(BasicStruct, VerifyContent) {
    std::srand(std::time(0));
    basicStruct basic;
    double num = static_cast<double>(std::rand()) / RAND_MAX;
    std::string name = "This title is not random because I am lazy.";
    
    basic.name = name;
    basic.number = num;
    
    ASSERT_TRUE(basic.name == name);
    ASSERT_EQ(basic.number, num);
}

TEST(ReadData, Verify) {
    
}