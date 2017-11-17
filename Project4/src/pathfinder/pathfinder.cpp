#include <cstdlib>
#include <string>
#include <iostream>

#include "deque.hpp"
#include "image.h"

static const int nav[4][2] = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};

class maze_solver {
private:
    struct point {
        std::size_t r = 0;
        std::size_t c = 0;
    };
    Image<Pixel> img;
    Image<Pixel> img_tmp;
    struct point start;
    Deque<struct point> unexplored;
    Deque<struct point> explored;

    bool is_solution(struct point pt) {
        return ((img(pt.r, pt.c) == WHITE) &&
                (  (pt.r == 0)
                || (pt.c == 0)
                || (pt.r == img.width()  - 1)
                || (pt.c == img.height() - 1)));
    }

    bool check_barrier() {
        bool exit_exists = false;
        for (size_t i = 0; i < img.width(); i++) {
            if (img(i, 0) == WHITE || img(i, img.height() - 1) == WHITE) {
                exit_exists = true;
                break;
            }
        }
        for (size_t i = 0; i < img.height(); i++) {
            if (exit_exists) break;
            if (img(0, i) == WHITE || img(img.width() - 1, i) == WHITE) {
                exit_exists = true;
                break;
            }
        }
        return exit_exists;
    }

    std::string solve()
    {
        if (!check_barrier()) return "No Solution Found";
        unexplored.pushFront(start);
        while (!unexplored.isEmpty()) {
            struct point cur = unexplored.back();
            unexplored.popBack();
            explored.pushFront(cur);
            img_tmp(cur.r, cur.c) = BLACK;
            if (is_solution(cur)) {
                img(cur.r, cur.c) = GREEN;
                return "Solution Found";
            }
            for (size_t i = 0; i < 4; i++) {
                struct point successor;
                successor.r = cur.r + nav[i][0];
                successor.c = cur.c + nav[i][1];
                if (img_tmp(successor.r, successor.c) != WHITE) continue;
                if (is_solution(successor)) {
                    img(successor.r, successor.c) = GREEN;
                    return "Solution Found";
                }
                unexplored.pushFront(successor);
                img_tmp(successor.r, successor.c) = BLUE;
            }
        }
        return "No Solution Found";
    }

public:
    maze_solver(const std::string& if_path) : img(readFromFile(if_path)),
                                              img_tmp(readFromFile(if_path))
    {
        bool start_found = false;
        for (size_t i = 0; i < img.width(); i++) {
            for (size_t j = 0; j < img.height(); j++) {
                Pixel p = img(i, j);
                if (p == RED && !start_found) {
                    start_found = true;
                    start.r = i; start.c = j;
                } else if (p == RED) {
                    throw std::runtime_error("More than one start pixel(RED)!");
                } else if (p == GREEN) {
                    throw std::runtime_error("Maze has already been solved!");
                } else if (p != WHITE && p != BLACK) {
                    throw std::runtime_error("Invalid pixel(Illegal Colours)!");
                }
            }
        }
    }

    ~maze_solver() {}

    void write(const std::string& of_path)
    {
        std::cout << solve() << std::endl;
        writeToFile(img, of_path);
    }
};

int main(int argc, const char *argv[])
{
    if (argc < 3) {
        std::cerr << "Error: Not Enough Arguments!\n";
        return EXIT_FAILURE;
    }
    if (argc > 3) {
        std::cerr << "Error: Too many Arguments!\n";
        return EXIT_FAILURE;
    }

    std::string if_path(argv[1]);
    std::string of_path(argv[2]);

    try {
        maze_solver maze(if_path);
        maze.write(of_path);
    } catch (const std::runtime_error& e) {
        std::cerr << "Error " << e.what();
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
