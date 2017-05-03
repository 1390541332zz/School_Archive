/*
 * Purpose for program: Google Unit Tests for ToDo.cpp
 *
 * Programmer: Jacob Abel
 * Date: May 02, 2017
 *
 * Honor Code: I have neither given nor received any unauthorized assistance
 * with this program.
 */

#include "ToDo.h"
#include <gtest/gtest.h>

TEST(ToDo, Content) {
    std::string cat = "category";
    std::string title = "Title";
    std::string desc = "description";
    Date date(3, 2, 1);
    ToDo item1;
    ToDo item2(cat, title, date, desc);
    item1.setCategory(cat);
    item1.setTitle(title);
    item1.setDueDate(date);
    item1.setDescription(desc);
    
    ASSERT_EQ(item1.getCategory(), item2.getCategory());
    ASSERT_EQ(item1.getTitle(), item2.getTitle());
    ASSERT_EQ(item1.getDueDate(), item2.getDueDate());
    ASSERT_EQ(item1.getDescription(), item2.getDescription());
    
    ASSERT_TRUE(item1 == item2);
    ASSERT_FALSE(item1 != item2);
}

TEST(ToDo, StreamOperator) {
    
}