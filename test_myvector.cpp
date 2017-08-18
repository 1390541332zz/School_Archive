#define CATCH_CONFIG_MAIN 
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"

#include "MyVector.h"

#include <stdexcept>

TEST_CASE( "Test the constructor, size, and empty with an int type.", "[MyVector]" ) {

  MyVector<int> vec;
  
  REQUIRE( vec.size() == 0 );
  REQUIRE( vec.empty() == true );
}

TEST_CASE( "Test the constructor, size, and empty with a double type.", "[MyVector]" ) {

  MyVector<double> vec;
  
  REQUIRE( vec.size() == 0 );
  REQUIRE( vec.empty() == true );
}

TEST_CASE( "Test push_back method.", "[MyVector]" ) {

  MyVector<int> vec;
  
  REQUIRE( vec.size() == 0 );
  REQUIRE( vec.empty() == true );

  vec.push_back(42);

  REQUIRE( vec.size() == 1 );
  REQUIRE( vec.empty() == false );

  vec.push_back(3574);

  REQUIRE( vec.size() == 2 );
  REQUIRE( vec.empty() == false );
}

TEST_CASE( "Test at method.", "[MyVector]" ) {

  MyVector<int> vec;
  vec.push_back(1);
  vec.push_back(12);
  vec.push_back(8);
  vec.push_back(-40);

  REQUIRE( vec.at(0) == 1 );
  REQUIRE( vec.at(1) == 12 );
  REQUIRE( vec.at(2) == 8 );
  REQUIRE( vec.at(3) == -40 );

  vec.at(2) = 0;
  REQUIRE( vec.at(2) == 0 );
}

TEST_CASE( "Test exceptions", "[MyVector]" ) {

  MyVector<int> vec;
    
  REQUIRE_THROWS_AS(vec.at(0), std::range_error);

  vec.push_back(1);
  vec.push_back(12);
  vec.push_back(8);
  vec.push_back(-40);
  
  REQUIRE_THROWS_AS(vec.at(4), std::range_error);
  REQUIRE_THROWS_AS(vec.at(20), std::range_error);
}

TEST_CASE( "Test value sematics", "[MyVector]" ) {

  MyVector<int> vec1;
  vec1.push_back(1);
  vec1.push_back(12);
  vec1.push_back(8);
  vec1.push_back(-40);

  // test copy
  MyVector<int> vec2 = vec1;
  
  REQUIRE( vec2.at(0) == 1 );
  REQUIRE( vec2.at(1) == 12 );
  REQUIRE( vec2.at(2) == 8 );
  REQUIRE( vec2.at(3) == -40 );

  // test assignment
  MyVector<int> vec3;
  vec3 = vec1;
  
  REQUIRE( vec3.at(0) == 1 );
  REQUIRE( vec3.at(1) == 12 );
  REQUIRE( vec3.at(2) == 8 );
  REQUIRE( vec3.at(3) == -40 );

  // test self assignment
  vec3 = vec3;
  
  REQUIRE( vec3.at(0) == 1 );
  REQUIRE( vec3.at(1) == 12 );
  REQUIRE( vec3.at(2) == 8 );
  REQUIRE( vec3.at(3) == -40 );
  
}

