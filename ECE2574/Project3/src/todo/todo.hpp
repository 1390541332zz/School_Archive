#ifndef TODO_H
#define TODO_H

#include <cstdint>
#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <limits>

#include "linked_list.hpp"

#define DEFAULT_FADDR "./todo.txt"

struct todo_item {
    std::string str = "";
    bool pending = true;
};

class todo {
private:
    std::fstream fs;
    std::string faddr;
    LinkedList<struct todo_item> list = {};
public:
    todo(std::string storage_file = DEFAULT_FADDR);
    ~todo();

    void add(const std::string& task);
    void list_tasks(std::ostream& os = std::cout) const;
    int mark_task(std::size_t i) noexcept;
};

std::ostream& operator<<(std::ostream& os, const todo_item& obj);

#endif /* TODO_H */
