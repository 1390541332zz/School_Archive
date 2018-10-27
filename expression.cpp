#include "expression.hpp"

#include <list>
#include <iostream>
#include <sstream>
#include <type_traits>
#include <algorithm>

#include "environment.hpp"
#include "semantic_error.hpp"

Expression::Expression() {}

Expression::Expression(const Atom& a)
{
    m_head = a;
}

// recursive copy
Expression::Expression(const Expression& a)
{
    m_head = a.m_head;
    scope = a.scope;
    for (auto e : a.m_tail) {
        m_tail.push_back(e);
    }
}

Expression& Expression::operator=(const Expression& a)
{
    if (this == &a)
        return *this;
    m_head = a.m_head;
    scope = a.scope;
    m_tail.clear();
    for (auto e : a.m_tail) {
        m_tail.push_back(e);
    }
    return *this;
}

Atom& Expression::head()
{
    return m_head;
}

const Atom& Expression::head() const
{
    return m_head;
}

bool Expression::isHeadComplex() const noexcept
{
    return m_head.isComplex();
}

bool Expression::isHeadNumber() const noexcept
{
    return m_head.isNumber();
}

bool Expression::isHeadSymbol() const noexcept
{
    return m_head.isSymbol();
}

bool Expression::isList() const noexcept
{
    return (m_head.asSymbol() == "list");
}

bool Expression::isLambda() const noexcept
{
    return (m_head.asSymbol() == "lambda");
}

std::size_t Expression::arg_length() const noexcept
{
    return m_tail.size();
}

void Expression::append(const Atom& a)
{
    m_tail.emplace_back(a);
}

void Expression::append(const Expression& e)
{
    m_tail.emplace_back(e);
}

Expression* Expression::tail()
{
    Expression* ptr = nullptr;

    if (m_tail.size() > 0) {
        ptr = &m_tail.back();
    }

    return ptr;
}

Expression::ConstIteratorType Expression::tailConstBegin() const noexcept
{
    return m_tail.cbegin();
}

Expression::ConstIteratorType Expression::tailConstEnd() const noexcept
{
    return m_tail.cend();
}

Expression apply(const Atom& op, const std::vector<Expression>& args, const Environment& env)
{
    // head must be a symbol
    if (!op.isSymbol()) {
        throw SemanticError("Error during evaluation: procedure name not symbol");
    }

    // must map to a proc
    if (!env.is_proc(op) && !(env.get_exp(op).isLambda())) {
        throw SemanticError("Error during evaluation: symbol does not name a procedure");
    }

    if (env.is_proc(op)) {
        // map from symbol to proc
        Procedure proc = env.get_proc(op);
        // call proc with args
        return proc(args);
    }
    Environment lambda_env;
    auto lambda_expr = env.get_exp(op);
    auto exp = *std::next(lambda_expr.tailConstBegin());
    auto val = args.cbegin();
    lambda_env.parent = &env;
    lambda_env.reset();
    for (auto arg = lambda_expr.tailConstBegin()->tailConstBegin(); 
             arg != lambda_expr.tailConstBegin()->tailConstEnd();
         ++arg, ++val) 
    {
        lambda_env.add_exp(arg->head(), *val);
    }
    return exp.eval(lambda_env);
}

Expression Expression::handle_lookup(const Atom& head, const Environment& env)
{
    if (head.isSymbol()) { // if symbol is in env return value
        if (!env.is_exp(head) && !env.is_proc(head)) {
            throw SemanticError("Error during evaluation: unknown symbol");
        }
        if (!env.is_exp(head)) {
            return Expression(head);
        } 
        return env.get_exp(head);
    } else if (head.isNumber()) {
        return Expression(head);
    } else {
        throw SemanticError("Error during evaluation: Invalid type in terminal expression");
    }
}

Expression Expression::handle_begin(Environment& env)
{

    if (m_tail.size() == 0) {
        throw SemanticError("Error during evaluation: zero arguments to begin");
    }

    // evaluate each arg from tail, return the last
    Expression result;
    for (Expression::IteratorType it = m_tail.begin(); it != m_tail.end(); ++it) {
        result = it->eval(env);
    }

    return result;
}

Expression Expression::handle_define(Environment& env)
{

    // tail must have size 3 or error
    if (m_tail.size() != 2) {
        throw SemanticError("Error during evaluation: invalid number of arguments to define");
    }

    // tail[0] must be symbol
    if (!m_tail[0].isHeadSymbol()) {
        throw SemanticError("Error during evaluation: first argument to define not symbol");
    }

    // but tail[0] must not be a special-form or procedure
    std::string s = m_tail[0].head().asSymbol();
    if ((s == "define") || (s == "begin")) {
        throw SemanticError("Error during evaluation: attempt to redefine a special-form");
    }

    if (env.is_proc(m_head)) {
        throw SemanticError("Error during evaluation: attempt to redefine a built-in procedure");
    }

    // eval tail[1]
    Expression result = m_tail[1].eval(env);

    if (env.is_exp(m_head)) {
        throw SemanticError("Error during evaluation: attempt to redefine a previously defined symbol");
    }

    //and add to env
    env.add_exp(m_tail[0].head(), result);

    return result;
}

Expression Expression::handle_lambda(Environment& env)
{
    if (m_tail.size() != 2) {
        throw SemanticError("Error during evaluation: invalid number of arguments to lambda");
    }

    // tail[0] must be a list of arguments
    if (std::any_of(m_tail[0].tailConstBegin(), 
                    m_tail[0].tailConstEnd(), 
                    [&env] (Expression const & e) {
              return (   !e.isHeadSymbol() 
                      || e.isList()
                      || (e.head().asSymbol() == "begin")
                      || (e.head().asSymbol() == "define")
                      || env.is_proc(e.head())
                     );
          })
    ) {
        throw SemanticError("Error during evaluation: the first argument must be a list of function arguments.");
    }
    std::string const s = "lambda";
    Expression expr(s);
    Expression e;
    if (m_tail[0].arg_length() > 0) {
        e.append(Expression(m_tail[0].head()));
        for (auto it = m_tail[0].tailConstBegin(); 
                 it != m_tail[0].tailConstEnd();
             ++it) 
        {
            e.append(it->head());
        }
        expr.append(e);
    } else {
        e.append(m_tail[0]);
        expr.append(e);
    }
    expr.append(m_tail[1]);
    return expr;
}

// this is a simple recursive version. the iterative version is more
// difficult with the ast data structure used (no parent pointer).
// this limits the practical depth of our AST
Expression Expression::eval(Environment& env)
{
    if (m_tail.empty() && (m_head.asSymbol() != "list")) {
        return handle_lookup(m_head, env);
    }
    // handle begin special-form
    if (m_head.isSymbol() && m_head.asSymbol() == "begin") {
        return handle_begin(env);
    }
    // handle define special-form
    if (m_head.isSymbol() && m_head.asSymbol() == "define") {
        return handle_define(env);
    }
    // handle lambda special-form
    if (m_head.isSymbol() && m_head.asSymbol() == "lambda") {
        return handle_lambda(env);
    }
    // else attempt to treat as procedure
    std::vector<Expression> results;
    for (Expression::IteratorType it = m_tail.begin(); it != m_tail.end(); ++it) {
        results.push_back(it->eval(env));
    }
    for (auto & x : results) {
        x.scope = &env;
    }
    return apply(m_head, results, env);

}

std::ostream& operator<<(std::ostream& out, const Expression& exp)
{

    out << '(';
    if (!exp.isList()) {
        out << exp.head();
    }
    for (auto e = exp.tailConstBegin(); e != exp.tailConstEnd(); ++e) {
        if (exp.isList() && (e != exp.tailConstBegin())) {
            out << ' ';
        }
        out << *e;
    }

    out << ')';
    return out;
}

bool Expression::operator==(const Expression& exp) const noexcept
{
    if ((m_head != exp.m_head) || (m_tail.size() != exp.m_tail.size())) {
        return false;
    }

    for (auto l = m_tail.begin(), r = exp.m_tail.begin();
         (l != m_tail.end()) && (r != exp.m_tail.end());
         ++l, ++r) {
        if (*l != *r)
            return false;
    }
    return true;
}

bool operator!=(const Expression& left, const Expression& right) noexcept
{

    return !(left == right);
}
