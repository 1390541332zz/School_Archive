#ifndef PROJECT5_TODOLIST_H
#define PROJECT5_TODOLIST_H

#include "ToDo.h"
#include "Date.h"
#include <iostream>
#include <sstream>
#include <cstddef>

#define ARRSIZE 10
#define SCALE 2
#define MARGIN 5

class ToDoList {
    private:
        size_t qty  = 0;
        size_t size = 0;
        ToDo* arr   = nullptr;
        
        void regulateSize();
        void shift(size_t index, bool shiftRight);
    public:
        ToDoList();
        ~ToDoList();
        size_t getToDoCount() const;
        size_t getSize() const;
        ToDo getToDo(int index) const;
        ToDo removeToDo(int index);
        void addToDo(ToDo obj);
        void addToDo(ToDo obj, int index);
        void printWhatIHaveToDo(std::ostream& os) const;
};

std::ostream& operator << (std::ostream& os, const ToDoList& obj);

#endif /* PROJECT5_TODOLIST_H */