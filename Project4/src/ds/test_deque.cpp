#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "deque.hpp"

#define TEST_WIDTH 4

auto validate = [](Deque<int>& d) {
    for (size_t i = 1; i <= TEST_WIDTH; i++) {
        REQUIRE_NOTHROW(d.back());
        REQUIRE(d.back() == i);
        d.popBack();
    }
    REQUIRE_THROWS(d.front());
    REQUIRE_THROWS(d.back());
};

TEST_CASE("Basic Functionality", "[Deque]")
{
    Deque<int> d;

    SECTION("Default Empty Deque")
    {
        REQUIRE(d.isEmpty());

        REQUIRE_THROWS(d.popFront());
        REQUIRE_THROWS(d.popBack());
        REQUIRE_THROWS(d.front());
        REQUIRE_THROWS(d.back());
    }
    SECTION("Deque Operations")
    {
        for (size_t i = 1; i <= TEST_WIDTH; i++) {
            d.pushFront(i);
        }

        SECTION("Unrolling Stack")
        {
            for (size_t i = TEST_WIDTH; i > 0; i--) {
                REQUIRE_NOTHROW(d.front());
                REQUIRE(d.front() == i);
                d.popFront();
            }
            REQUIRE_THROWS(d.front());
            REQUIRE_THROWS(d.back());
        }
        SECTION("Unrolling Queue")
        {
            validate(d);
        }
        SECTION("Constructors")
        {
            Deque<int> d_c(d);
            validate(d_c);
            Deque<int> d_m(std::move(d));
            validate(d_m);
            REQUIRE(d.isEmpty());
            Deque<int> d_cp(d);
            REQUIRE(d_cp.isEmpty());
            for (size_t i = TEST_WIDTH; i > 0; i--) {
                d.pushBack(i);
            }
            validate(d);
        }
        SECTION("Assignment Operators")
        {
            Deque<int> d_c = d;
            validate(d_c);

            Deque<int> d_m = std::move(d);
            validate(d_m);
            REQUIRE(d.isEmpty());
            for (size_t i = 1; i <= TEST_WIDTH; i++) {
                d.pushFront(i);
            }
            validate(d);
        }
    }
}

TEST_CASE("Reverse Operators", "[Deque]")
{
    Deque<int> d;
    for (size_t i = 1; i <= TEST_WIDTH; i++) {
        d.pushBack(i);
    }
    for (size_t i = 1; i <= TEST_WIDTH; i++) {
        REQUIRE_NOTHROW(d.front());
        REQUIRE(d.front() == i);
        d.popFront();
    }
    REQUIRE_THROWS(d.front());
    REQUIRE_THROWS(d.back());

}
