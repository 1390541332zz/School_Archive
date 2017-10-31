#include "todo.hpp"

todo::todo(std::string storage_file)
         : fs(storage_file),
           faddr(storage_file)
{
    struct todo_item item = {};
    while (fs >> item.pending) {
        fs.ignore(std::numeric_limits<std::streamsize>::max(), ':');
        std::getline(fs, item.str);
        list.insert(list.getLength(), item);
    }
}

todo::~todo()
{
    if (fs.is_open()) fs.close();
    fs.open(faddr, std::fstream::out | std::fstream::trunc);
    for (std::size_t i = 0; i < list.getLength(); i++) {
        struct todo_item item = list.getEntry(i);
        fs << item.pending << " :" << item.str << '\n';
    }
    fs.close();
}

void todo::add(const std::string& task)
{
    struct todo_item item;
    item.str = task;
    item.pending = true;
    list.insert(list.getLength(), item);
}

void todo::list_tasks(std::ostream& os) const
{
    for (std::size_t i = 0; i < list.getLength(); i++) {
        os << (i + 1) << ':' << list.getEntry(i);
    }
}

int todo::mark_task(std::size_t i) noexcept
{
    i--;
    if (i >= list.getLength()) {
        std::cerr << "Error: Attempted to mark non-existant task!\n";
        return EXIT_FAILURE;
    }
    struct todo_item item = list.getEntry(i);
    list.remove(i);
    item.pending = false;
    list.insert(list.getLength(), item);
    return EXIT_SUCCESS;
}

std::ostream& operator<<(std::ostream& os, const todo_item& obj)
{
    os << '[' << (obj.pending ? ' ' : 'x') << ']' << ' ' << obj.str << '\n';
    return os;
}
