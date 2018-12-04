/*! \file atom.hpp
Defines the Atom type and associated functions.
 */
#ifndef ATOM_HPP
#define ATOM_HPP

#include "token.hpp"
#include <complex>

/*! \class Atom
\brief A variant type that may be a Number or Symbol or the default type None.

This class provides value semantics.
*/
class Atom {
public:
    /// Construct a default Atom of type None
    Atom() noexcept;

    /// Construct an Atom of type Number with value
    Atom(double value) noexcept;

    /// Construct an Atom of type Number with value
    Atom(std::complex<double> value) noexcept;

    /// Construct an Atom of type Symbol named value
    Atom(std::string const & value) noexcept;

    /// Construct an Atom directly from a Token
    Atom(Token const & token) noexcept;

    /// Copy-construct an Atom
    Atom(Atom const & x) noexcept;

    /// Move-construct an Atom
    Atom(Atom && x) noexcept;

    /// Copy Assign an Atom
    Atom & operator=(Atom const & x) noexcept;

    /// Move Assign an Atom
    Atom & operator=(Atom && x) noexcept;

    /// Atom destructor
    ~Atom();

    /// predicate to determine if an Atom is of type None
    bool isNone() const noexcept;

    /// predicate to determine if an Atom is of type Number
    bool isNumber() const noexcept;

    /// predicate to determine if an Atom is of type Number and Complex
    bool isComplex() const noexcept;

    /// predicate to determine if an Atom is of type String
    bool isString() const noexcept;

    /// predicate to determine if an Atom is of type Symbol
    bool isSymbol() const noexcept;

    /// value of Atom as a real number, return 0 if not a Number
    double asNumber() const noexcept;

    /// value of Atom as a complex number, return 0 if not a Number
    std::complex<double> asComplex() const noexcept;

    /// value of Atom as a number, returns empty-string if not a Symbol
    std::string asSymbol() const noexcept;

    /// equality comparison based on type and value
    bool operator==(Atom const & right) const noexcept;

private:
    // internal enum of known types
    enum Type {
        NoneType    = 0,
        DoubleType  = 1,
        StringType  = 2,
        SymbolType  = 3,
        ComplexType = 4
    };

    // track the type
    Type m_type = NoneType;

    // values for the known types. Note the use of a union requires care
    // when setting non POD values (see setSymbol)
    union {
        std::complex<double> num;
        std::string str;
    };

    // helper to set type and value of Number
    void setNumber(std::complex<double> value) noexcept;

    // helper to set type and value of Number
    void setNumber(double value) noexcept;

    // helper to set type and value of Symbol
    void setSymbol(std::string const & value) noexcept;

    // helper to set type and value of String
    void setString(std::string const & value) noexcept;
};

/// inequality comparison for Atom
bool operator!=(Atom const & left, Atom const & right) noexcept;

/// output stream rendering
std::ostream & operator<<(std::ostream & out, Atom const & a);

#endif
