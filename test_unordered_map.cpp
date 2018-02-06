#include <unordered_map>

#define CATCH_CONFIG_MAIN
#include "catch.hpp"


TEST_CASE("Random Tests", "[unordered_map]") {
    std::unordered_map<int,int> m;
    for (std::size_t i = 0; i < 100; ++i) m[i] = i;
    for (std::size_t i = 0; i < 100; ++i) {
        REQUIRE(m[i] == i);
    }
}
