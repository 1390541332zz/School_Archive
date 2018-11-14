/*! \file expression.hpp
Defines the Expression type and assiciated functions.
 */
#ifndef EXPRESSION_HPP
#define EXPRESSION_HPP

#include <map>
#include <string>
#include <vector>

#include "atom.hpp"
#include "token.hpp"

// forward declare Environment
class Environment;
class OutputWidget;

/*! \class Expression
\brief An expression is a tree of Atoms.

An expression is an atom called the head followed by a (possibly empty) 
list of expressions called the tail.
 */
class Expression {
    friend OutputWidget;
public:
    typedef std::vector<Expression>::const_iterator ConstIteratorType;

    /// Default construct and Expression, whose type in NoneType
    Expression();

    /*! Construct an Expression with given Atom as head an empty tail
    \param atom the atom to make the head
  */
    Expression(const Atom& a);

    /// deep-copy construct an expression (recursive)
    Expression(const Expression& a);

    /// list constructor
    template <typename it,
        typename = typename std::enable_if<
            std::is_same<
                typename std::iterator_traits<it>::value_type,
                Expression>::value>::type>
    Expression(it const& begin, it const& end)
    {
        m_head = Atom("list");
        for (auto e = begin; e != end; ++e) {
            m_tail.push_back(*e);
        }
    }
    /// deep-copy assign an expression  (recursive)
    Expression& operator=(const Expression& a);

    /// return a reference to the head Atom
    Atom& head();

    /// return a const-reference to the head Atom
    const Atom& head() const;

    /// append Atom to tail of the expression
    void append(const Atom& a);

    /// append Expression to tail of the expression
    void append(const Expression& e);

    /// return a pointer to the last expression in the tail, or nullptr
    Expression* tail();

    /// return a const-iterator to the beginning of tail
    ConstIteratorType tailConstBegin() const noexcept;

    /// return a const-iterator to the tail end
    ConstIteratorType tailConstEnd() const noexcept;

    /// convienience member to determine if head atom is a number
    bool isHeadComplex() const noexcept;

    /// convienience member to determine if head atom is a number
    bool isHeadNumber() const noexcept;

    /// convienience member to determine if head atom is a symbol
    bool isHeadSymbol() const noexcept;

    /// convienience member to determine if head atom is a string
    bool isHeadString() const noexcept;

    /// convienience member to determine if expression is a list
    bool isList() const noexcept;

    /// convienience member to determine if expression is a lambda
    bool isLambda() const noexcept;
    
    /// convienience member to determine if expression is the type defined by 'str'
    bool is(std::string const & str) const noexcept;

    /// convienience member to determine if expression is a NONE
    bool isNone() const noexcept;

    /// convienience member to determine length of arguments
    std::size_t arg_length() const noexcept;

    /// Evaluate expression using a post-order traversal (recursive)
    Expression eval(Environment& env);

    /// equality comparison for two expressions (recursive)
    bool operator==(const Expression& exp) const noexcept;

    // Scope pointer for combinators
    Environment* scope = nullptr;

private:
    // the head of the expression
    Atom m_head;

    // the tail list is expressed as a vector for access efficiency
    // and cache coherence, at the cost of wasted memory.
    std::vector<Expression> m_tail;

    // property map
    std::map<std::string, Expression> pmap;

    // convenience typedef
    typedef std::vector<Expression>::iterator IteratorType;

    // internal helper methods
    Expression handle_lookup(const Atom& head, const Environment& env);
    Expression handle_define(Environment& env);
    Expression handle_begin(Environment& env);
    Expression handle_lambda(Environment& env);
    Expression handle_getprop(Environment& env);
    Expression handle_setprop(Environment& env);
};

/// Render expression to output stream
std::ostream& operator<<(std::ostream& out, const Expression& exp);

/// inequality comparison for two expressions (recursive)
bool operator!=(const Expression& left, const Expression& right) noexcept;

#endif
