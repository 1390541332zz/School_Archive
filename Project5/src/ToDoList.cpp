/*
 * Purpose for program: This class is contains a list of todo objects.
 *
 * Programmer: Jacob Abel
 * Date: May 02, 2017
 *
 * Honor Code: I have neither given nor received any unauthorized assistance
 * with this program.
 */

#include "ToDoList.h"

// Default Constructor
ToDoList::ToDoList() {
}

// Destructor
ToDoList::~ToDoList() {
    delete [] arr;
    arr = nullptr;
    size = 0;
    qty = 0;
}

// Grows and shrinks the array as necessary
void ToDoList::regulateSize() {
    if (arr == nullptr) {
        arr = new ToDo [ARRSIZE];
        size = ARRSIZE;
    } else if (qty == size) {
        ToDo* tmp = arr;
        arr = new ToDo [size * SCALE];
        for (size_t i = 0; i < qty; i++) arr[i] = tmp[i];
        delete [] tmp;
        size *= SCALE;
    } else if ((qty > ARRSIZE) && (qty + MARGIN == size / SCALE)) {
        ToDo* tmp = arr;
        arr = new ToDo [size / SCALE];
        for (size_t i = 0; i < qty; i++) arr[i] = tmp[i];
        delete [] tmp;
        size /= SCALE;
    }
}

// Shifts the array values after index to the left or right.
void ToDoList::shift(size_t index, bool shiftRight) {
    if (index >= qty) return;
    if (shiftRight) {
        for (size_t i = qty; i > index; i--) arr[i] = arr[i - 1];
    } else {
        for (size_t i = index; i < qty - 1; i++) arr[i] = arr[i + 1];
    }
}

// Returns the quantity of ToDo objects
size_t ToDoList::getToDoCount() const {
    return qty;
}

// Returns the quantity of ToDo objects
size_t ToDoList::getSize() const {
    return size;
}
// Returns the ToDo at the index. If an invalid index is provided the 
// default ToDo is returned;
ToDo ToDoList::getToDo(int index) const {
    return (index >= 0 && static_cast<size_t>(index) < qty) ? arr[index] : ToDo();
}

// Removes the ToDo at the index.
ToDo ToDoList::removeToDo(int index) {
    if (index < 0 || static_cast<size_t>(index) >= qty) return ToDo();
    ToDo obj = arr[index];
    ToDoList::shift(index, false);
    qty--;
    ToDoList::regulateSize();
    return obj;
}

// Adds the ToDo obj to the end of the array.
void ToDoList::addToDo(ToDo obj) {
    ToDoList::regulateSize();
    arr[qty++] = obj;
}

// Adds the ToDo at the index provided. If below 0 it is at the front, If above
// the qty, it is added to the end.
void ToDoList::addToDo(ToDo obj, int index) {
    ToDoList::regulateSize();
    if (index < 0 || static_cast<size_t>(index) < qty) {
        if (index < 0) index = 0;
        ToDoList::shift(index, true);
        arr[index] = obj;
        qty++;
    } else {
        arr[qty++] = obj;
    }
}

// Displays the ToDoList
void ToDoList::printWhatIHaveToDo(std::ostream& os) const {
    std::ostringstream ss;
    ss << "Here's what I've got to do:" << std::endl;
    for (size_t i = 0; i < qty; i++) ss << arr[i] << std::endl;
    os << ss.str();
}

// Stream Insertion Operator
std::ostream& operator << (std::ostream& os, const ToDoList& obj) {
    obj.printWhatIHaveToDo(os);
    return os;
}

// Equality Operator
bool operator == (const ToDoList& o1, const ToDoList& o2) {
    bool state = (o1.getToDoCount() == o2.getToDoCount());
    if (o1.getToDoCount() == 0 || o2.getToDoCount() == 0) return state;
    for (size_t i = 0; i < o1.getToDoCount(); i++) state = state && (o1.getToDo(i) == o2.getToDo(i));
    return state;
}

// Inequality Operator
bool operator != (const ToDoList& o1, const ToDoList& o2) {
    return !(o1 == o2); 
}