#include "catch.hpp"
#include <sstream>

#include "atom.hpp"

TEST_CASE("Test constructors", "[atom]")
{

    {
        INFO("Default Constructor");
        Atom a;

        REQUIRE(a.isNone());
        REQUIRE(!a.isNumber());
        REQUIRE(!a.isSymbol());
    }

    {
        INFO("Number Constructor");
        Atom a(1.0);

        REQUIRE(!a.isNone());
        REQUIRE(a.isNumber());
        REQUIRE(!a.isSymbol());
    }

    {
        INFO("Symbol Constructor");
        Atom a("hi");

        REQUIRE(!a.isNone());
        REQUIRE(!a.isNumber());
        REQUIRE(a.isSymbol());
    }

    {
        INFO("Token Constructor");
        Token t("hi");
        Atom a(t);

        REQUIRE(!a.isNone());
        REQUIRE(!a.isNumber());
        REQUIRE(a.isSymbol());
    }

    {
        INFO("Copy Constructor");
        Atom a("hi");
        Atom b(1.0);
        Atom c;
        Atom d(std::complex<double>(1, 1));

        Atom e(a);
        REQUIRE(!a.isNone());
        REQUIRE(!e.isNumber());
        REQUIRE(e.isSymbol());

        Atom f(b);
        REQUIRE(!b.isNone());
        REQUIRE(f.isNumber());
        REQUIRE(!f.isSymbol());

        Atom g(c);
        REQUIRE(c.isNone());
        REQUIRE(g.isNone());
        REQUIRE(!g.isSymbol());

        Atom h(d);
        REQUIRE(d.isComplex());
        REQUIRE(h.isComplex());
        REQUIRE(!h.isNumber());
    }
}

TEST_CASE("Test assignment", "[atom]")
{

    {
        INFO("default to default");
        Atom a;
        Atom b;
        b = a;
        REQUIRE(b.isNone());
        REQUIRE(!b.isNumber());
        REQUIRE(!b.isSymbol());
        b = std::move(a);
        REQUIRE(b.isNone());
        REQUIRE(!b.isNumber());
        REQUIRE(!b.isSymbol());
    }

    {
        INFO("default to number");
        Atom a;
        Atom b(1.0);
        b = a;
        REQUIRE(b.isNone());
        REQUIRE(!b.isNumber());
        REQUIRE(!b.isSymbol());
        b = std::move(a);
        REQUIRE(b.isNone());
        REQUIRE(!b.isNumber());
        REQUIRE(!b.isSymbol());
    }

    {
        INFO("default to symbol");
        Atom a;
        Atom b("hi");
        b = a;
        REQUIRE(b.isNone());
        REQUIRE(!b.isNumber());
        REQUIRE(!b.isSymbol());
        b = std::move(a);
        REQUIRE(b.isNone());
        REQUIRE(!b.isNumber());
        REQUIRE(!b.isSymbol());
    }

    {
        INFO("number to default");
        Atom a(1.0);
        Atom b;
        b = a;
        REQUIRE(b.isNumber());
        REQUIRE(b.asNumber() == 1.0);
        b = std::move(a);
        REQUIRE(b.isNumber());
        REQUIRE(b.asNumber() == 1.0);
    }

    {
        INFO("number to number");
        Atom a(1.0);
        Atom b(2.0);
        a = a;
        REQUIRE(a.isNumber());
        REQUIRE(a.asNumber() == 1.0);
        b = a;
        REQUIRE(b.isNumber());
        REQUIRE(b.asNumber() == 1.0);
        b = std::move(a);
        REQUIRE(b.isNumber());
        REQUIRE(b.asNumber() == 1.0);
        b = std::move(b);
        REQUIRE(b.isNumber());
        REQUIRE(b.asNumber() == 1.0);
    }

    {
        INFO("number to symbol");
        Atom a("hi");
        Atom b(1.0);
        b = a;
        REQUIRE(b.isSymbol());
        REQUIRE(b.asSymbol() == "hi");
        b = std::move(a);
        REQUIRE(b.isSymbol());
        REQUIRE(b.asSymbol() == "hi");
    }

    {
        INFO("symbol to default");
        Atom a("hi");
        Atom b;
        b = a;
        REQUIRE(b.isSymbol());
        REQUIRE(b.asSymbol() == "hi");
        b = std::move(a);
        REQUIRE(b.isSymbol());
        REQUIRE(b.asSymbol() == "hi");
    }

    {
        INFO("symbol to number");
        Atom a("hi");
        Atom b(1.0);
        b = a;
        REQUIRE(b.isSymbol());
        REQUIRE(b.asSymbol() == "hi");
        b = std::move(a);
        REQUIRE(b.isSymbol());
        REQUIRE(b.asSymbol() == "hi");
    }

    {
        INFO("symbol to symbol");
        Atom a("hi");
        Atom b("bye");
        b = a;
        REQUIRE(b.isSymbol());
        REQUIRE(b.asSymbol() == "hi");
        b = std::move(a);
        REQUIRE(b.isSymbol());
        REQUIRE(b.asSymbol() == "hi");
    }
}

TEST_CASE("test comparison", "[atom]")
{

    {
        INFO("compare default to default");
        Atom a;
        Atom b;
        REQUIRE(a == b);
    }

    {
        INFO("compare default to number");
        Atom a;
        Atom b(1.0);
        REQUIRE(a != b);
    }

    {
        INFO("compare default to symbol");
        Atom a;
        Atom b("hi");
        REQUIRE(a != b);
    }

    {
        INFO("compare number to default");
        Atom a(1.0);
        Atom b;
        REQUIRE(a != b);
    }

    {
        INFO("compare number to number");
        Atom a(1.0);
        Atom b(1.0);
        Atom c(2.0);
        REQUIRE(a == b);
        REQUIRE(a != c);
    }

    {
        INFO("compare number to symbol");
        Atom a(1.0);
        Atom c(std::complex<double>(1.0, 2.0));
        Atom b("hi");
        REQUIRE(a != b);
        REQUIRE(c != b);
    }

    {
        INFO("compare symbol to default");
        Atom a("hi");
        Atom b;
        REQUIRE(a != b);
    }

    {
        INFO("compare symbol to number");
        Atom a("hi");
        Atom b(1.0);
        REQUIRE(a != b);
    }

    {
        INFO("compare symbol to symbol");
        Atom a("hi");
        Atom b("hi");
        Atom c("bye");
        REQUIRE(a == b);
        REQUIRE(a != c);
    }
}

TEST_CASE("test output", "[atom]")
{
    Atom a(std::complex<double>(1, 1));
    Atom b("str");

    std::ostringstream ss;
    SECTION("complex output", "[atom]")
    {
        ss << a;
        REQUIRE(ss.str() == "1,1");
    }
    SECTION("string invalid output", "[atom]")
    {
        ss << b.asNumber() << ' ' << b.asComplex();
        REQUIRE(ss.str() == "0 (0,0)");
    }
}
