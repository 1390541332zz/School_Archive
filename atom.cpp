#include "atom.hpp"

#include <sstream>
#include <cctype>
#include <cmath>
#include <limits>

Atom::Atom(): m_type(NoneType) {}

Atom::Atom(std::complex<double> value){
  setNumber(value);
}

Atom::Atom(double value){
  setNumber(value);
}

Atom::Atom(const Token & token): Atom(){
  
  // is token a number?
  double temp;
  std::istringstream iss(token.asString());
  if(iss >> temp){
    // check for trailing characters if >> succeeds
    if(iss.rdbuf()->in_avail() == 0){
      setNumber(temp);
    }
  }
  else{ // else assume symbol
    // make sure does not start with number
    if(!std::isdigit(token.asString()[0])){
      setSymbol(token.asString());
    }
  }
}

Atom::Atom(const std::string & value): Atom() { 
  setSymbol(value);
}

Atom::Atom(const Atom & x): Atom() {
  switch(x.m_type) {
    case ComplexType:
      setNumber(x.num);
      break;
    case DoubleType:
      setNumber(x.num.real());
      break;
    case SymbolType:
      setSymbol(x.str);
      break;
    case NoneType:
      m_type = x.m_type;
      break; 
  }
}

Atom & Atom::operator=(const Atom & x){

  if(this == &x) return *this;
  switch(x.m_type) {
    case ComplexType:
      setNumber(x.num);
      break;
    case DoubleType:
      setNumber(x.num.real());
      break;
    case SymbolType:
      setSymbol(x.str);
      break;
    case NoneType:
      m_type = x.m_type;
      break; 
  }
  return *this;
}
  
Atom::~Atom(){
  // we need to ensure the destructor of the symbol string is called
  if(m_type == SymbolType){
    str.~basic_string();
  }
}

bool Atom::isNone() const noexcept{
  return m_type == NoneType;
}

bool Atom::isNumber() const noexcept{
  return m_type == DoubleType;
}

bool Atom::isComplex() const noexcept{
  return m_type == ComplexType;
}

bool Atom::isSymbol() const noexcept{
  return m_type == SymbolType;
}  

void Atom::setNumber(std::complex<double> value){
  m_type = ComplexType;
  num = value;
}

void Atom::setNumber(double value){
  m_type = DoubleType;
  num = std::complex<double>(value, 0);
}

void Atom::setSymbol(const std::string & value){
  // we need to ensure the destructor of the symbol string is called
  if(m_type == SymbolType){
    str.~basic_string();
  }
  m_type = SymbolType;
  // copy construct in place
  new (&str) std::string(value);
}

std::complex<double> Atom::asComplex() const noexcept{
  switch(m_type) {
    case ComplexType: return num;
    case DoubleType:  return std::complex<double>(num.real(), 0.0);
    default:          return std::complex<double>(0.0, 0.0);
  }
}

double Atom::asNumber() const noexcept {
  switch(m_type) {
    case DoubleType:  
    case ComplexType: return num.real();
    default:          return 0.0;
  }
}

std::string Atom::asSymbol() const noexcept{
  std::string result;

  if(m_type == SymbolType){
    result = str;
  }

  return result;
}

bool Atom::operator==(const Atom & right) const noexcept{
  
  if(m_type != right.m_type) return false;

  switch(m_type){
  case NoneType:
    return (right.m_type == NoneType);
  case ComplexType: case DoubleType:
    {
      if((right.m_type != DoubleType) && (right.m_type != ComplexType)) return false;
      auto l = asComplex(); 
      auto r = right.asComplex(); 
      double lr = l.real();
      double rr = r.real();
      double dr = std::fabs(lr - rr);

      double li = l.imag();
      double ri = r.imag();
      double di = std::fabs(li - ri);

      return (  !std::isnan(dr) 
             && !std::isnan(di) 
	         && (dr <= std::numeric_limits<double>::epsilon())
	         && (di <= std::numeric_limits<double>::epsilon())
             ); 
    }
    break;
  case SymbolType:
    return (right.m_type == SymbolType) && (str == right.str);
  default:
    return false;
  }
}

bool operator!=(const Atom & left, const Atom & right) noexcept{
  
  return !(left == right);
}


std::ostream & operator<<(std::ostream & out, const Atom & a){

  if (a.isComplex()) {
      out << a.asComplex().real() << ',' << a.asComplex().imag();
  } else if(a.isNumber()) {
    out << a.asNumber();
  } else if(a.isSymbol()) {
    out << a.asSymbol();
  }
  return out;
}
