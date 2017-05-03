/*
 * Purpose for program: Google Unit Tests for Date.cpp
 *
 * Programmer: Jacob Abel
 * Date: May 02, 2017
 *
 * Honor Code: I have neither given nor received any unauthorized assistance
 * with this program.
 */

#include "Date.h"
#include <gtest/gtest.h>

TEST(Date, Content) {
    int year  = 1;
    int month = 2;
    int day   = 3;
    
    Date date1;
    Date date2(month, day, year);
    
    date1.setYear(year);
    date1.setMonth(month);
    date1.setDay(day);
    
    ASSERT_EQ(date1.getYear(), date2.getYear());
    ASSERT_EQ(date1.getMonth(), date2.getMonth());
    ASSERT_EQ(date1.getDay(), date2.getDay());
    ASSERT_TRUE(date1 == date2);
    ASSERT_FALSE(date1 != date2);
}

TEST(Date, StreamOperator) {
    int year  = 1;
    int month = 2;
    int day   = 3;
    Date date(month, day, year);
    std::string str = "02/03/0001";
    std::ostringstream ss;
    ss << date;
    ASSERT_EQ(str, ss.str());
}