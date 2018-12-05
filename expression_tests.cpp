#include "catch.hpp"
#include "expression.hpp"
#include "interpreter.hpp"
#include <sstream>

TEST_CASE("Test default expression", "[expression]")
{

    Expression exp;

    REQUIRE(!exp.isHeadNumber());
    REQUIRE(!exp.isHeadSymbol());
}

TEST_CASE("Test double expression", "[expression]")
{

    Expression exp(6.023);

    REQUIRE(exp.isHeadNumber());
    REQUIRE(!exp.isHeadSymbol());
}

TEST_CASE("Test symbol expression", "[expression]")
{

    Expression exp(Atom("asymbol"));

    REQUIRE(!exp.isHeadNumber());
    REQUIRE(exp.isHeadSymbol());
}

TEST_CASE("Test prop checks", "[expression]")
{
    auto test_pls = [](std::string const & pls) {
        std::istringstream ss(pls);
        Interpreter intr;
        intr.parseStream(ss);
        return intr.evaluate();
    };
    auto exp = test_pls("(set-property \"object-name\" \"text\"  \"yeet\")");
    REQUIRE(!exp.is("point"));
    REQUIRE(exp.is("text"));
    exp = test_pls("(+ 1 2)");
    REQUIRE(!exp.is("text"));
}
