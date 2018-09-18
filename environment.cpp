#include <cassert>
#include <cmath>
#include <complex>
#include <limits>

#include "environment.hpp"
#include "semantic_error.hpp"

/*********************************************************************** 
Helper Functions
**********************************************************************/

// predicate, the number of args is nargs
bool nargs_equal(const std::vector<Expression> & args, unsigned nargs){
  return args.size() == nargs;
}

bool anyargs_complex(const std::vector<Expression> & args) {
  for (auto const & x : args) {
    if (x.isHeadComplex()) return true;
  }
  return false;
}

bool isComplex(std::complex<double> x) {
  double absi = std::abs(x.imag());
  return (  !std::isnan(absi) 
         && (absi >= std::numeric_limits<double>::epsilon())
         );
}

/*********************************************************************** 
Each of the functions below have the signature that corresponds to the
typedef'd Procedure function pointer.
**********************************************************************/

double const PI = std::atan2(0, -1);
double const EXP = std::exp(1);
std::complex<double> const IMAG(0, 1);

// the default procedure always returns an expresison of type None
Expression default_proc(const std::vector<Expression> & args){
  args.size(); // make compiler happy we used this parameter
  return Expression();
}

Expression add(const std::vector<Expression> & args){
  // check all aruments are numbers, while adding
  std::complex<double> result(0, 0);
  for( auto & a :args) {
    if(!a.isHeadNumber() && !a.isHeadComplex()) {
      throw SemanticError("Error in call to add, argument not a number");
    }
    result += a.head().asComplex();
  }
  if (anyargs_complex(args)) return Expression(result);
  return Expression(result.real());
}

Expression mul(const std::vector<Expression> & args) { 
  // check all aruments are numbers, while multiplying
  std::complex<double> result(1, 0);
  for( auto & a :args) {
    if (!a.isHeadNumber() && !a.isHeadComplex()) {
      throw SemanticError("Error in call to mul, argument not a number");
    }
    result *= a.head().asComplex();
  }

  if (anyargs_complex(args)) return Expression(result);
  return Expression(result.real());
}

Expression subneg(const std::vector<Expression> & args){
  std::complex<double> result(0, 0);

  // preconditions
  if ( nargs_equal(args,1) ) {
    if (!args[0].isHeadNumber() && !args[0].isHeadComplex()) {
      throw SemanticError("Error in call to negate: invalid argument.");
    }
    result = -args[0].head().asComplex();
  }
  else if (nargs_equal(args,2)){
    if(  (!args[0].isHeadNumber() && !args[0].isHeadComplex()) 
      || (!args[1].isHeadNumber() && !args[1].isHeadComplex()) ){
      throw SemanticError("Error in call to subtraction: invalid argument.");
    }
    result = args[0].head().asComplex() - args[1].head().asComplex();
  }
  else {
    throw SemanticError("Error in call to subtraction or negation: invalid number of arguments.");
  }

  if (anyargs_complex(args)) return Expression(result);
  return Expression(result.real());
}

Expression div(const std::vector<Expression> & args) {
  if (!nargs_equal(args,2)) {
    throw SemanticError("Error in call to division: invalid number of arguments.");
  }
  if(  (!args[0].isHeadNumber() && !args[0].isHeadComplex()) 
    || (!args[1].isHeadNumber() && !args[1].isHeadComplex()) ){
    throw SemanticError("Error in call to division: invalid argument.");
  }
  
  auto result = args[0].head().asComplex() / args[1].head().asComplex();
  if (anyargs_complex(args)) return Expression(result);
  return Expression(result.real());
}

Expression pow(const std::vector<Expression> & args){
  if (!nargs_equal(args,2)) {
    throw SemanticError("Error in call to power: invalid number of arguments.");
  }
  if(  (!args[0].isHeadNumber() && !args[0].isHeadComplex()) 
    || (!args[1].isHeadNumber() && !args[1].isHeadComplex()) ){
    throw SemanticError("Error in call to power: invalid argument.");
  }
  
  auto result = std::pow(args[0].head().asComplex(), args[1].head().asComplex());
  if (anyargs_complex(args)) return Expression(result);
  return Expression(result.real());
}

Expression sqrt(const std::vector<Expression> & args){
  if (!nargs_equal(args,1)) {
    throw SemanticError("Error in call to square root: invalid number of arguments.");
  }
  if (!args[0].isHeadNumber() && !args[0].isHeadComplex()) {
    throw SemanticError("Error in call to square root: invalid argument.");
  }
  
  auto result = std::sqrt(args[0].head().asComplex());
  if (args[0].isHeadComplex() || isComplex(result)) return Expression(result);
  return Expression(result.real());
}

Expression natlog(const std::vector<Expression> & args){
  
  if (!nargs_equal(args,1)) {
    throw SemanticError("Error in call to natural log: invalid number of arguments.");
  }
  if (  (!args[0].isHeadNumber() && !args[0].isHeadComplex()) 
     || (std::abs(args[0].head().asComplex()) == 0)) {
    throw SemanticError("Error in call to natural log: invalid argument.");
  }
  
  auto result = std::log(args[0].head().asComplex());
  if (args[0].isHeadComplex() || isComplex(result)) return Expression(result);
  return Expression(result.real());
}

Expression sin(const std::vector<Expression> & args){
  
  if (!nargs_equal(args,1)) {
    throw SemanticError("Error in call to sin: invalid number of arguments.");
  }
  if (!args[0].isHeadNumber() && !args[0].isHeadComplex()) {
    throw SemanticError("Error in call to sin: invalid argument.");
  }
  
  auto result = std::sin(args[0].head().asComplex());
  if (args[0].isHeadComplex()) return Expression(result);
  return Expression(result.real());
}

Expression cos(const std::vector<Expression> & args){
  if (!nargs_equal(args,1)) {
    throw SemanticError("Error in call to cos: invalid number of arguments.");
  }
  if (!args[0].isHeadNumber() && !args[0].isHeadComplex()) {
    throw SemanticError("Error in call to cos: invalid argument.");
  }
  
  auto result = std::cos(args[0].head().asComplex());
  if (args[0].isHeadComplex()) return Expression(result);
  return Expression(result.real());
}

Expression tan(const std::vector<Expression> & args){
  
  if (!nargs_equal(args,1)) {
    throw SemanticError("Error in call to tan: invalid number of arguments.");
  }
  if (!args[0].isHeadNumber() && !args[0].isHeadComplex()) {
    throw SemanticError("Error in call to tan: invalid argument.");
  }
  
  auto result = std::tan(args[0].head().asComplex());
  if (args[0].isHeadComplex() || isComplex(result)) return Expression(result);
  return Expression(result.real());
}

Expression real(const std::vector<Expression> & args) {
  if (!nargs_equal(args,1)) {
    throw SemanticError("Error in call to real: invalid number of arguments.");
  }
  if (!(args[0].isHeadComplex())) {
    throw SemanticError("Error in call to real: non-complex argument.");
  }

  auto result = std::real(args[0].head().asComplex());
  return Expression(result);
}

Expression imag(const std::vector<Expression> & args) {
  if (!nargs_equal(args,1)) {
    throw SemanticError("Error in call to imag: invalid number of arguments.");
  }
  if (!(args[0].isHeadComplex())) {
    throw SemanticError("Error in call to imag: non-complex argument.");
  }

  auto result = std::imag(args[0].head().asComplex());
  return Expression(result);
}

Expression mag(const std::vector<Expression> & args) {
  if (!nargs_equal(args,1)) {
    throw SemanticError("Error in call to mag: invalid number of arguments.");
  }
  if (!(args[0].isHeadComplex())) {
    throw SemanticError("Error in call to mag: non-complex argument.");
  }

  auto result = std::abs(args[0].head().asComplex());
  return Expression(result);
}

Expression arg(const std::vector<Expression> & args) {
  if (!nargs_equal(args,1)) {
    throw SemanticError("Error in call to arg: invalid number of arguments.");
  }
  if (!(args[0].isHeadComplex())) {
    throw SemanticError("Error in call to arg: non-complex argument.");
  }

  auto result = std::arg(args[0].head().asComplex());
  return Expression(result);
}

Expression conj(const std::vector<Expression> & args) {
  if (!nargs_equal(args,1)) {
    throw SemanticError("Error in call to conj: invalid number of arguments.");
  }
  if (!(args[0].isHeadComplex())) {
    throw SemanticError("Error in call to conj: non-complex argument.");
  }

  auto result = std::conj(args[0].head().asComplex());
  return Expression(result);
}


Environment::Environment(){
  reset();
}

bool Environment::is_known(const Atom & sym) const{
  if(!sym.isSymbol()) return false;
  
  return envmap.find(sym.asSymbol()) != envmap.end();
}

bool Environment::is_exp(const Atom & sym) const{
  if(!sym.isSymbol()) return false;
  
  auto result = envmap.find(sym.asSymbol());
  return (result != envmap.end()) && (result->second.type == ExpressionType);
}

Expression Environment::get_exp(const Atom & sym) const{

  Expression exp;
  
  if(sym.isSymbol()){
    auto result = envmap.find(sym.asSymbol());
    if((result != envmap.end()) && (result->second.type == ExpressionType)){
      exp = result->second.exp;
    }
  }

  return exp;
}

void Environment::add_exp(const Atom & sym, const Expression & exp){

  if(!sym.isSymbol()){
    throw SemanticError("Attempt to add non-symbol to environment");
  }
    
  // error if overwriting symbol map
  if(envmap.find(sym.asSymbol()) != envmap.end()){
    throw SemanticError("Attempt to overwrite symbol in environemnt");
  }

  envmap.emplace(sym.asSymbol(), EnvResult(ExpressionType, exp)); 
}

bool Environment::is_proc(const Atom & sym) const{
  if(!sym.isSymbol()) return false;
  
  auto result = envmap.find(sym.asSymbol());
  return (result != envmap.end()) && (result->second.type == ProcedureType);
}

Procedure Environment::get_proc(const Atom & sym) const{

  //Procedure proc = default_proc;

  if(sym.isSymbol()){
    auto result = envmap.find(sym.asSymbol());
    if((result != envmap.end()) && (result->second.type == ProcedureType)){
      return result->second.proc;
    }
  }

  return default_proc;
}

/*
Reset the environment to the default state. First remove all entries and
then re-add the default ones.
 */
void Environment::reset(){

  envmap.clear();
  
  // Built-In value of pi
  envmap.emplace("pi", EnvResult(ExpressionType, Expression(PI)));

  // Built-In value of exp
  envmap.emplace("e", EnvResult(ExpressionType, Expression(EXP)));

  // Built-In value of imaginary i
  envmap.emplace("I", EnvResult(ExpressionType, Expression(IMAG)));

  // Procedure: add;
  envmap.emplace("+", EnvResult(ProcedureType, add)); 

  // Procedure: subneg;
  envmap.emplace("-", EnvResult(ProcedureType, subneg)); 

  // Procedure: mul;
  envmap.emplace("*", EnvResult(ProcedureType, mul)); 

  // Procedure: div;
  envmap.emplace("/", EnvResult(ProcedureType, div)); 
  
  // Procedure: power;
  envmap.emplace("^", EnvResult(ProcedureType, pow)); 
  
  // Procedure: square root;
  envmap.emplace("sqrt", EnvResult(ProcedureType, sqrt)); 
  
  // Procedure: natura log;
  envmap.emplace("ln", EnvResult(ProcedureType, natlog)); 
  
  // Procedure: sin;
  envmap.emplace("sin", EnvResult(ProcedureType, sin)); 
  
  // Procedure: cos;
  envmap.emplace("cos", EnvResult(ProcedureType, cos)); 
  
  // Procedure: tan;
  envmap.emplace("tan", EnvResult(ProcedureType, tan)); 
  
  // Procedure: real;
  envmap.emplace("real", EnvResult(ProcedureType, real)); 
  
  // Procedure: imag;
  envmap.emplace("imag", EnvResult(ProcedureType, imag));

  // Procedure: mag;
  envmap.emplace("mag", EnvResult(ProcedureType, mag)); 
  
  // Procedure: arg;
  envmap.emplace("arg", EnvResult(ProcedureType, arg)); 

  // Procedure: conj;
  envmap.emplace("conj", EnvResult(ProcedureType, conj)); 
}
