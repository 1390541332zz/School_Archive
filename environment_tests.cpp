#include "catch.hpp"

#include "environment.hpp"
#include "semantic_error.hpp"

#include "interpreter.hpp"

#include <cmath>

TEST_CASE("Test default constructor", "[environment]")
{

    Environment env;

    std::vector<std::string> constants = { "pi", "e", "I" };
    std::vector<std::string> functions = {
        "+", "-", "*", "/",
        "^", "sqrt", "ln",
        "sin", "cos", "tan",
        "real", "imag", "conj", "arg", "mag"
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

TEST_CASE("Test get expression", "[environment]")
{
    Environment env;

    REQUIRE(env.get_exp(Atom("pi")) == Expression(std::atan2(0, -1)));
    REQUIRE(env.get_exp(Atom("hi")) == Expression());
}

TEST_CASE("Test add expression", "[environment]")
{
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

TEST_CASE("Test get built-in procedure", "[environment]")
{
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

TEST_CASE("Test reset", "[environment]")
{
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

TEST_CASE("Test semeantic errors", "[environment]")
{

    Environment env;

    {
        Expression exp(Atom("begin"));

        REQUIRE_THROWS_AS(exp.eval(env), SemanticError);
    }
}

TEST_CASE("Test Default Functions", "[environment]")
{
    auto test_pls = [](std::string const & pls) {
        std::istringstream ss(pls);
        Interpreter intr;
        intr.parseStream(ss);
        return intr.evaluate();
    };

    // clang-format off
    std::vector<std::pair<std::string, std::string>> pass_cases{
        // input,                                result,                       test case
        // - Arithmetic Procedure Cases -
        { "( 3 )",                             "( 3 )"                         }, // No Proc
        { "( \"yeet\" )",                      "( \"yeet\" )"                  }, // No Proc
        { "( + 3 )",                           "( 3 )"                         }, // Add 1 Arg
        { "( + 3 5 )",                         "( 8 )"                         }, // Add 2 Arg
        { "( + 3 5 2 )",                       "( 10 )"                        }, // Add 3 Arg
        { "( * 2 )",                           "( 2 )"                         }, // Mul 1 Arg
        { "( * 2 5 )",                         "( 10 )"                        }, // Mul 2 Arg
        { "( * 2 5 3 )",                       "( 30 )"                        }, // Mul 3 Arg
        { "( - 5 3 )",                         "( 2 )"                         }, // Sub
        { "( - 4   )",                         "( -4 )"                        }, // Neg
        { "( / 2 )",                           "( 0.5 )"                       }, // Inverse 
        { "( / 1 1 )",                         "( 1 )"                         }, // Div
        { "( ^ 5 2 )",                         "( 25 )"                        }, // Pow
        { "( ^ (+ 4 I) 2 )",                   "(+ 15 (* 8 I))"                }, // Pow
        { "( ^ I 2 )",                         "(+  -1 (* 0 I))"               }, // Pow
        { "( sqrt 4 )",                        "( 2 )"                         }, // Sqrt
        { "( sqrt -1 )",                       "( I )"                         }, // Sqrt
        { "( ln e )",                          "( 1 )"                         }, // Log
        { "( ln (+ e (* 0 I)))",                "(+ 1 (* 0 I))"                }, // Log
        { "( sin (/ pi 2) )",                  "( 1 )"                         }, // Sin
        { "( cos pi )",                        "( -1 )"                        }, // Cos
        { "( tan pi )",                        "( 0 )"                         }, // Tan
        { "( real (+ 2 I ))",                  "( 2 )"                         }, // Real
        { "( imag (+ 2 I ))",                  "( 1 )"                         }, // Imag
        { "( mag  (+ 3 (* 4 I)))",             "( 5 )"                         }, // Mag
        { "( arg  (+ 1 I ))",                  "(/ pi 4)"                      }, // Arg
        { "( conj (+ 3 ( * 4 I)))",            "(- 3 (* 4 I))"                 }, // Conj
        // - List Procedure Cases - 
        { "(first (list 7 2 3))",              "(7)"                           }, // First
        { "(rest  (list 7 2 3))",              "(list 2 3)"                    }, // Rest
        { "(rest  (list 7))",                  "(rest (list 2))"               }, // Rest
        { "(rest  (list 7))",                  "(list)"                        }, // Rest
        { "(length (list))",                   "(0)"                           }, // Length
        { "(length (list 7 2 5))",             "(3)"                           }, // Length
        { "(append (list 7 2 3) 9)",           "(list 7 2 3 9)"                }, // Append
        { "(join (list 7 2 3) (list 1 5))",    "(list 7 2 3 1 5)"              }, // Join
        { "(range -3 3 1.4)",                  "(list -3 -1.6 -0.2 1.2 2.6)"   }, // Range
        { "(range 0 5 1)",                     "(list 0 1 2 3 4 5)"            }, // Range
        // - Lambda Procedure Cases - 
        { "(begin                           \
             (define f                      \
               (lambda (x) (* 2 x))         \
             )                              \
             (f 2)                          \
           )",                                 "(4)"                           }, // Lambda
        { "(begin                           \
             (define f                      \
               (lambda (x) (* 2 x))         \
             )                              \
             (define y 3)                   \
             (f y)                          \
           )",                                 "(6)"                           }, // Lambda
        { "(begin                           \
             (define f                      \
               (lambda (x y) (* 2 (+ x y))) \
             )                              \
             (define a 3)                   \
             (define b 4)                   \
             (f a b)                        \
           )",                                "(14)"                          }, // Lambda
        { "(begin                           \
             (define f                      \
               (lambda (x y) (* y (+ x b))) \
             )                              \
             (define a 3)                   \
             (define b 4)                   \
             (f a 2)                        \
           )",                                "(14)"                          }, // Capture
        { "(begin                           \
             (define f                      \
               (lambda (x y) (* 2 (+ x y))) \
             )                              \
             (define x 3)                   \
             (define y 4)                   \
             (f 2 4)                        \
           )",                                "(12)"                          }, // Shadow
        { "(apply                           \
             (lambda (x y) (* 2 (+ x y)))   \
             (list 2 3)                     \
           )",                                "(10)"                          }, // Apply 
        { "(apply + (list 1 2 3)            \
           )",                                "(6)"                           }, // Apply 
        { "(map / (list 1 2 4 8))",           "(list 1 0.5 0.25 0.125)"       }, // Map 
        { "(map (lambda (x) (- x))          \
            (list 1 2 3 4)                  \
           )",                                "(list -1 -2 -3 -4)"            }, // Map
        // - Property Procedure Cases -
        { "(set-property \"y\" 2 1)",         "(1)"                           }, // set-prop
        { "(get-property \"y\"              \
              (set-property \"y\" 2 1))",     "(2)"                           }, // get-prop
    };

    std::vector<std::string> fail_cases{
        // input,                                          test case
        "()",                                           // Invalid Type in terminal
        "(begin)",                                      // Zero Args
        "(define 1 1)",                                 // Define nonstring
        "(define + 1)",                                 // Define builtin
        "(y 1 2)",                                      // Undefined proc
        "(1 1 2)",                                      // Undefined proc
        "(g)",                                          // Undefined var
        // - Arithmetic Procedure Cases -    
        "( / 3 2 1)",                                   // Div Invalid # of Arg
        "( ^ 1 )",                                      // Pow Invalid # of Arg
        "( - 3 2 2 )",                                  // Sub Invalid # of Arg
        "( sqrt 4 2 )",                                 // Sqrt Invalid # of Arg
        "( ln 4 2 )",                                   // Log Invalid # of Arg
        "( sin 4 2 )",                                  // Sin Invalid # of Arg
        "( cos 4 2 )",                                  // Cos Invalid # of Arg
        "( tan 4 2 )",                                  // Tan Invalid # of Arg
        "( real I 2 )",                                 // Real Invalid # of Arg
        "( imag I 2 )",                                 // Imag Invalid # of Arg
        "( mag I 2 )",                                  // Mag Invalid # of Arg
        "( arg I 2 )",                                  // Arg Invalid # of Arg
        "( conj I 2 )",                                 // Conj Invalid # of Arg
        "( ln 0 )",                                     // Log Invalid Arg
        "( real 1 )",                                   // Real Non-complex Arg
        "( imag 1 )",                                   // Imag Non-complex Arg
        "( mag 1 )",                                    // Mag  Non-complex Arg
        "( arg 1 )",                                    // Arg  Non-complex Arg
        "( conj 1 )",                                   // Conj Non-complex Arg
        // - List Procedure Cases - 
        "(first (list 7 2 3) 2)",                       // First # of Args
        "(first 1)",                                    // First Not List
        "(first (list))",                               // First Empty List
        "(rest  (list 7 2 3) 2)",                       // Rest # of Args
        "(rest  1)",                                    // Rest Not List
        "(rest  (list))",                               // Rest Empty List
        "(length (list 7 2 5) 2)",                      // Length # of Args
        "(length 2)",                                   // Length Not List
        "(append (list 7 2 3) 9 7)",                    // Append # of Args
        "(append 9 (list 7 2 3))",                      // Append Not List
        "(join (list 7 2 3))",                          // Join # of Args
        "(join (list 7) (list 2) (list 3))",            // Join # of Args
        "(join (list 7 2 3) 9)",                        // Join Not List
        "(join 9 (list 7 2 3))",                        // Join Not List
        "(range 1 5 )",                                 // Range # of Args
        "(range 1 5 7 7)",                              // Range # of Args
        "(range (list 1 2) 4 3)",                       // Range Not Number
        "(range 7 1 2)",                                // Range Beg > End
        "(range 1 6 0)",                                // Range Neg Rate
        "(range 1 6 -4)",                               // Range Neg Rate
        // - Functional Procedure Cases -
        "(lambda (x))",                                 // lambda # of args
        "(lambda (1 2) (x))",                           // Lambda Not Arg List
        "(apply + (list 1 2) (1))",                     // Apply # of Args
        "(apply 1 (list 1 2))",                         // Apply No Proc
        "(apply + 1)",                                  // Apply No List
        "(apply first (list 1))",                       // Apply Proc fail
        "(apply (lambda (x) (first x)) (list 1))",      // Apply Lambda fail
        "(map + (list 1 2) (1))",                       // Map # of Args
        "(map 1 (list 1 2))",                           // Map No Proc
        "(map + 1)",                                    // Map No List
        "(map first (list (list)))",                    // Apply Proc fail
        "(map (lambda (x) (first x)) (list (list)))",   // Apply Lambda fail
        // - Property Procedure Cases -
        "(set-property \"y\" 2)",                       // set-prop # of args
        "(set-property 1 2 1)",                         // set-prop Not String
        "(get-property \"y\")",                         // set-prop # of args
        "(get-property 2 1)",                           // set-prop Not String
    };
    //clang-format on

    {
        Expression result = Atom{};
        auto str = "(get-property \"y\" 2)";
        Expression test = test_pls(str);
        CAPTURE(str);
        CAPTURE(result);
        REQUIRE_NOTHROW(test = test_pls(str));
        REQUIRE(test == result);
    }
    for (auto const& p : pass_cases) {
        Expression test;
        Expression result = test_pls(std::get<1>(p));
        CAPTURE(std::get<0>(p));
        CAPTURE(std::get<1>(p));
        REQUIRE_NOTHROW(test = test_pls(std::get<0>(p)));
        REQUIRE(test == result);
    }

    for (auto const& p : fail_cases) {
        CAPTURE(p);
        REQUIRE_THROWS_AS(test_pls(p), SemanticError);
    }
}
