#include "catch.hpp"

#include "environment.hpp"
#include "semantic_error.hpp"

#include "interpreter.hpp"

#include <cmath>


TEST_CASE( "Test default constructor", "[environment]" ) {

  Environment env;

  std::vector<std::string> constants = {"pi", "e", "I"};
  std::vector<std::string> functions = {
         "+",    "-",    "*",   "/", 
         "^", "sqrt",   "ln",
       "sin",  "cos",  "tan",
      "real", "imag", "conj", "arg",  "mag"
  };

  for (auto x : constants) {  
      CAPTURE(x);
      REQUIRE(env.is_known(Atom(x)));
      REQUIRE(env.is_exp(Atom(x)));
  }
 
  REQUIRE(!env.is_known(Atom("hi")));
  REQUIRE(!env.is_exp(Atom("hi")));

  for (auto x : functions) {  
      CAPTURE(x);
      REQUIRE(env.is_known(Atom(x)));
      REQUIRE(env.is_proc(Atom(x)));
  }
  
  REQUIRE(!env.is_proc(Atom("op")));
}

TEST_CASE( "Test get expression", "[environment]" ) {
  Environment env;

  REQUIRE(env.get_exp(Atom("pi")) == Expression(std::atan2(0, -1)));
  REQUIRE(env.get_exp(Atom("hi")) == Expression());
}

TEST_CASE( "Test add expression", "[environment]" ) {
  Environment env;

  Expression a(Atom(1.0));
  env.add_exp(Atom("one"), a);
  REQUIRE(env.is_known(Atom("one")));
  REQUIRE(env.is_exp(Atom("one")));
  REQUIRE(env.get_exp(Atom("one")) == a);

  Expression b(Atom("hello"));
  env.add_exp(Atom("hi"), b);
  REQUIRE(env.is_known(Atom("hi")));
  REQUIRE(env.is_exp(Atom("hi")));
  REQUIRE(env.get_exp(Atom("hi")) == b);

  REQUIRE_THROWS_AS(env.add_exp(Atom(1.0), b), SemanticError);
}

TEST_CASE( "Test get built-in procedure", "[environment]" ) {
  Environment env;

  INFO("default procedure")
  Procedure p1 = env.get_proc(Atom("doesnotexist"));
  Procedure p2 = env.get_proc(Atom("alsodoesnotexist"));
  REQUIRE(p1 == p2);
  std::vector<Expression> args;
  REQUIRE(p1(args) == Expression());
  REQUIRE(p2(args) == Expression());

  INFO("trying add procedure")
  Procedure padd = env.get_proc(Atom("+"));
  args.emplace_back(1.0);
  args.emplace_back(2.0);
  REQUIRE(padd(args) == Expression(3.0));
}

TEST_CASE( "Test reset", "[environment]" ) {
  Environment env;

  Expression a(Atom(1.0));
  env.add_exp(Atom("one"), a);
  Expression b(Atom("hello"));
  env.add_exp(Atom("hi"), b);

  env.reset();
  REQUIRE(!env.is_known(Atom("one")));
  REQUIRE(!env.is_exp(Atom("one")));
  REQUIRE(env.get_exp(Atom("one")) == Expression());
  REQUIRE(!env.is_known(Atom("hi")));
  REQUIRE(!env.is_exp(Atom("hi")));
  REQUIRE(env.get_exp(Atom("hi")) == Expression());
}

TEST_CASE( "Test semeantic errors", "[environment]" ) {

  Environment env;

  {
    Expression exp(Atom("begin"));
    
    REQUIRE_THROWS_AS(exp.eval(env), SemanticError);
  }
}


TEST_CASE( "Test Default Functions", "[environment]" ) {
 auto test_pls = [] (std::string const & pls) {
      std::istringstream ss(pls);
      Interpreter intr;
      intr.parseStream(ss);
      return intr.evaluate();
  };

  std::vector<std::pair<std::string, std::string>> pass_cases {
  // input,                         result,               test case 
    { "( + 3 )"                 , "( 3 )"           }, // Add 1 Arg
    { "( + 3 5 )"               , "( 8 )"           }, // Add 2 Arg
    { "( + 3 5 2 )"             , "( 10 )"          }, // Add 3 Arg
    { "( * 2 )"                 , "( 2 )"           }, // Mul 1 Arg 
    { "( * 2 5 )"               , "( 10 )"          }, // Mul 2 Arg 
    { "( * 2 5 3 )"             , "( 30 )"          }, // Mul 3 Arg
    { "( - 5 3 )"               , "( 2 )"           }, // Sub  
    { "( - 4   )"               , "( -4 )"          }, // Neg 
    { "( / 1 1 )"               , "( 1 )"           }, // Div 
    { "( ^ 5 2 )"               , "( 25 )"          }, // Pow
    { "( ^ (+ 4 I) 2 )"         , "(+ 15 (* 8 I))"  }, // Pow
    { "( ^ I 2 )"               , "(+  -1 (* 0 I))" }, // Pow
    { "( sqrt 4 )"              , "( 2 )"           }, // Sqrt 
    { "( ln e )"                , "( 1 )"           }, // Log 
    { "( sin (/ pi 2) )"        , "( 1 )"           }, // Sin 
    { "( cos pi )"              , "( -1 )"          }, // Cos 
    { "( tan pi )"              , "( 0 )"           }, // Tan 
    { "( real (+ 2 I ))"        , "( 2 )"           }, // Real
    { "( imag (+ 2 I ))"        , "( 1 )"           }, // Imag
    { "( mag  (+ 3 (* 4 I)))"   , "( 5 )"           }, // Mag
    { "( arg  (+ 1 I ))"        , "(/ pi 4)"        }, // Arg
    { "( conj (+ 3 ( * 4 I)))" , "(- 3 (* 4 I))"    }, // Conj
  };

  std::vector<std::string> fail_cases {
  // input,                          test case 
    "( * 2 qr )"                , // Mul Invalid Arg
    "( / 2 rq )"                , // Div Invalid Arg
    "( + 2 rq )"                , // Add Invalid Arg
    "( - 2 qr )"                , // Sub Invalid Arg
    "( - q )"                   , // Neg Invalid Arg
    "( / q q )"                 , // Div Invalid Arg
    "( / q q )"                 , // Div Invalid Arg
    "( / 3 )"                   , // Div Invalid # of Arg
    "( ^ 1 )"                   , // Pow Invalid # of Arg
    "( - 3 2 2 )"               , // Sub Invalid # of Arg
    "( sqrt 4 2 )"              , // Sqrt Invalid # of Arg
  };

  for (auto const & p : pass_cases) {
    //SECTION("Pass Case", "[Environment]") {
      Expression test;
      Expression result = test_pls(std::get<1>(p));
      CAPTURE(std::get<0>(p));
      CAPTURE(std::get<1>(p));
      REQUIRE_NOTHROW(test = test_pls(std::get<0>(p)));
      REQUIRE(test == result);
  //  }
  }

  for (auto const & p : fail_cases) {
    SECTION("Fail Case", "[Environment]") {
      CAPTURE(p);
      REQUIRE_THROWS_AS(test_pls(p), SemanticError);
    }
  }
}
