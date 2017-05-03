/*
 * Purpose for program: This class is contains a todo object.
 *
 * Programmer: Jacob Abel
 * Date: May 02, 2017
 *
 * Honor Code: I have neither given nor received any unauthorized assistance
 * with this program.
 */

#include "ToDo.h"

// Default Constructor
ToDo::ToDo(){
}

// Constructor with parameters
ToDo::ToDo(std::string categoryVal, std::string titleVal, Date dueDate, std::string descriptionVal)
:   category(categoryVal),
    title(titleVal),
    description(descriptionVal),
    due(dueDate)
{}

// Returns the category
std::string ToDo::getCategory() const {
    return category;
}

// Returns the title
std::string ToDo::getTitle() const {
    return title;
}

// Returns the description
std::string ToDo::getDescription() const {
    return description;
}

// Returns the due date
Date ToDo::getDueDate() const {
    return due;
}

// Sets the category
void ToDo::setCategory(std::string str) {
    category = str;
}

// Sets the title
void ToDo::setTitle(std::string str) {
    title = str;
}

// Sets the description
void ToDo::setDescription(std::string str) {
    description = str;
}

// Sets the due date
void ToDo::setDueDate(Date dueDate) {
    due = dueDate;
}

// Prints the ToDo object
void ToDo::printToDo(std::ostream& os) const {
    std::ostringstream ss;
    ss << std::left;
    ss << std::setw(15) << "Category:"    << std::setw(0) << category    << std::endl;
    ss << std::setw(15) << "Title:"       << std::setw(0) << title       << std::endl;
    ss << std::setw(15) << "Due Date:"    << std::setw(0) << due         << std::endl;
    ss << std::setw(15) << "Description:" << std::setw(0) << description << std::endl;
    os << ss.str();
}

// Stream Insertion Operator
std::ostream& operator << (std::ostream& os, const ToDo& obj) {
    obj.printToDo(os);
    return os;
}

// Equality Operator
bool operator == (const ToDo& o1, const ToDo& o2) {
    return ((o1.getCategory()    == o2.getCategory()) && \
            (o1.getTitle()       == o2.getTitle())    && \
            (o1.getDueDate()     == o2.getDueDate())  && \
            (o1.getDescription() == o2.getDescription()));
}

// Inequality Operator
bool operator != (const ToDo& o1, const ToDo& o2) {
    return !(o1 == o2); 
}