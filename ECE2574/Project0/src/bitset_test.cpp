/*
 * bitset_test.cpp - Test cases for the bitset class.
 *
 * Author: Jacob Abel
 *
 * This file is part of Project 0.
 */

#include <algorithm>
#include <functional>
#include <array>
#include <cmath>

#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "bitset.hpp"

enum bound {
    LOWER_BOUND,
    UPPER_BOUND
};
static std::array<const intmax_t, 2> invalid_size = { 0, -1 };
static std::array<const std::string, 7> invalid_string = {
    " 0101100001",
    "0101100001 ",
    " ",
    "",
    "\n",
    "0000\n11",
    "000a0a0a02"
};
static std::array<const intmax_t, 6> valid_size = { 1, 2, 4, 8, 32, 1024 };
static std::array<const std::string, 7> valid_string = {
    "0",
    "1",
    "00000000000000000000000000000000000000000000",
    "11111111111111111111111111111111111111111111111",
    "0101010100110101010101001010101010101010110"
};

static auto string_cmp = [](std::string a) {
    Bitset bit(a);
    REQUIRE(bit.asString() == a);
};
static auto size_cmp = [](intmax_t a) {
    Bitset bit(a);
    REQUIRE(bit.size() == a);
};

static std::array<std::function<void(Bitset&, intmax_t)>, 3> mutators = {
    std::mem_fn(&Bitset::set),
    std::mem_fn(&Bitset::reset),
    std::mem_fn(&Bitset::toggle)
};

TEST_CASE("Constructors") {
    SECTION("Default Constructor") {
        Bitset bit;
        REQUIRE(bit.good());
    }
    SECTION("String Copy Constructor") {
        std::for_each(invalid_string.cbegin(), invalid_string.cend(), [](std::string a) {
            Bitset bit(a);
            REQUIRE_FALSE(bit.good());
        });
    }
    SECTION("Sized Constructor") {
        std::for_each(invalid_size.cbegin(), invalid_size.cend(), [](intmax_t a) {
            Bitset bit(a);
            REQUIRE_FALSE(bit.good());
        });
    }
}

TEST_CASE("Pure Accessors") {
    SECTION("good") {
        std::for_each(valid_size.cbegin(), valid_size.cend(), [](intmax_t a) {
            Bitset bit(a);
            REQUIRE(bit.good());
        });
    }
    SECTION("size") {
        std::for_each(valid_size.cbegin(), valid_size.cend(), size_cmp);
    }
    SECTION("asString") {
        std::for_each(valid_string.cbegin(), valid_string.cend(), string_cmp);
    }
}

TEST_CASE("Accesors with side effects") {
    SECTION("test") {
        std::for_each(valid_string.cbegin(), valid_string.cend(), string_cmp);
    }
}

TEST_CASE("Mutators") {
    Bitset bit0;
    Bitset bitstr("11110101");
    SECTION("set") {
        bit0.set(0);
        bit0.set(3);
        bit0.set(4);
        bit0.set(4);
        REQUIRE(bit0.asString() == "00011001");
    }
    SECTION("reset") {
        bitstr.reset(0);
        bitstr.reset(3);
        bitstr.reset(4);
        bitstr.reset(4);
        REQUIRE(bitstr.asString() == "11100100");
    }
    SECTION("toggle") {
        bitstr.toggle(0);
        bitstr.toggle(3);
        bitstr.toggle(4);
        bitstr.toggle(6);
        bitstr.toggle(1);
        bitstr.toggle(1);
        bitstr.toggle(7);
        REQUIRE(bitstr.asString() == "00101100");
    }
}

TEST_CASE("Bounds Checking") {
    using namespace std::placeholders;
    auto test_bounds = [](std::string a, enum bound b) {
        Bitset bit(a);
        INFO("String: " << a);
        INFO("Bitset: " << bit.asString());
        REQUIRE_FALSE(bit.test((b == LOWER_BOUND) ? (-1) : (a.length())));
        REQUIRE_FALSE(bit.good());
    };
    auto mutator_bounds_ = [](std::string a, enum bound b,
                              std::function<void(Bitset&, intmax_t)> fn) {
        Bitset bit(a);
        INFO("String: " << a);
        INFO("Bitset: " << bit.asString());
        fn(bit, ((b == LOWER_BOUND) ? (-1) : (a.length())));
        REQUIRE_FALSE(bit.good());
    };
    auto mutator_bounds = [&](std::string a, enum bound b) {
        std::for_each(mutators.cbegin(), mutators.cend(),
            std::bind(mutator_bounds_, a, b, _1)
        );
    };
    SECTION("Test Functions: Lower Bounds") {
        std::for_each(valid_string.cbegin(), valid_string.cend(),
            std::bind(test_bounds, _1, LOWER_BOUND)
        );
    }
    SECTION("Test Functions: Upper Bounds") {
        std::for_each(valid_string.cbegin(), valid_string.cend(),
            std::bind(test_bounds, _1, UPPER_BOUND)
        );
    }
    SECTION("Mutator: Lower Bounds") {
        std::for_each(valid_string.cbegin(), valid_string.cend(),
            std::bind(mutator_bounds, _1, LOWER_BOUND)
        );
    }
    SECTION("Mutator: Upper Bounds") {
        std::for_each(valid_string.cbegin(), valid_string.cend(),
            std::bind(mutator_bounds, _1, UPPER_BOUND)
        );
    }
}
