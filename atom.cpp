#include "atom.hpp"

#include <cctype>
#include <cmath>
#include <limits>
#include <sstream>

Atom::Atom() noexcept
    : num(0, 0)
{
}

Atom::Atom(std::complex<double> value) noexcept
{
    setNumber(value);
}

Atom::Atom(double value) noexcept
{
    setNumber(value);
}

Atom::Atom(Token const & token) noexcept
    : Atom()
{
    // is token a number?
    double temp;
    std::istringstream iss(token.asString());
    if (iss >> temp) {
        // check for trailing characters if >> succeeds
        if (iss.rdbuf()->in_avail() == 0) {
            setNumber(temp);
        }
    } else if (std::isdigit(token.asString()[0]) == 0) {
        std::string str = token.asString();
        if ((str.front() == '"') && (str.back() == '"')) {
            auto x = str.substr(1, str.size() - 2);
            setString(x);
        } else {
            setSymbol(str);
        }
    }
}

Atom::Atom(std::string const & value) noexcept
    : Atom()
{
    setSymbol(value);
}

Atom::Atom(Atom const & x) noexcept
    : Atom()
{
    switch (x.m_type) {
    case ComplexType:
        setNumber(x.num);
        break;
    case DoubleType:
        setNumber(x.num.real());
        break;
    case SymbolType:
        setSymbol(x.str);
        break;
    case StringType:
        setString(x.str);
        break;
    case NoneType:
        m_type = x.m_type;
        break;
    }
}

Atom::Atom(Atom && x) noexcept
{
    switch (x.m_type) {
    case NoneType:
        m_type = NoneType;
        break;
    case ComplexType:
        m_type = ComplexType;
        num = x.num;
        break;
    case DoubleType:
        m_type = DoubleType;
        num = x.num;
        break;
    case SymbolType:
        m_type = SymbolType;
        new (&str) std::string(x.str);
        break;
    case StringType:
        m_type = StringType;
        new (&str) std::string(x.str);
        break;
    }
}

Atom & Atom::operator=(Atom const & x) noexcept
{

    if (this == &x) {
        return *this;
    }
    switch (x.m_type) {
    case ComplexType:
        setNumber(x.num);
        break;
    case DoubleType:
        setNumber(x.num.real());
        break;
    case SymbolType:
        setSymbol(x.str);
        break;
    case StringType:
        setString(x.str);
        break;
    case NoneType:
        m_type = x.m_type;
        break;
    }
    return *this;
}

Atom & Atom::operator=(Atom && x) noexcept
{

    if (this == &x) {
        return *this;
    }
    switch (x.m_type) {
    case NoneType:
        m_type = NoneType;
        break;
    case ComplexType:
        m_type = ComplexType;
        num = x.num;
        break;
    case DoubleType:
        m_type = DoubleType;
        num = x.num;
        break;
    case SymbolType:
        m_type = SymbolType;
        new (&str) std::string(x.str);
        break;
    case StringType:
        m_type = StringType;
        new (&str) std::string(x.str);
        break;
    }
    x.m_type = NoneType;
    return *this;
}

Atom::~Atom()
{
    // we need to ensure the destructor of the symbol string is called
    if ((m_type == StringType) || (m_type == SymbolType)) {
        str.~basic_string();
    }
}

bool Atom::isNone() const noexcept
{
    return m_type == NoneType;
}

bool Atom::isNumber() const noexcept
{
    return m_type == DoubleType;
}

bool Atom::isComplex() const noexcept
{
    return m_type == ComplexType;
}

bool Atom::isSymbol() const noexcept
{
    return m_type == SymbolType;
}

bool Atom::isString() const noexcept
{
    return m_type == StringType;
}

void Atom::setNumber(std::complex<double> value) noexcept
{
    m_type = ComplexType;
    num = value;
}

void Atom::setNumber(double value) noexcept
{
    m_type = DoubleType;
    num = std::complex<double>(value, 0);
}

void Atom::setSymbol(std::string const & value) noexcept
{
    // we need to ensure the destructor of the symbol string is called
    if ((m_type == StringType) || (m_type == SymbolType)) {
        str.~basic_string();
    }
    m_type = SymbolType;
    // copy construct in place
    new (&str) std::string(value);
}

void Atom::setString(std::string const & value) noexcept
{
    setSymbol(value);
    m_type = StringType;
}

std::complex<double> Atom::asComplex() const noexcept
{
    switch (m_type) {
    case ComplexType:
        return num;
    case DoubleType:
        return { num.real(), 0.0 };
    default:
        return { 0.0, 0.0 };
    }
}

double Atom::asNumber() const noexcept
{
    switch (m_type) {
    case DoubleType:
    case ComplexType:
        return num.real();
    default:
        return 0.0;
    }
}

std::string Atom::asSymbol() const noexcept
{
    std::string result;

    if ((m_type == SymbolType) || (m_type == StringType)) {
        result = str;
    }

    return result;
}

bool Atom::operator==(Atom const & right) const noexcept
{

    if (m_type != right.m_type) {
        return false;
    }

    switch (m_type) {
    case NoneType:
        return (right.m_type == NoneType);
    case ComplexType:
    case DoubleType: {
        if ((right.m_type != DoubleType) && (right.m_type != ComplexType)) {
            return false;
        }
        auto l = asComplex();
        auto r = right.asComplex();
        double lr = l.real();
        double rr = r.real();
        double dr = std::fabs(lr - rr);

        double li = l.imag();
        double ri = r.imag();
        double di = std::fabs(li - ri);

        return (!std::isnan(dr)
            && !std::isnan(di)
            && (dr <= std::numeric_limits<float>::epsilon())
            && (di <= std::numeric_limits<float>::epsilon()));
    };
    case StringType:
        return (right.m_type == StringType) && (str == right.str);
    case SymbolType:
        return (right.m_type == SymbolType) && (str == right.str);
    default:
        return false;
    }
}

bool operator!=(Atom const & left, Atom const & right) noexcept
{

    return !(left == right);
}

std::ostream & operator<<(std::ostream & out, Atom const & a)
{

    if (a.isComplex()) {
        out << a.asComplex().real() << ',' << a.asComplex().imag();
    } else if (a.isNumber()) {
        out << a.asNumber();
    } else if (a.isSymbol()) {
        out << a.asSymbol();
    } else if (a.isString()) {
        out << '"' << a.asSymbol() << '"';
    } else if (a.isNone()) {
        out << "NONE";
    }
    return out;
}
