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

auto string_cmp = [](std::string a) {
    Bitset bit(a);
    REQUIRE(bit.asString() == a);
};

auto size_cmp = [](intmax_t a) {
    Bitset bit(a);
    REQUIRE(bit.size() == a);
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
        REQUIRE(bit0.asString() == "10010000");
    }
    SECTION("reset") {
        bitstr.reset(0);
        bitstr.reset(3);
        REQUIRE(bitstr.asString() == "01100101");
    }
    SECTION("toggle") {
        bitstr.toggle(0);
        bitstr.toggle(3);
        bitstr.toggle(4);
        bitstr.toggle(6);
        REQUIRE(bitstr.asString() == "01101111");
    }
}
