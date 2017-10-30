#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <cstdlib>

#include "dynamic_array_list.hpp"
#include "linked_list.hpp"


TEST_CASE("Basic Operation", "[Lists]")
{
    LinkedList<std::size_t> ll;
    DynamicArrayList<std::size_t> dl;
    REQUIRE(ll.isEmpty());
    REQUIRE(dl.isEmpty());
    for (std::size_t i = 0; i < 100; i++) {
        REQUIRE(ll.getLength() == i);
        REQUIRE(dl.getLength() == i);
        REQUIRE_NOTHROW(ll.insert(i, i));
        REQUIRE_NOTHROW(dl.insert(i, i));
        REQUIRE_FALSE(ll.isEmpty());
        REQUIRE_FALSE(dl.isEmpty());
    }
    SECTION("Mutators and Accessors", "[Lists]")
    {
        SECTION("Sequential Insertion, Deletion, and Modification", "[Lists]")
        {
            for (std::size_t i = 99; i > 0; i--) {
                REQUIRE(ll.getEntry(i) == i);
                REQUIRE(dl.getEntry(i) == i);
                REQUIRE_NOTHROW(ll.setEntry(i, i + 1));
                REQUIRE_NOTHROW(dl.setEntry(i, i + 1));
                REQUIRE(ll.getEntry(i) == i + 1);
                REQUIRE(dl.getEntry(i) == i + 1);
                REQUIRE_NOTHROW(ll.remove(i));
                REQUIRE_NOTHROW(dl.remove(i));
                REQUIRE(ll.getLength() == i);
                REQUIRE(dl.getLength() == i);
            }
            REQUIRE_NOTHROW(ll.remove(0));
            REQUIRE_NOTHROW(dl.remove(0));
            REQUIRE(ll.getLength() == 0);
            REQUIRE(dl.getLength() == 0);
        }
        SECTION("Out of Order Insertion", "[Lists]")
        {
            for (std::size_t i = 0; i < 50; i++) {
                REQUIRE_NOTHROW(ll.insert(i * 2, i * 1000));
                REQUIRE_NOTHROW(dl.insert(i * 2, i * 1000));
                REQUIRE(ll.getEntry(i * 2) == i * 1000);
                REQUIRE(dl.getEntry(i * 2) == i * 1000);
            }
        }
        SECTION("Out of Order Deletion", "[Lists]")
        {
            for (std::size_t i = 50; i > 0; i--) {
                REQUIRE_NOTHROW(ll.remove(i * 2 - 1));
                REQUIRE_NOTHROW(dl.remove(i * 2 - 1));
            }
            REQUIRE(ll.getLength() == 50);
            REQUIRE(dl.getLength() == 50);
            for (std::size_t i = 0; i < 50; i++) {
                REQUIRE(ll.getEntry(i) == i * 2);
                REQUIRE(dl.getEntry(i) == i * 2);
            }
        }
        SECTION("Clear", "[Lists]")
        {
            ll.clear();
            dl.clear();
            REQUIRE(ll.isEmpty());
            REQUIRE(dl.isEmpty());
            ll.clear();
            dl.clear();
        }
    }
    SECTION("Copy Operators", "[Lists]")
    {
        LinkedList<std::size_t> llc(ll);
        DynamicArrayList<std::size_t> dlc(dl);

        LinkedList<std::size_t> lla = ll;
        DynamicArrayList<std::size_t> dla = dl;

        for (std::size_t i = 0; i < 100; i++) {
            REQUIRE(llc.getEntry(i) == i);
            REQUIRE(dlc.getEntry(i) == i);

            REQUIRE(lla.getEntry(i) == i);
            REQUIRE(dla.getEntry(i) == i);
        }
    }
}

TEST_CASE("Bounds Checking", "[Lists]")
{
    LinkedList<std::size_t> ll;
    DynamicArrayList<std::size_t> dl;
    for (std::size_t i = 0; i < 50; i++) {
        ll.insert(i, i);
        dl.insert(i, i);
    }
    REQUIRE_THROWS(ll.insert(1000, 1000));
    REQUIRE_THROWS(dl.insert(1000, 1000));
    REQUIRE_THROWS(ll.remove(1000));
    REQUIRE_THROWS(dl.remove(1000));

    REQUIRE_THROWS(ll.setEntry(1000, 1000));
    REQUIRE_THROWS(dl.setEntry(1000, 1000));
    REQUIRE_THROWS(ll.getEntry(1000));
    REQUIRE_THROWS(dl.getEntry(1000));

    REQUIRE_THROWS(ll.remove(100));
    REQUIRE_THROWS(dl.remove(100));

    REQUIRE_THROWS(ll.setEntry(100, 100));
    REQUIRE_THROWS(dl.setEntry(100, 100));
    REQUIRE_THROWS(ll.getEntry(100));
    REQUIRE_THROWS(dl.getEntry(100));
}

TEST_CASE("Access Schemes", "[Lists]")
{
    LinkedList<std::size_t> ll;
    DynamicArrayList<std::size_t> dl;

    SECTION("First In, First Out", "[List]") {
        for (std::size_t i = 0; i < 50; i++) {
            ll.insert(0, 50-i);
            dl.insert(0, 50-i);
        }
        for (std::size_t i = 0; i < 50; i++) {
            ll.remove(0);
            dl.remove(0);
        }
    }

    SECTION("First In, First Out", "[List]") {
        for (std::size_t i = 1; i < 51; i++) {
            std::size_t x = std::rand() % i;
            ll.insert(x, x);
            dl.insert(x, x);
        }
        for (std::size_t i = 1; i < 51; i++) {
            std::size_t x = std::rand() % (51-i);
            ll.remove(x);
            dl.remove(x);
        }
    }
}
