#include "catch.hpp"

#include <sstream>
#include <iostream>

#include "parser.hpp"
#include "lexer.hpp"
#include "parser_utilities.hpp"


TEST_CASE("Utilities", "[Parser Utilities]") {
    REQUIRE(is_num("12340506"));
    REQUIRE(is_num("-12340506"));
    REQUIRE(is_num("1"));
    REQUIRE(is_num("+106"));
    REQUIRE_FALSE(is_num("/12340506"));
    REQUIRE_FALSE(is_num(""));
    REQUIRE_FALSE(is_num("assa"));

    REQUIRE(conv_data_type(".text") == ERR);
    REQUIRE(conv_data_type(".word") == WORD);

    REQUIRE(conv_reg_val(".text") == INVALID);
    REQUIRE(conv_reg_val("$k1") == K1);


    REQUIRE(conv_instr_type("meme") == INVAL);
    REQUIRE(conv_instr_type("j") == JUMP);

    num i;
    i.x = 100000;
    REQUIRE(validate_int(i, WORD));
}


//bool parse_data();
//bool parse_text();
//bool parse_constant();
//bool parse_label();
//bool parse_var();
//bool parse_ints(enum data_type type);
//bool parse_str(enum data_type type);
//bool parse_instr();
//bool parse_sep(); 
//bool parse_arg(arg & a, enum arg_type type);

//bool parse_tag(arg & a);
//bool parse_reg(arg & a);
//bool parse_mem(arg & a);
//bool parse_imm(arg & a);
//bool parse_source(arg & a);

TEST_CASE("Constants", "[Parser]") {
    std::stringstream s("TEST = 1239493");
    auto l = tokenize(s);
    program prog;
    parser p(prog, l.begin(), l.end(), std::cout);
    arg a;
    REQUIRE(p.parse_constant());
}


TEST_CASE("Data", "[Parser]") {
    std::stringstream s("\n\
var1: .word 1024, 13311\n\
      .word 12, 1\n\
LLLE = 11\n\
var2: .half 12\n\
");
    auto l = tokenize(s);
    program prog;
    parser p(prog, l.begin(), l.end(), std::cout);
    arg a;
    REQUIRE(p.parse_data());
}

TEST_CASE("Separators", "[Parser]") {
    std::stringstream s(",,,");
    auto l = tokenize(s);
    program prog;
    parser p(prog, l.begin(), l.end(), std::cout);
    arg a;
    REQUIRE(p.parse_sep());
    REQUIRE(p.parse_sep());
    REQUIRE(p.parse_sep());
}

TEST_CASE("Variable", "[Parser]") {
    SECTION("Var int") {
        std::stringstream s("test: .word 21, 1243\n\
                                   .byte 1");
        auto l = tokenize(s);
        program prog;
        parser p(prog, l.begin(), l.end(), std::cout);
        arg a;
        REQUIRE(p.parse_var());
    }
    SECTION("Var int") {
        std::stringstream s("test: .word 21, 1243");
        auto l = tokenize(s);
        program prog;
        parser p(prog, l.begin(), l.end(), std::cout);
        arg a;
        REQUIRE(p.parse_var());
    }
    SECTION("Var int") {
        std::stringstream s("test: .word 21");
        auto l = tokenize(s);
        program prog;
        parser p(prog, l.begin(), l.end(), std::cout);
        arg a;
        REQUIRE(p.parse_var());
    }
    SECTION("Var str") {
        std::stringstream s("tewt: .ascii \"Tejewjwjwjw rjejejj \"");
        auto l = tokenize(s);
        program prog;
        parser p(prog, l.begin(), l.end(), std::cout);
        arg a;
        REQUIRE(p.parse_var());
    }
    SECTION("Integer") {
        std::stringstream s("21");
        auto l = tokenize(s);
        program prog;
        parser p(prog, l.begin(), l.end(), std::cout);
        arg a;
        REQUIRE(p.parse_ints(WORD));
    }
    SECTION("Integer") {
        std::stringstream s("-1221");
        auto l = tokenize(s);
        program prog;
        parser p(prog, l.begin(), l.end(), std::cout);
        arg a;
        REQUIRE(p.parse_ints(WORD));
    }
    SECTION("Integers") {
        std::stringstream s("21, 234, -1393");
        auto l = tokenize(s);
        program prog;
        parser p(prog, l.begin(), l.end(), std::cout);
        arg a;
        REQUIRE(p.parse_ints(WORD));
    }
    SECTION("Strings") {
        std::stringstream s("\"helllo othicd\"");
        auto l = tokenize(s);
        program prog;
        parser p(prog, l.begin(), l.end(), std::cout);
        arg a;
        REQUIRE(p.parse_str(ASCII));
    }
}












































TEST_CASE("Parse Indirect Offset", "[Parser]") {
    std::stringstream s("2($t0)");
    auto l = tokenize(s);
    program prog;
    parser p(prog, l.begin(), l.end(), std::cout);
    arg a;
    SECTION("Mem") {
        REQUIRE(p.parse_mem(a));
    }
    SECTION("Source") {
        REQUIRE(p.parse_source(a));
    }
    SECTION("Arg") {
        REQUIRE(p.parse_arg(a, MEM));
    }
    SECTION("Arg") {
        REQUIRE(p.parse_arg(a, SOURCE));
    }
}
TEST_CASE("Parse Indirect", "[Parser]") {
    std::stringstream s("($t0)");
    auto l = tokenize(s);
    program prog;
    parser p(prog, l.begin(), l.end(), std::cout);
    arg a;
    SECTION("Mem") {
        REQUIRE(p.parse_mem(a));
    }
    SECTION("Source") {
        REQUIRE(p.parse_source(a));
    }
    SECTION("Arg") {
        REQUIRE(p.parse_arg(a, MEM));
    }
    SECTION("Arg") {
        REQUIRE(p.parse_arg(a, SOURCE));
    }
}
TEST_CASE("Parse Register", "[Parser]") {
    std::stringstream s("$t0");
    auto l = tokenize(s);
    program prog;
    parser p(prog, l.begin(), l.end(), std::cout);
    arg a;
    SECTION("Reg") {
        REQUIRE(p.parse_reg(a));
    }
    SECTION("Source") {
        REQUIRE(p.parse_source(a));
    }
    SECTION("Arg") {
        REQUIRE(p.parse_arg(a, REG));
    }
    SECTION("Arg") {
        REQUIRE(p.parse_arg(a, SOURCE));
    }
}


