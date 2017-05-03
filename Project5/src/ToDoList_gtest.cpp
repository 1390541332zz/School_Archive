/*
 * Purpose for program: Google Unit Tests for ToDoList.cpp
 *
 * Programmer: Jacob Abel
 * Date: May 02, 2017
 *
 * Honor Code: I have neither given nor received any unauthorized assistance
 * with this program.
 */

#include "ToDoList.h"
#include <gtest/gtest.h>

TEST(ToDoList, Content) {
    std::string cat = "category";
    std::string title = "Title";
    std::string desc = "description";
    Date date(3, 2, 1);
    ToDo item(cat, title, date, desc);
    ToDoList list();
}

TEST(ToDoList, StreamOperator) {
    
}

TEST(ToDoList, DynamicArray) {    
    std::string cat = "category";
    std::string title = "Title";
    std::string desc = "description";
    Date date(3, 2, 1);
    ToDo item(cat, title, date, desc);
    ToDoList list;
    size_t qty = 0;
    for (size_t i = 0; i < ARRSIZE; i++) {
        list.addToDo(item);
        ASSERT_EQ(list.getToDoCount(), ++qty);
    }
    for (size_t i = qty - 1; i > 0; i--) {
        list.removeToDo(i);
        ASSERT_EQ(list.getToDoCount(), --qty);
    }
    for (size_t i = 0; i < ARRSIZE * 50; i++) {
        list.addToDo(item);
        ASSERT_EQ(list.getToDoCount(), ++qty);
    }
    for (size_t i = qty - 1; i > 0; i--) {
        list.removeToDo(i);
        ASSERT_EQ(list.getToDoCount(), --qty);
    }
    
}