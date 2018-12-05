#include <thread>

#include "catch.hpp"

#include "message_queue.hpp"

TEST_CASE("Test basics", "[message_queue]")
{
//    message_queue<std::string> q;
//    message_queue<std::string> q2;
//    bool done = false;
//
//    auto p0 = [&q] () {
//        for (auto x = 0; x < 1010; x++) {
//            q.push({1, "beep i made a " + std::to_string(x)});
//        }
//    };
//    auto p1 = [&q] () {
//        for (auto x = 1007; x > 1; x--) {
//            q.push({2, "boop i made a " + std::to_string(x)});
//        }
//    };
//    auto p2 = [&q] () {
//        for (auto x = 1400; x > 1; x--) {
//            q.push({3, "bloop i made a " + std::to_string(x)});
//        }
//    };
//    auto p3 = [&q] () {
//        for (auto x = 0; x < 1013; x++) {
//            q.push({4, "bleep i made a " + std::to_string(x)});
//        }
//    };
//    auto cp = [&q, &q2, &done] () {
//        while (!done) {
//            message<std::string> m1, m2;
//            bool w1 = q.pop(3, m1);
//            bool w2 = q.pop(4, m2);
//            if (w1) {
//                q2.push(m1);
//            }
//            if (w2) {
//                q2.push(m2);
//            }
//        }
//    };
//    auto c0 = [&q] () {
//        for (auto x = 0; x < 1010; x++) { 
//            bool wait = true;
//            message<std::string> m;
//            while(!q.pop(1, m)) {}
//        }
//    };
//    auto c1 = [&q] () {
//        for (auto x = 1007; x > 1; x--) {
//            bool wait = true;
//            message<std::string> m;
//            while(!q.pop(2, m)) {}
//        }
//    };
//    auto c2 = [&q2] () {
//        for (auto x = 1400; x > 1; x--) {
//            bool wait = true;
//            message<std::string> m;
//            while(!q2.pop(3, m)) {}
//            REQUIRE(m.id == 3);
//            REQUIRE(m.item == ("bloop i made a " + std::to_string(x)));
//        }
//    };
//    auto c3 = [&q2] () {
//        for (auto x = 0; x < 1013; x++) { 
//            bool wait = true;
//            message<std::string> m;
//            while(!q2.pop(4, m)) {}
//        }
//    };
//
//
//    std::thread t0(p0);
//    std::thread t1(p1);
//    std::thread t2(p2);
//    std::thread t3(p3);
//    std::thread t4(cp);
//    std::thread t5(c0);
//    std::thread t6(c1);
//    std::thread t7(c2);
//    std::thread t8(c3);
//
//
//    t0.join();
//    t1.join();
//    t2.join();
//    t3.join();
//    t5.join();
//    t6.join();
//    t7.join();
//    t8.join();
//    done = true;
//    t4.join();
}
