// --------------------------------
// projects/integer/TestInteger.c++
// Copyright (C) 2015
// Glenn P. Downing
// --------------------------------

// https://code.google.com/p/googletest/wiki/V1_7_Primer#Basic_Assertions

// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // string
#include <utility>  // pair
#include <vector>   // vector
#include <list>     // list
#include <deque>

#include "gtest/gtest.h"

#include "Integer.h"

using namespace std;

// -----------
// TestInteger
// -----------

using testing::Test;
using testing::Types;

template <typename T>
struct Integer_Fixture : Test {
    typedef T Integer_type;};

typedef Types<
            Integer<int>,
            Integer<int, deque<int>>,
            Integer<int, vector<int>>>
        Integer_types;

TYPED_TEST_CASE(Integer_Fixture, Integer_types);


// ----
// insert tests here
// ----

TEST(IntegerFixture, shift_left_1) {
	//tests the output vector
    vector<int> vec = {1,2,3,4,5};
    vector<int> out(3);
    vector<int> test = {3,4,5};
    shift_left_digits(vec.begin(), vec.end(), 2, out.begin());
    ASSERT_TRUE(equal(out.begin(), out.end(), test.begin()));
}

TEST(IntegerFixture, shift_left_2) {
	//tests the output iterator value
	vector<int> vec = {1,2,3,4,5};
	vector<int> out(3);
	vector<int>::iterator itr = shift_left_digits(vec.begin(), vec.end(), 2, out.begin());
	ASSERT_EQ(itr, out.end());
}

TEST(IntegerFixture, shift_left_3) {
	//shift in middle
	vector<int> vec = {1,2,3,4,5};
	vector<int> out(1);
	vector<int> test = {4};
	vector<int>::iterator itr = shift_left_digits(vec.begin()+2, vec.end()-1, 2, out.begin());
	ASSERT_TRUE(equal(out.begin(), itr, test.begin()));
}

/*shift_right tests */

TEST(IntegerFixture, shift_right_1) {
	//tests the output vector
    vector<int> vec = {1,2,3,4,5};
    vector<int> out(7);
    vector<int> test = {0,0,1,2,3,4,5};
    shift_right_digits(vec.begin(), vec.end(), 2, out.begin());
    ASSERT_TRUE(equal(out.begin(), out.end(), test.begin()));
}

TEST(IntegerFixture, shift_right_2) {
	//tests the output iterator value
	vector<int> vec = {1,2,3,4,5};
	vector<int> out(7);
	vector<int>::iterator itr = shift_right_digits(vec.begin(), vec.end(), 2, out.begin());
	ASSERT_EQ(itr, out.end());
}

TEST(IntegerFixture, shift_right_3) {
	//shift in middle
	vector<int> vec = {1,2,3,4,5};
	vector<int> out(5);
	vector<int> test = {0,0,2,3,4};
	vector<int>::iterator itr = shift_right_digits(vec.begin()+1, vec.end()-1, 2, out.begin());
	ASSERT_TRUE(equal(out.begin(), itr, test.begin()));
}

TEST(IntegerFixture, shift_right_4) {
	//failure case
	vector<int> vec = {4};
	vector<int> out(2);
	vector<int> test = {0,4};
	vector<int>::iterator itr = shift_right_digits(vec.begin(), vec.end(), 1, out.begin());
	ASSERT_TRUE(equal(out.begin(), itr, test.begin()));
}

TEST(IntegerFixture, shift_right_5) {
	//output result into original vector
	vector<int> vec = {1,0,2,0};
	vector<int> test = {0,1,0,2};
	vector<int>::iterator itr = shift_right_digits(vec.begin(), vec.end()-1, 1, vec.begin());
	ASSERT_TRUE(equal(vec.begin(), itr, test.begin()));
}

/* plus_digits tests */

TEST(IntegerFixture, plus_digits_1) {
	//tests the output vector
    vector<int> vecOne = {5,4,3,2,1};
    vector<int> vecTwo = {3,9,8,7,6};
    vector<int> out(5);
    vector<int> test = {8,3,2,0,8};
    plus_digits(vecOne.begin(), vecOne.end(), vecTwo.begin(), vecTwo.end(), out.begin());
    ASSERT_TRUE(equal(out.begin(), out.end(), test.begin()));
}

TEST(IntegerFixture, plus_digits_2) {
	//tests the output iterator value
    vector<int> vecOne = {5,4,3,2,1};
    vector<int> vecTwo = {3,9,8,7,6};
	vector<int> out(5);
	vector<int>::iterator itr = plus_digits(vecOne.begin(), vecOne.end(), vecTwo.begin(), vecTwo.end(), out.begin());
	ASSERT_EQ(itr, out.end());
}

TEST(IntegerFixture, plus_digits_3) {
	//vectors of two different lengths
    vector<int> vecOne = {5,4,3,2,1};
    vector<int> vecTwo = {9,8,7,6};
	vector<int> out(5);
	vector<int> test = {4,3,1,9,1};
	vector<int>::iterator itr = plus_digits(vecOne.begin(), vecOne.end(), vecTwo.begin(), vecTwo.end(), out.begin());
	ASSERT_TRUE(equal(out.begin(), out.end(), test.begin()));
	ASSERT_EQ(itr, out.end());
}

TEST(IntegerFixture, plus_digits_4) {
	//vectors of two different lengths
    vector<int> vecOne = {5,4,3,2,1};
    vector<int> vecTwo = {9,8,7,6};
	vector<int> out(5);
	vector<int> test = {4,3,1,9,1};
	vector<int>::iterator itr = plus_digits(vecOne.begin(), vecOne.end(), vecTwo.begin(), vecTwo.end(), out.begin());
	ASSERT_TRUE(equal(out.begin(), out.end(), test.begin()));
	ASSERT_EQ(itr, out.end());
}

TEST(IntegerFixture, plus_digits_5) {
	//add in middle
    vector<int> vecOne = {5,4,3,2,1};
    vector<int> vecTwo = {3,9,8,7,6};
    vector<int> out(4);
    vector<int> test = {3,2,0,1};
	vector<int>::iterator itr = plus_digits(vecOne.begin()+1, vecOne.end()-1, vecTwo.begin()+1, vecTwo.end()-1, out.begin());
	ASSERT_TRUE(equal(out.begin(), itr, test.begin()));
}

/* minus_digits tests */

TEST(IntegerFixture, minus_digits_1) {
	//tests the output vector
    vector<int> vecOne = {3,9,8,7,6};
    vector<int> vecTwo = {5,4,3,2,1};
    vector<int> out(5);
    vector<int> test = {8,4,5,5,5};
    minus_digits(vecOne.begin(), vecOne.end(), vecTwo.begin(), vecTwo.end(), out.begin());
    ASSERT_TRUE(equal(out.begin(), out.end(), test.begin()));
}

TEST(IntegerFixture, minus_digits_2) {
	//tests the output iterator value
    vector<int> vecOne = {5,4,3,2,1};
    vector<int> vecTwo = {3,9,8,7,6};
	vector<int> out(5);
	vector<int>::iterator itr = minus_digits(vecOne.begin(), vecOne.end(), vecTwo.begin(), vecTwo.end(), out.begin());
	ASSERT_EQ(itr, out.end());
}

TEST(IntegerFixture, minus_digits_3) {
	//vectors of two different lengths
    vector<int> vecOne = {5,4,3,2,1};
    vector<int> vecTwo = {9,8,7,6};
	vector<int> out(4);
	vector<int> test = {6,5,5,5};
	vector<int>::iterator itr = minus_digits(vecOne.begin(), vecOne.end(), vecTwo.begin(), vecTwo.end(), out.begin());
	ASSERT_TRUE(equal(out.begin(), out.end(), test.begin()));
	ASSERT_EQ(itr, out.end());

}

TEST(IntegerFixture, minus_digits_4) {
	//add in middle
	vector<int> vecOne = {1,2,3,4,5};
    vector<int> vecTwo = {1,2,3,4,5};
    vector<int> out(1);
    vector<int> test = {0};
	vector<int>::iterator itr = minus_digits(vecOne.begin()+1, vecOne.end()-1, vecTwo.begin()+1, vecTwo.end()-1, out.begin());
	ASSERT_TRUE(equal(out.begin(), itr, test.begin()));
}

TEST(IntegerFixture, minus_digits_5) {
	//failure case
    vector<int> vecOne = {6,5};
    vector<int> vecTwo = {6,1};
    vector<int> out(2);
    vector<int> test = {0,4};
    minus_digits(vecOne.begin(), vecOne.end(), vecTwo.begin(), vecTwo.end(), out.begin());
    ASSERT_TRUE(equal(out.begin(), out.end(), test.begin()));
}

TEST(IntegerFixture, minus_digits_6) {
	//failure case
    vector<int> vecOne = {6,1,0,2};
    vector<int> vecTwo = {6};
    vector<int> out(4);
    vector<int> test = {0,1,0,2};
    minus_digits(vecOne.begin(), vecOne.end(), vecTwo.begin(), vecTwo.end(), out.begin());
    ASSERT_TRUE(equal(out.begin(), out.end(), test.begin()));
}

TEST(IntegerFixture, minus_digits_7) {
	//failure case
    vector<int> vecOne = {0,1,0,2};
    vector<int> vecTwo = {4,9,7,1};
    vector<int> out(3);
    vector<int> test = {6,1,2};
    vector<int>::iterator itr = minus_digits(vecOne.begin(), vecOne.end(), vecTwo.begin(), vecTwo.end(), out.begin());
    ASSERT_TRUE(equal(out.begin(), out.end(), test.begin()));
    ASSERT_EQ(itr, out.end());
}

TEST(IntegerFixture, minus_digits_8) {
	//failure case
    vector<int> vecOne = {0,1,0,2,1};
    vector<int> vecTwo = {7,6};
    vector<int> out(5);
    vector<int> test = {3,4,9,1,1};
    vector<int>::iterator itr = minus_digits(vecOne.begin(), vecOne.end(), vecTwo.begin(), vecTwo.end(), out.begin());
    ASSERT_TRUE(equal(out.begin(), out.end(), test.begin()));
    ASSERT_EQ(itr, out.end());
}


/* multiplies_digits tests */

TEST(IntegerFixture, multiplies_digits_00) {
	//tests the output vector
    vector<int> vecOne = {2,1};
    vector<int> vecTwo = {7,6};
    vector<int> out(3);
    vector<int> test = {4,0,8}; 
    multiplies_digits(vecOne.begin(), vecOne.end(), vecTwo.begin(), vecTwo.end(), out.begin());
    ASSERT_TRUE(equal(out.begin(), out.end(), test.begin()));
}

TEST(IntegerFixture, multiplies_digits_0) {
	//tests the output vector
    vector<int> vecOne = {3,2,1};
    vector<int> vecTwo = {8,7,6};
    vector<int> out(5);
    vector<int> test = {4,9,3,3,8}; 
    multiplies_digits(vecOne.begin(), vecOne.end(), vecTwo.begin(), vecTwo.end(), out.begin());
    ASSERT_TRUE(equal(out.begin(), out.end(), test.begin()));
}

TEST(IntegerFixture, multiplies_digits_1) {
	//tests the output vector
    vector<int> vecOne = {5,4,3,2,1};
    vector<int> vecTwo = {3,9,8,7,6};
    vector<int> out(9);
    vector<int> test = {5,8,0,9,3,1,8,3,8}; 
    multiplies_digits(vecOne.begin(), vecOne.end(), vecTwo.begin(), vecTwo.end(), out.begin());
    ASSERT_TRUE(equal(out.begin(), out.end(), test.begin()));
}

TEST(IntegerFixture, multiplies_digits_2) {
	//tests the output iterator value
    vector<int> vecOne = {5,4,3,2,1};
    vector<int> vecTwo = {3,9,8,7,6};
	vector<int> out(9);
	vector<int>::iterator itr = multiplies_digits(vecOne.begin(), vecOne.end(), vecTwo.begin(), vecTwo.end(), out.begin());
	ASSERT_EQ(itr, out.end());
}

TEST(IntegerFixture, multiplies_digits_3) {
	//vectors of two different lengths
	vector<int> vecOne = {5,4,3,2,1};
    vector<int> vecTwo = {9,8,7,6};
	vector<int> out(8);
	vector<int> test = {5,0,2,0,1,8,3,8};
	vector<int>::iterator itr = multiplies_digits(vecOne.begin(), vecOne.end(), vecTwo.begin(), vecTwo.end(), out.begin());
	ASSERT_TRUE(equal(out.begin(), out.end(), test.begin()));
	ASSERT_EQ(itr, out.end());
}

TEST(IntegerFixture, multiplies_digits_4) {
	//vectors of two different lengths
	vector<int> vecOne = {4,3,2,1};
    vector<int> vecTwo = {5,9,8,7,6};
	vector<int> out(8);
	vector<int> test = {0,3,4,2,8,7,3,8};
	vector<int>::iterator itr = multiplies_digits(vecOne.begin(), vecOne.end(), vecTwo.begin(), vecTwo.end(), out.begin());
	ASSERT_TRUE(equal(out.begin(), out.end(), test.begin()));
	ASSERT_EQ(itr, out.end());
}

TEST(IntegerFixture, multiplies_digits_5) {
	//add in middle
    vector<int> vecOne = {5,4,3,2,1};
    vector<int> vecTwo = {3,9,8,7,6};
    vector<int> out(6);
    vector<int> test = {6,2,6,4,8,1}; 
	vector<int>::iterator itr = multiplies_digits(vecOne.begin()+1, vecOne.end()-1, vecTwo.begin()+1, vecTwo.end()-1, out.begin());
	ASSERT_TRUE(equal(out.begin(), itr, test.begin()));
}

/* divides_digits tests */

TEST(IntegerFixture, divides_digits_00) {
	//tests the output vector
	vector<int> vecOne = {5};
    vector<int> vecTwo = {1};
    vector<int> out(1);
    vector<int> test = {5}; 
    divides_digits(vecOne.begin(), vecOne.end(), vecTwo.begin(), vecTwo.end(), out.begin());
    ASSERT_TRUE(equal(out.begin(), out.end(), test.begin()));
}

TEST(IntegerFixture, divides_digits_0) {
	//tests the output vector
	vector<int> vecOne = {5,2,1};
    vector<int> vecTwo = {5,2};
    vector<int> out(1);
    vector<int> test = {5}; 
    divides_digits(vecOne.begin(), vecOne.end(), vecTwo.begin(), vecTwo.end(), out.begin());
    ASSERT_TRUE(equal(out.begin(), out.end(), test.begin()));
}

TEST(IntegerFixture, divides_digits_1) {
	//tests the output vector
	vector<int> vecOne = {3,8,9,9,9};
    vector<int> vecTwo = {5,4,3,2,1};
    vector<int> out(1);
    vector<int> test = {8}; 
    divides_digits(vecOne.begin(), vecOne.end(), vecTwo.begin(), vecTwo.end(), out.begin());
    ASSERT_TRUE(equal(out.begin(), out.end(), test.begin()));
}

TEST(IntegerFixture, divides_digits_2) {
	//tests the output iterator value
	vector<int> vecOne = {3,8,9,9,9};
    vector<int> vecTwo = {5,4,3,2,1};
    vector<int> out(1);
	vector<int>::iterator itr = divides_digits(vecOne.begin(), vecOne.end(), vecTwo.begin(), vecTwo.end(), out.begin());
	ASSERT_EQ(itr, out.end());
}

TEST(IntegerFixture, divides_digits_3) {
	//vectors of two different lengths
	vector<int> vecOne = {5,4,3,2,1};
    vector<int> vecTwo = {7,6};
	vector<int> out(3);
	vector<int> test = {4,8,1};
	vector<int>::iterator itr = divides_digits(vecOne.begin(), vecOne.end(), vecTwo.begin(), vecTwo.end(), out.begin());
	ASSERT_TRUE(equal(out.begin(), out.end(), test.begin()));
	ASSERT_EQ(itr, out.end());
}

TEST(IntegerFixture, divides_digits_4) {
	//vectors of two different lengths
	vector<int> vecOne = {4,3,2,1};
    vector<int> vecTwo = {5,9,8,7,6};
	vector<int> out(1);
	vector<int> test = {0};
	vector<int>::iterator itr = divides_digits(vecOne.begin(), vecOne.end(), vecTwo.begin(), vecTwo.end(), out.begin());
	ASSERT_TRUE(equal(out.begin(), out.end(), test.begin()));
	ASSERT_EQ(itr, out.end());
}

TEST(IntegerFixture, divides_digits_5) {
	//add in middle
	vector<int> vecOne = {1,5,3,6,5,4,9,9,9};
    vector<int> vecTwo = {2,5,2,3,4,9,1,1,1};
    vector<int> out(4);
    vector<int> test = {4,5,0,1}; 
	vector<int>::iterator itr = divides_digits(vecOne.begin()+1, vecOne.end()-1, vecTwo.begin()+2, vecTwo.end()-3, out.begin());
	ASSERT_TRUE(equal(out.begin(), itr, test.begin()));
}

/* integer methods tests */

TEST(IntegerFixture, equals_1) {
	Integer<int> a = 12345;
	Integer<int> b = 12345;
	ASSERT_EQ(a, b);
}

TEST(IntegerFixture, equals_2) {
	Integer<int> a = 0;
	Integer<int> b = 0;
	ASSERT_EQ(a, b);
}

TEST(IntegerFixture, equals_3) {
	Integer<int> a = 12345;
	Integer<int> b = -12345;
	ASSERT_NE(a, b);
}

TEST(IntegerFixture, equals_4) {
	Integer<int> a = -12345;
	Integer<int> b = -12345;
	ASSERT_EQ(a, b);
}

TEST(IntegerFixture, equals_5) {
	Integer<int> a = 12345;
	Integer<int> b = 98765;
	ASSERT_NE(a, b);
}

TEST(IntegerFixture, less_than_1) {
	Integer<int> a = 12345;
	Integer<int> b = 987;
	ASSERT_TRUE(b < a);
}

TEST(IntegerFixture, less_than_2) {
	Integer<int> a = 12345;
	Integer<int> b = 12345;
	ASSERT_FALSE(b < a);
}

TEST(IntegerFixture, less_than_3) {
	Integer<int> a = -12345;
	Integer<int> b = 12345;
	ASSERT_TRUE(a < b);
}

TEST(IntegerFixture, less_than_4) {
	Integer<int> a = -12345;
	Integer<int> b = -12345;
	ASSERT_FALSE(a < b);
}

TEST(IntegerFixture, less_than_5) {
	Integer<int> a = -12345;
	Integer<int> b = -987;
	ASSERT_TRUE(a < b);
}

TEST(IntegerFixture, less_than_6) {
	Integer<int> a = 1234;
	Integer<int> b = 1232;
	ASSERT_TRUE(b < a);
}

TEST(IntegerFixture, output_1) {
	Integer<int> a = 12345;
	ostringstream output;
	output << a;
	ASSERT_EQ(output.str(), "12345");
}

TEST(IntegerFixture, output_2) {
	Integer<int> a = -12345;
	ostringstream output;
	output << a;
	ASSERT_EQ(output.str(), "-12345");
}

TEST(IntegerFixture, constructor_int_1) {
	Integer<int> a = 12345;
	ostringstream output;
	output << a;
	ASSERT_EQ(output.str(), "12345");
}

TEST(IntegerFixture, constructor_int_2) {
	Integer<int> a = 2147483647;
	ostringstream output;
	output << a;
	ASSERT_EQ(output.str(), "2147483647");
}

TEST(IntegerFixture, constructor_int_3) {
	Integer<int> a = 0;
	ostringstream output;
	output << a;
	ASSERT_EQ(output.str(), "0");
}

TEST(IntegerFixture, constructor_string_1) {
	Integer<int> a("12345");
	ostringstream output;
	output << a;
	ASSERT_EQ(output.str(), "12345");
}

TEST(IntegerFixture, constructor_string_2) {
	Integer<int> a("2147483647");
	ostringstream output;
	output << a;
	ASSERT_EQ(output.str(), "2147483647");
}

TEST(IntegerFixture, constructor_string_3) {
	Integer<int> a("0");
	ostringstream output;
	output << a;
	ASSERT_EQ(output.str(), "0");
}

TEST(IntegerFixture, constructor_string_int_1) {
	Integer<int> a("-12345");
	Integer<int> b(-12345);
	ASSERT_EQ(a, b);
}

TEST(IntegerFixture, negation_1) {
	Integer<int> a = -12345;
	Integer<int> b = 12345;
	ASSERT_EQ(-a, b);
}
TEST(IntegerFixture, negation_2) {
	Integer<int> a = 12345;
	Integer<int> b = -12345;
	ASSERT_EQ(-a, b);
}

TEST(IntegerFixture, plus_equal_1) {
	Integer<int> a = 123;
	Integer<int> b = 123;
	ASSERT_EQ(a += b, 246);
}

TEST(IntegerFixture, plus_equal_2) {
	Integer<int> a = 123;
	Integer<int> b = 123;
	Integer<int>& c = a += b;
	ASSERT_EQ(c, 246);
	ASSERT_TRUE(&c == &a);
}

TEST(IntegerFixture, plus_equal_3) {
	Integer<int> a = 1234;
	Integer<int> b = -123;
	ASSERT_EQ(a += b, 1111);
}

TEST(IntegerFixture, plus_equal_4) {
	Integer<int> a = -1234;
	Integer<int> b = 123;
	ASSERT_EQ(a += b, -1111);
}

TEST(IntegerFixture, plus_equal_5) {
	Integer<int> a = 123;
	Integer<int> b = -1234;
	ASSERT_EQ(a += b, -1111);
}

TEST(IntegerFixture, plus_equal_6) {
	Integer<int> a = -123;
	Integer<int> b = 1234;
	ASSERT_EQ(a += b, 1111);
}

TEST(IntegerFixture, plus_equal_7) {
	Integer<int> a = -123;
	Integer<int> b = -123;
	ASSERT_EQ(a += b, -246);
}

TEST(IntegerFixture, plus_equal_8) {
	Integer<int> a = -1234;
	Integer<int> b = 1232;
	ASSERT_EQ(a += b, -2);
}

TEST(IntegerFixture, plus_equal_9) {
	Integer<int> a = 1234;
	Integer<int> b = 123;
	ASSERT_EQ(a += b, 1357);
}

TEST(IntegerFixture, minus_equal_1) {
	Integer<int> a = 123;
	Integer<int> b = 123;
	ASSERT_EQ(a -= b, 0);
}

TEST(IntegerFixture, minus_equal_2) {
	Integer<int> a = 123;
	Integer<int> b = 123;
	Integer<int>& c = a -= b;
	ASSERT_EQ(c, 0);
	ASSERT_TRUE(&c == &a);
}

TEST(IntegerFixture, minus_equal_3) {
	Integer<int> a = 1234;
	Integer<int> b = -123;
	ASSERT_EQ(a -= b, 1357);
}

TEST(IntegerFixture, minus_equal_4) {
	Integer<int> a = -1234;
	Integer<int> b = 123;
	ASSERT_EQ(a -= b, -1357);
}

TEST(IntegerFixture, minus_equal_5) {
	Integer<int> a = 123;
	Integer<int> b = -1234;
	ASSERT_EQ(a -= b, 1357);
}

TEST(IntegerFixture, minus_equal_6) {
	Integer<int> a = -123;
	Integer<int> b = 1234;
	ASSERT_EQ(a -= b, -1357);
}

TEST(IntegerFixture, minus_equal_7) {
	Integer<int> a = -123;
	Integer<int> b = -123;
	ASSERT_EQ(a -= b, 0);
}

TEST(IntegerFixture, minus_equal_8) {
	Integer<int> a = -1234;
	Integer<int> b = 1232;
	ASSERT_EQ(a -= b, -2466);
}

TEST(IntegerFixture, multi_equal_1) {
	Integer<int> a = 123;
	Integer<int> b = 123;
	ASSERT_EQ(a*b, 15129);
}

TEST(IntegerFixture, multi_equal_2) {
	Integer<int> a = 123;
	Integer<int> b = 1;
	ASSERT_EQ(a*b, 123);
}

TEST(IntegerFixture, multi_equal_3) {
	Integer<int> a = 123;
	Integer<int> b = 0;
	ASSERT_EQ(a*b, 0);
}

TEST(IntegerFixture, multi_equal_4) {
	Integer<int> a = -123;
	Integer<int> b = -123;
	ASSERT_EQ(a*b, 15129);
}

TEST(IntegerFixture, multi_equal_5) {
	Integer<int> a = 123;
	Integer<int> b = -123;
	ASSERT_EQ(a*b, -15129);
}
TEST(IntegerFixture, multi_equal_6) {
	Integer<int> a = -123;
	Integer<int> b = 0;
	ASSERT_EQ(a*b, 0);
}

TEST(IntegerFixture, divide_equal_1) {
	Integer<int> a = 123;
	Integer<int> b = 123;
	ASSERT_EQ(a /= b, 1);
}

TEST(IntegerFixture, divide_equal_2) {
	Integer<int> a = 123;
	Integer<int> b = 678;
	ASSERT_EQ(a /= b, 0);
}

TEST(IntegerFixture, divide_equal_3) {
	Integer<int> a = 123;
	Integer<int> b = 678;
	ASSERT_EQ(b /= a, 5);
}

TEST(IntegerFixture, divide_equal_4) {
	Integer<int> a = -123;
	Integer<int> b = 678;
	ASSERT_EQ(b /= a, -5);
}

TEST(IntegerFixture, divide_equal_5) {
	Integer<int> a = 123;
	Integer<int> b = -678;
	ASSERT_EQ(b /= a, -5);
}

TEST(IntegerFixture, divide_equal_6) {
	Integer<int> a = 0;
	Integer<int> b = -678;
	ASSERT_EQ(a /= b, 0);
}

TEST(IntegerFixture, divide_equal_7) {
	Integer<int> a = -123;
	Integer<int> b = -678;
	ASSERT_EQ(b /= a, 5);
}

TEST(IntegerFixture, mod_equal_1) {

}

// TEST(IntegerFixture, left_shift_equal_1) {

// }

// TEST(IntegerFixture, right_shift_equal_1) {

// }

TEST(IntegerFixture, abs_1) {
	Integer<int> a = 12;
	ASSERT_EQ(a.abs(), 12);
}

TEST(IntegerFixture, abs_2) {
	Integer<int> a = 12;
	ASSERT_EQ(a.abs(), 12);
}

TEST(IntegerFixture, pow_1) {
	Integer<int> a = 12;
	ASSERT_EQ(a.pow(2), 144);
}

TEST(IntegerFixture, pow_2) {
	Integer<int> a = -12;
	ASSERT_EQ(a.pow(2), 144);
}

TEST(IntegerFixture, pow_3) {
	Integer<int> a = -12;
	ASSERT_EQ(a.pow(3), -1728);
}

TEST(IntegerFixture, pow_4) {
	Integer<int> a = 12;
	ASSERT_EQ(a.pow(0), 1);
}

TEST(IntegerFixture, pow_5) {
	Integer<int> a = 2;
	ostringstream output;
	output << a.pow(34);
	ASSERT_EQ(output.str(), "17179869184");
}
