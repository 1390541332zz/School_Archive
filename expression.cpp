#include "expression.hpp"

#include <algorithm>
#include <iostream>
#include <list>
#include <sstream>
#include <type_traits>

#include "environment.hpp"
#include "semantic_error.hpp"

Expression::Expression(Atom const & a) noexcept
    : m_head(a)
{
}

Atom & Expression::head() noexcept
{
    return m_head;
}

Atom const & Expression::head() const noexcept
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

bool Expression::isHeadString() const noexcept
{
    return m_head.isString();
}

bool Expression::isNone() const noexcept
{
    return (m_head.isNone());
}

bool Expression::isList() const noexcept
{
    return (m_head.asSymbol() == "list");
}

bool Expression::isLambda() const noexcept
{
    return (m_head.asSymbol() == "lambda");
}

bool Expression::is(std::string const & str) const noexcept
{
    auto it = pmap.find("object-name");
    if (it == pmap.cend()) {
        return false;
    }
    return (it->second.head().asSymbol() == str);
}

std::size_t Expression::arg_length() const noexcept
{
    return m_tail.size();
}

void Expression::append(Atom const & a)
{
    m_tail.emplace_back(a);
}

void Expression::append(Expression const & e)
{
    m_tail.emplace_back(e);
}

Expression * Expression::tail() noexcept
{
    Expression * ptr = nullptr;

    if (!m_tail.empty()) {
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

Expression apply(Atom const & op, std::vector<Expression> const & args, Environment const & env)
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
         ++arg, ++val) {
        lambda_env.add_exp(arg->head(), *val);
    }
    return exp.eval(lambda_env);
}

Expression Expression::handle_lookup(Atom const & head, Environment const & env)
{
    if (head.isString()) { // if string is in env return value
        return Expression(head);
    }
    if (head.isSymbol()) { // if symbol is in env return value
        if (!env.is_exp(head) && !env.is_proc(head)) {
            throw SemanticError("Error during evaluation: unknown symbol");
        }
        if (!env.is_exp(head)) {
            return Expression(head);
        }
        return env.get_exp(head);
    }
    if (head.isNumber()) {
        return Expression(head);
    }
    throw SemanticError("Error during evaluation: Invalid type in terminal expression");
}

Expression Expression::handle_begin(Environment & env)
{
    // Unreachable Error
    //if (m_tail.empty()) {
    //    throw SemanticError("Error during evaluation: zero arguments to begin");
    //}

    // evaluate each arg from tail, return the last
    Expression result;
    std::for_each(m_tail.begin(), m_tail.end(), [&result, &env](Expression & e) {
        result = e.eval(env);
    });

    return result;
}

Expression Expression::handle_define(Environment & env)
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

    // eval tail[1]
    Expression result = m_tail[1].eval(env);
    //and add to env
    env.add_exp(m_tail[0].head(), result);

    return result;
}

Expression Expression::handle_lambda(Environment & env)
{
    if (m_tail.size() != 2) {
        throw SemanticError("Error during evaluation: invalid number of arguments to lambda");
    }

    // tail[0] must be a list of arguments
    if (std::any_of(m_tail[0].tailConstBegin(),
            m_tail[0].tailConstEnd(),
            [&env](Expression const & e) {
                return (!e.isHeadSymbol()
                    || e.isList()
                    || (e.head().asSymbol() == "begin")
                    || (e.head().asSymbol() == "define")
                    || env.is_proc(e.head()));
            })) {
        throw SemanticError("Error during evaluation: the first argument must be a list of function arguments.");
    }
    std::string const s = "lambda";
    Expression expr(s);
    Expression args = Atom("list");
    if (m_tail[0].arg_length() > 0) {
        args.append(Expression(m_tail[0].head()));
        for (auto it = m_tail[0].tailConstBegin();
             it != m_tail[0].tailConstEnd();
             ++it) {
            args.append(it->head());
        }
        expr.append(args);
    } else {
        args.append(m_tail[0]);
        expr.append(args);
    }
    expr.append(m_tail[1]);
    return expr;
}

Expression Expression::handle_setprop(Environment & env)
{
    if (m_tail.size() != 3) {
        throw SemanticError("Error during evaluation: invalid number of arguments to set-property");
    }
    if (!m_tail[0].isHeadString()) {
        throw SemanticError("Error: first argument to set-property not a string");
    }
    auto exp = m_tail[2];
    auto e = exp.eval(env);
    auto prop = m_tail[1];
    if (!prop.isLambda()) {
        prop = prop.eval(env);
    }
    e.pmap[m_tail[0].head().asSymbol()] = prop;
    return e;
}

Expression Expression::handle_getprop(Environment & env)
{
    if (m_tail.size() != 2) {
        throw SemanticError("Error during evaluation: invalid number of arguments to get-property");
    }
    if (!m_tail[0].isHeadString()) {
        throw SemanticError("Error: first argument to get-property not a string");
    }
    auto exp = m_tail[1].eval(env);
    auto f = exp.pmap.find(m_tail[0].head().asSymbol());
    if (f != exp.pmap.end()) {
        return f->second.eval(env);
    }
    return Expression(Atom());
}

// this is a simple recursive version. the iterative version is more
// difficult with the ast data structure used (no parent pointer).
// this limits the practical depth of our AST
Expression Expression::eval(Environment & env)
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
    // handle property special-forms
    if (m_head.isSymbol() && m_head.asSymbol() == "get-property") {
        return handle_getprop(env);
    }
    if (m_head.isSymbol() && m_head.asSymbol() == "set-property") {
        return handle_setprop(env);
    }
    // else attempt to treat as procedure
    std::vector<Expression> res;
    res.reserve(m_tail.size());
    std::for_each(m_tail.begin(), m_tail.end(), [&env, &res](Expression e) {
        res.push_back(e.eval(env));
    });
    std::for_each(res.begin(), res.end(), [&env](Expression & e) {
        e.scope = &env;
    });
    return apply(m_head, res, env);
}

std::ostream & operator<<(std::ostream & out, Expression const & exp)
{

    if (exp.isNone()) {
        out << exp.head();
        return out;
    }
    out << '(';
    if (!exp.isList() && !exp.isLambda()) {
        out << exp.head();
    }
    for (auto e = exp.tailConstBegin(); e != exp.tailConstEnd(); ++e) {
        if ((!exp.isList() && !exp.isLambda()) || (e != exp.tailConstBegin())) {
            out << ' ';
        }
        out << *e;
    }

    out << ')';
    return out;
}

bool Expression::operator==(Expression const & exp) const noexcept
{
    if ((m_head != exp.m_head) || (m_tail.size() != exp.m_tail.size())) {
        return false;
    }
    return std::equal(m_tail.cbegin(), m_tail.cend(), exp.m_tail.cbegin());
}

bool operator!=(Expression const & left, Expression const & right) noexcept
{

    return !(left == right);
}
