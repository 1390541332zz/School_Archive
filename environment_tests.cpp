#include "catch.hpp"

#include "environment.hpp"
#include "semantic_error.hpp"

#include <cmath>

//enum test_state { SUCCEED, FAIL };

TEST_CASE( "Test default constructor", "[environment]" ) {

  Environment env;

  std::vector<std::string> constants = {"pi", "e"};
  std::vector<std::string> functions = {
      "+", "-", "*", "/", "^", "sqrt", "ln", "sin", "cos", "tan"
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


//TEST_CASE( "Test Default Functions", "[environment]" ) {
//
//  Environment env;
//
//  std::vector<std::pair<enum test_state, std::vector<Atom>> test_cases = {
//  // test state,           op,        x,        y,     result,      test case 
//    { SUCCEED, { Atom(   "+"), Atom( 3), Atom(  5), Atom(  8) }}, // Add Succeed
//    {    FAIL, { Atom(   "+"), Atom( 3), Atom(   ),           }}, // Add Invalid Arg
//    { SUCCEED, { Atom(   "-"), Atom( 5), Atom(  3), Atom(  2) }}, // Sub Succeed 
//    { SUCCESS, { Atom(   "-"), Atom( 4),            Atom( -4) }}, // Neg Succeed
//    {    FAIL, { Atom(   "-"), Atom( 3), Atom(   ),           }}, // Sub Invalid Arg
//    {    FAIL, { Atom(   "-"), Atom( 3),                      }}, // Sub Invalid Arg
//    { SUCCEED, { Atom(   "*"), Atom( 2), Atom(  5), Atom( 10) }}, // Mul Succeed
//    {    FAIL, { Atom(   "*"), Atom( 3), Atom("q"),           }}, // Mul Invalid Arg
//    {    FAIL, { Atom(   "*"), Atom( 3),                      }}, // Mul Invalid # of Arg
//    { SUCCEED, { Atom(   "/"), Atom( 1), Atom(  1), Atom(  2) }}, // Div Succeed
//    {    FAIL, { Atom(   "/"), Atom( 3), Atom(  0),           }}, // Div Invalid Arg
//    {    FAIL, { Atom(   "/"), Atom( 3),                      }}, // Div Invalid # of Arg
//    { SUCCESS, { Atom("sqrt"), Atom( 4),            Atom(  2) }}, // Sqrt Succeed
//    { SUCCESS, { Atom("sqrt"), Atom(-1),                      }}, // Sqrt Negative
//    {    FAIL, { Atom("sqrt"), Atom( 4), Atom(  2)            }}, // Sqrt Invalid $ of Arg
//  };
//
//  for (auto & t : test_cases) {
//    if (t.first == SUCCEED) {
//        switch (t.second.size())
//          case 3:
//            env.add_exp();
//            break;
//          case 4:
//            
//            break;
//          default:
//            break;
//    } else if (t.first == FAIL) {
//        
//    }
//  }
//}
