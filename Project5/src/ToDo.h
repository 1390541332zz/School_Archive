#ifndef PROJECT5_TODO_H
#define PROJECT5_TODO_H

#include "Date.h"
#include <string>
#include <iostream>

class ToDo {
    private:
        std::string category = "";
        std::string title = "";
        std::string description = "";
        Date due;
    public:
        ToDo();
        ToDo(std::string category, std::string title, Date dueDate, std::string description);
        std::string getCategory() const;
        std::string getTitle() const;
        std::string getDescription() const;
        Date getDueDate() const;
        void setCategory(std::string str);
        void setTitle(std::string str);
        void setDescription(std::string str);
        void setDueDate(Date dueDate);
        void printToDo(std::ostream& os) const;
};

std::ostream& operator << (std::ostream& os, const ToDo& obj);
bool operator == (const ToDo& o1, const ToDo& o2);
bool operator != (const ToDo& o1, const ToDo& o2);

#endif /* PROJECT5_TODO_H */