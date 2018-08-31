#include <cassert>
#include <cmath>

#include "environment.hpp"
#include "semantic_error.hpp"

/*********************************************************************** 
Helper Functions
**********************************************************************/

// predicate, the number of args is nargs
bool nargs_equal(const std::vector<Expression> & args, unsigned nargs){
  return args.size() == nargs;
}

/*********************************************************************** 
Each of the functions below have the signature that corresponds to the
typedef'd Procedure function pointer.
**********************************************************************/

double const PI = std::atan2(0, -1);
double const EXP = std::exp(1);

// the default procedure always returns an expresison of type None
Expression default_proc(const std::vector<Expression> & args){
  args.size(); // make compiler happy we used this parameter
  return Expression();
}

Expression add(const std::vector<Expression> & args){

  // check all aruments are numbers, while adding
  double result = 0;
  for( auto & a :args) {
    if(!a.isHeadNumber()) {
      throw SemanticError("Error in call to add, argument not a number");
    }
    result += a.head().asNumber();
  }

  return Expression(result);
}

Expression mul(const std::vector<Expression> & args) { 
  // check all aruments are numbers, while multiplying
  double result = 1;
  for( auto & a :args) {
    if (!a.isHeadNumber()) {
      throw SemanticError("Error in call to mul, argument not a number");
    }
    result *= a.head().asNumber();
  }

  return Expression(result);
}

Expression subneg(const std::vector<Expression> & args){

  double result = 0;

  // preconditions
  if ( nargs_equal(args,1) ) {
    if (!args[0].isHeadNumber()) {
      throw SemanticError("Error in call to negate: invalid argument.");
    }
    result = -args[0].head().asNumber();
  }
  else if (nargs_equal(args,2)){
    if( !(args[0].isHeadNumber()) || !(args[1].isHeadNumber()) ){
      throw SemanticError("Error in call to subtraction: invalid argument.");
    }
    result = args[0].head().asNumber() - args[1].head().asNumber();
  }
  else {
    throw SemanticError("Error in call to subtraction or negation: invalid number of arguments.");
  }

  return Expression(result);
}

Expression div(const std::vector<Expression> & args) {
  if (!nargs_equal(args,2)) {
    throw SemanticError("Error in call to division: invalid number of arguments.");
  }
  if (!(args[0].isHeadNumber()) || !(args[1].isHeadNumber())) {
    throw SemanticError("Error in call to division: invalid argument.");
  }
  
  double result = args[0].head().asNumber() / args[1].head().asNumber();
  return Expression(result);
}

Expression pow(const std::vector<Expression> & args){
  if (!nargs_equal(args,2)) {
    throw SemanticError("Error in call to power: invalid number of arguments.");
  }
  if (!(args[0].isHeadNumber()) || !(args[1].isHeadNumber())) {
    throw SemanticError("Error in call to power: invalid argument.");
  }
  
  double result = std::pow(args[0].head().asNumber(), args[1].head().asNumber());
  return Expression(result);
}

Expression sqrt(const std::vector<Expression> & args){
  if (!nargs_equal(args,1)) {
    throw SemanticError("Error in call to square root: invalid number of arguments.");
  }
  if (!(args[0].isHeadNumber()) || !(args[0].head().asNumber() < 0)) {
    throw SemanticError("Error in call to square root: invalid argument.");
  }
  
  double result = std::sqrt(args[0].head().asNumber());
  return Expression(result);
}

Expression sin(const std::vector<Expression> & args){
  if (!nargs_equal(args,1)) {
    throw SemanticError("Error in call to sin: invalid number of arguments.");
  }
  if (!(args[0].isHeadNumber())) {
    throw SemanticError("Error in call to sin: invalid argument.");
  }
  
  double result = std::sin(args[0].head().asNumber());
  return Expression(result);
}

Expression cos(const std::vector<Expression> & args){
  if (!nargs_equal(args,1)) {
    throw SemanticError("Error in call to cos: invalid number of arguments.");
  }
  if (!(args[0].isHeadNumber())) {
    throw SemanticError("Error in call to cos: invalid argument.");
  }
  
  double result = std::cos(args[0].head().asNumber());
  return Expression(result);
}

Expression tan(const std::vector<Expression> & args){
  if (!nargs_equal(args,1)) {
    throw SemanticError("Error in call to tan: invalid number of arguments.");
  }
  if (!(args[0].isHeadNumber())) {
    throw SemanticError("Error in call to tan: invalid argument.");
  }
  
  double result = std::tan(args[0].head().asNumber());
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

  // Built-In value of pi
  envmap.emplace("e", EnvResult(ExpressionType, Expression(EXP)));

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
  
  // Procedure: sin;
  envmap.emplace("sin", EnvResult(ProcedureType, sin)); 
  
  // Procedure: cos;
  envmap.emplace("cos", EnvResult(ProcedureType, cos)); 
  
  // Procedure: tan;
  envmap.emplace("tan", EnvResult(ProcedureType, cos)); 
}
