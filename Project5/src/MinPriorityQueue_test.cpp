#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "MinPriorityQueue.hpp"
#include <cstdlib>
#include <cmath>

#define TEST_QTY 100

TEST_CASE("Basic Operations", "[MinPriorityQueue]")
{
    MinPriorityQueue<std::size_t, std::size_t> q;

    SECTION("Initial State", "[MinPriorityQueue]")
    {
        REQUIRE(q.size() == 0);
        REQUIRE(q.height() == 0);
        REQUIRE(q.isEmpty());
        REQUIRE_THROWS(q.getMinItem());
        REQUIRE_THROWS(q.getMinValue());
        REQUIRE_THROWS(q.deleteMin());
    }
    SECTION("Modification", "[MinPriorityQueue]")
    {
        for (std::size_t i = TEST_QTY; i > 0; i--) {
            REQUIRE(q.insert(i, i));
            REQUIRE_NOTHROW(q.getMinItem());
            REQUIRE_NOTHROW(q.getMinValue());
            REQUIRE(q.getMinItem() == i);
            REQUIRE(q.getMinValue() == i);
            REQUIRE(q.size() == TEST_QTY - i + 1);
            REQUIRE(q.height() != 0);
        }
        q.printTree();
        for (std::size_t i = TEST_QTY; i > 0; i--) {
            REQUIRE_NOTHROW(q.getMinItem());
            REQUIRE_NOTHROW(q.getMinValue());
            REQUIRE(q.size() == i);
            REQUIRE(q.height() != 0);
            REQUIRE_NOTHROW(q.deleteMin());
        }
    }

    SECTION("Manual Rebalance", "[MinPriorityQueue]")
    {
        q.setAutoRebalance(false);
        for (std::size_t i = TEST_QTY; i > 0; i--) {
            std::size_t r = (rand() % TEST_QTY) + 1;
            REQUIRE(q.insert(r, r));
            REQUIRE_NOTHROW(q.getMinItem());
            REQUIRE_NOTHROW(q.getMinValue());
            REQUIRE(q.size() == TEST_QTY - i + 1);
            REQUIRE(q.height() != 0);
        }
        q.printTree();
        REQUIRE(q.rebalance(std::ceil(std::log2(q.size()))));
        REQUIRE_FALSE(q.rebalance(std::ceil(std::log2(q.size()))-1));
        for (std::size_t i = TEST_QTY; i > 0; i--) {
            REQUIRE_NOTHROW(q.getMinItem());
            REQUIRE_NOTHROW(q.getMinValue());
            REQUIRE(q.size() == i);
            REQUIRE(q.height() != 0);
            REQUIRE_NOTHROW(q.deleteMin());
        }
    }
    SECTION("Auto Rebalance", "[MinPriorityQueue]")
    {
        q.setAutoRebalance(true);
        for (std::size_t i = TEST_QTY; i > 0; i--) {
            std::size_t r = (rand() % TEST_QTY) + 1;
            REQUIRE(q.insert(r, r));
            REQUIRE_NOTHROW(q.getMinItem());
            REQUIRE_NOTHROW(q.getMinValue());
            REQUIRE(q.size() == TEST_QTY - i + 1);
            REQUIRE(q.height() != 0);
        }
        q.printTree();
        for (std::size_t i = TEST_QTY; i > 0; i--) {
            REQUIRE_NOTHROW(q.getMinItem());
            REQUIRE_NOTHROW(q.getMinValue());
            REQUIRE(q.size() == i);
            REQUIRE(q.height() != 0);
            REQUIRE_NOTHROW(q.deleteMin());
        }
    }
}
