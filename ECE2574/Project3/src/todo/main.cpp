#include <cstdlib>
#include <cctype>
#include <string>
#include <algorithm>
#include "todo.hpp"

int main(int argc, const char *argv[])
{
    if (argc < 2) {
        std::cerr << "Error: Not Enough Arguments!\n";
        return EXIT_FAILURE;
    }
    std::size_t cur_arg = 1;
    std::string faddr = DEFAULT_FADDR;
    if (std::string(argv[cur_arg]) == "-f") {
        cur_arg++;
        faddr = argv[cur_arg++];
    }
    if (cur_arg >= argc) {
        std::cerr << "Error: Not Enough Arguments!\n";
        return EXIT_FAILURE;
    }
    std::string cmd = argv[cur_arg++];
    std::string excess = "";
    while (cur_arg < argc) {
        excess += argv[cur_arg++];
        if (cur_arg < argc) excess += ' ';
    }
    excess.erase(std::remove(excess.begin(), excess.end(), '"'), excess.end());
    todo todo_list(faddr);
    if (cmd == "add") {
        if (excess.empty()) {
            std::cerr << "Error: Not Enough Arguments!\n";
            return EXIT_FAILURE;
        }
        todo_list.add(excess);
    } else if (cmd == "list") {
        if (!excess.empty()) {
            std::cerr << "Error: Too Many Arguments!\n";
            return EXIT_FAILURE;
        }
        todo_list.list_tasks();
    } else if (cmd == "do") {
        if (!std::all_of(excess.cbegin(), excess.cend(), ::isdigit)) {
            std::cerr << "Error: Expected Numerical Index!\n";
            return EXIT_FAILURE;
        }
        if(todo_list.mark_task(std::stoull(excess)) != EXIT_SUCCESS) {
            return EXIT_FAILURE;
        }
    } else {
        std::cerr << "Error: Invalid Command Parameters!\n";
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
