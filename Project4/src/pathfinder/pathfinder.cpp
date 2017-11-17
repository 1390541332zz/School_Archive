#include <cstdlib>
#include <string>
#include <iostream>

#include "deque.hpp"
#include "image.h"

static const int nav[4][2] = {{0, 1}, {0, -1}, {-1, 0}, {1, 0}};

class maze_solver {
private:
    struct point {
        struct Pixel p = BLUE;
        std::size_t x = 0;
        std::size_t y = 0;
    };
    Image<Pixel> img;
    struct point start;
    Deque<struct point> unexplored;
    Deque<struct point> explored;

    bool is_solution(struct point pt) {
        return ((img(pt.x, pt.y) == WHITE) &&
                (  (pt.x == 0)
                || (pt.y == 0)
                || (pt.x == img.width()  - 1)
                || (pt.y == img.height() - 1)));
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
        std::size_t cnt = 0;
        while (!unexplored.isEmpty()) {
            struct point cur = unexplored.back();
            unexplored.popBack();
            if (is_solution(cur)) {
                img(cur.x, cur.y) = GREEN;
                return "Solution Found";
            }
            bool used[4] = {0};
            auto cmp = [&used, &cur](const struct point& x) {
                for (size_t i = 0; i < 4; i++) {
                    used[i] = (used[i])
                           || (   (cur.x + nav[i][0] == x.x)
                               && (cur.y + nav[i][1] == x.y));
                }
            };
            explored.pushFront(cur);
            explored.for_each(cmp);
            unexplored.for_each(cmp);
            for (size_t i = 0; i < 4; i++) {
                struct point successor;
                successor.x = cur.x + nav[i][0];
                successor.y = cur.y + nav[i][1];
                successor.p = img(successor.x, successor.y);
                if (++cnt % 1000 == 0) std::cout << cnt << std::endl;
                if (successor.p == BLACK) continue;
                if (used[i]) continue;
                if (is_solution(successor)) {
                    img(successor.x, successor.y) = GREEN;
                    return "Solution Found";
                }
                unexplored.pushFront(successor);
            }
        }
        return "No Solution Found";
    }

public:
    maze_solver(const std::string& if_path) : img(readFromFile(if_path))
    {
        bool start_found = false;
        for (size_t i = 0; i < img.width(); i++) {
            for (size_t j = 0; j < img.height(); j++) {
                Pixel p = img(i, j);
                if (p == RED && !start_found) {
                    start_found = true;
                    start.p = p; start.x = i; start.y = j;
                } else if (p == RED) {
                    throw std::runtime_error("More than one start pixel(RED)!");
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
        std::cerr << "Error: " << e.what();
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
