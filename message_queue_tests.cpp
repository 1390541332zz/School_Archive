#include <thread>

#include "catch.hpp"

#include "message_queue.hpp"

TEST_CASE("Test basics", "[message_queue]")
{
    message_queue<std::string> q;

    auto p0 = [&q] () {
        for (auto x = 0; x < 110; x++) {
            q.push({1, "beep i made a " + std::to_string(x)});
        }
    };
    auto p1 = [&q] () {
        for (auto x = 107; x > 1; x--) {
            q.push({2, "boop i made a " + std::to_string(x)});
        }
    };
    auto c0 = [&q] () {
        for (auto x = 0; x < 110; x++) { 
            bool wait = true;
            message<std::string> m;
            while(!q.pop(1, m)) {}
        }
    };
    auto c1 = [&q] () {
        for (auto x = 107; x > 1; x--) {
            bool wait = true;
            message<std::string> m;
            while(!q.pop(2, m)) {}
            REQUIRE(m.item == ("boop i made a " + std::to_string(x)));
        }
    };


    std::thread t0(p0);
    std::thread t1(p1);
    std::thread t2(c0);
    std::thread t3(c1);


    t0.join();
    t1.join();
    t2.join();
    t3.join();
}
