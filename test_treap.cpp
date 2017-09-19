#define CATCH_CONFIG_MAIN
#include "catch.hpp"

// standard includes
#include <string>
#include <random>
#include <map>
#include <sstream>

// the ADT being testing
#include "treap_bst.h"

// exapand the full template
template class TreapBST<std::mt19937::result_type, std::string>;

typedef TreapBST<std::mt19937::result_type, std::string> TreeType;

// number of random increments
const unsigned int N = 5000;

TEST_CASE( "I tested empty before and after insert/removes", "[treap_bst]" ) {

  TreeType t;
  REQUIRE( t.empty() );
  
  t.insert(18, "18");
  REQUIRE( !t.empty() );
  
  t.insert(61, "61");
  REQUIRE( !t.empty() );
  
  t.insert(1, "1");
  REQUIRE( !t.empty() );
  
  t.remove(18);
  REQUIRE( !t.empty() );
  
  t.remove(1);
  REQUIRE( !t.empty() );
  
  t.remove(61);
  REQUIRE( t.empty() );
}
