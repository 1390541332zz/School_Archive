#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "vector.hpp"

TEST_CASE( "TODO", "[ThreadSafeVector]" ) {
    Vector<int> v;
    int a = 4;
    v([&a](std::vector<int>& x){x.push_back(a);});
    REQUIRE(v([](std::vector<int>& v){return v.back();}) == a);
}
