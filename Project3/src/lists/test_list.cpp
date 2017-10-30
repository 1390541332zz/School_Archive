#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "dynamic_array_list.hpp"
#include "linked_list.hpp"

TEST_CASE("Rounding Up", "[round_base2]") {
    std::size_t rounds[][2] = {
        {1,   2},   {3,   4},
        {6,   8},   {11,  16},
        {21,  32},  {34,  64},
        {85,  128}, {150, 256},
        {312, 512}, {745, 1024}
    };

    for (auto x : rounds) {
        REQUIRE(x[1] == round_base2(x[0]));
    }
}

TEST_CASE("Basic Operation", "[Lists]") {

}
