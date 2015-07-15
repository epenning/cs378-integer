// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // string
#include <utility>  // pair
#include <vector>
#include <iterator>

#include "gtest/gtest.h"

#define private public

#include "Integer.h"



using namespace std;

// 20 methods or functions

TEST(IntegerFixture, equalequal1){
	Integer<int> x(1);
	Integer<int> y(-1);
	ASSERT_FALSE(x == y);
}

TEST(IntegerFixture, equalequal2){
	Integer<int> x(1);
	Integer<int> y(4);
	ASSERT_FALSE(x == y);
}

TEST(IntegerFixture, equalequal3){
	Integer<int> x(-333);
	Integer<int> y(-5);
	ASSERT_FALSE(x == y);
}

TEST(IntegerFixture, equalequal4){
	Integer<int> x(-3);
	Integer<int> y(-3);
	ASSERT_TRUE(x == y);
}

TEST(IntegerFixture, equalequal5){
	Integer<int> x(100);
	Integer<int> y("100");
	ASSERT_TRUE(x == y);
}

TEST(IntegerFixture, notequal1){
	Integer<int> x(1);
	Integer<int> y(-1);
	ASSERT_TRUE(x != y);
}

TEST(IntegerFixture, notequal2){
	Integer<int> x(1);
	Integer<int> y(4);
	ASSERT_TRUE(x != y);
}

TEST(IntegerFixture, notequal3){
	Integer<int> x(-333);
	Integer<int> y(-5);
	ASSERT_TRUE(x != y);
}

TEST(IntegerFixture, notequal4){
	Integer<int> x(-3);
	Integer<int> y(-3);
	ASSERT_FALSE(x != y);
}

TEST(IntegerFixture, notequal5){
	Integer<int> x(100);
	Integer<int> y("100");
	ASSERT_FALSE(x != y);
}

TEST(IntegerFixture, lessthan1){
	Integer<int> x(1);
	Integer<int> y(1000);
	ASSERT_TRUE(x < y);
}

TEST(IntegerFixture, lessthan2){
	Integer<int> x(-2);
	Integer<int> y(56);
	ASSERT_TRUE(x < y);
}
TEST(IntegerFixture, lessthan3){
	Integer<int> x(-3);
	Integer<int> y(-6);
	ASSERT_FALSE(x < y);
}
TEST(IntegerFixture, lessthan4){
	Integer<int> x(100);
	Integer<int> y("100");
	ASSERT_FALSE(x < y);
}

TEST(IntegerFixture, lessthan5){
	Integer<int> x(-7);
	Integer<int> y(-3);
	ASSERT_TRUE(x < y);
}

TEST(IntegerFixture, mod1){
	Integer<int> x(1);
	Integer<int> y = x % (1000);
	cout << y << endl;
	ASSERT_EQ(y , 1);
}

TEST(IntegerFixture, mod2){
	Integer<int> x(101);
	Integer<int> y = x % (100);
	ASSERT_EQ(y ,1);
}
TEST(IntegerFixture, mod3){
	Integer<int> x(-3);
	Integer<int> y = x % (2);
	ASSERT_EQ(y ,-1);
}
TEST(IntegerFixture, mod4){
	Integer<int> x(100);
	Integer<int> z("100");
	Integer<int> y = x % z;
	ASSERT_EQ(y,0);
}

TEST(IntegerFixture, mod5){
	try {
		Integer<int> x(-7);
		Integer<int> y = x % 0;
		ASSERT_TRUE(false);
	} catch(...) {
		ASSERT_TRUE(true);
	}
}

TEST(IntegerFixture, div1){
	Integer<int> x(1);
	Integer<int> y = x / (1000);
	ASSERT_EQ(y, 0);
}

TEST(IntegerFixture, div2){
	Integer<int> x(101);
	Integer<int> y = x / (100);
	ASSERT_EQ(y, 1);
}
TEST(IntegerFixture, div3){
	Integer<int> x(-6);
	Integer<int> y = x / (2);
	ASSERT_EQ(y, -3);
}
TEST(IntegerFixture, div4){
	Integer<int> x(100);
	Integer<int> z("100");
	Integer<int> y = x / z;
	ASSERT_EQ(y, 1);
}

TEST(IntegerFixture, div5){
	try {
		Integer<int> x(-7);
		Integer<int> y = x / 0;
		ASSERT_TRUE(false);
	} catch(...) {
		ASSERT_TRUE(true);
	}
}
TEST(IntegerFixture, lessless1){
	Integer<int> x(100);
	Integer<int> y = x << (1);
	ASSERT_EQ(y, 1000);
}

TEST(IntegerFixture, lessless2){
	Integer<int> x(-100);
	Integer<int> y = x << (1);
	ASSERT_EQ(y, -1000);
}

TEST(IntegerFixture, lessless3){
	Integer<int> x(1);
	Integer<int> y = x << (0);
	ASSERT_EQ(y, 1);
}

TEST(IntegerFixture, lessless4){
	try {
		Integer<int> x(-7);
		Integer<int> y = x << -1;
		ASSERT_TRUE(false);
	} catch(...) {
		ASSERT_TRUE(true);
	}
}

TEST(IntegerFixture, lessless5){
	Integer<int> x(1);
	Integer<int> y = x << (5);
	ASSERT_EQ(y, 100000);
}

TEST(IntegerFixture, greatergreater1){
	Integer<int> x(300);
	Integer<int> y = x >> (2);
	ASSERT_EQ(y, 3);
}

TEST(IntegerFixture, greatergreater2){
	Integer<int> x(-100);
	Integer<int> y = x >> (1);
	ASSERT_EQ(y, -10);
}

TEST(IntegerFixture, greatergreater3){
	Integer<int> x(10);
	Integer<int> y = x >> (0);
	ASSERT_EQ(y, 10);
}

TEST(IntegerFixture, greatergreater4){
	try {
		Integer<int> x(8);
		Integer<int> y = x >> -1;
		ASSERT_TRUE(false);
	} catch(...) {
		ASSERT_TRUE(true);
	}
}

TEST(IntegerFixture, greatergreater5){
	Integer<int> x(1);
	Integer<int> y = x >> (1);
	ASSERT_EQ(y, 0);
}


TEST(IntegerFixture, test_output_1) {
    ostringstream w;
    Integer<int> n(-1234567890);
    w << n;
    ASSERT_EQ(w.str(), "-1234567890");
}

TEST(IntegerFixture, test_output_2) {
    ostringstream w;
    Integer<int> n(33333);
    w << n;
    ASSERT_EQ(w.str(), "33333");
}

TEST(IntegerFixture, test_output_3) {
    ostringstream w;
    Integer<int> n("12345");
    w << n;
    ASSERT_EQ(w.str(), "12345");
}

TEST(IntegerFixture, test_output_4) {
    ostringstream w;
    Integer<int> n("-32245");
    w << n;
    ASSERT_EQ(w.str(), "-32245");
}

TEST(IntegerFixture, test_output_5) {
    ostringstream w;
    Integer<int> n(-1234567890);
    w << n;
    ASSERT_EQ(w.str(), "-1234567890");
}

TEST(IntegerFixture, pow1){
	Integer<int> x(-7);
	Integer<int> y = x.pow(3);
	ASSERT_EQ(y, -343);
}

TEST(IntegerFixture, pow2){
	Integer<int> x(7);
	Integer<int> y = x.pow(3);
	ASSERT_EQ(y, 343);
}

TEST(IntegerFixture, pow3){
	Integer<int> x(7);
	Integer<int> y = x.pow(0);
	ASSERT_EQ(y, 1);
}
TEST(IntegerFixture, pow4){
	try{
		Integer<int> x(0);
		Integer<int> y = x.pow(0);
		ASSERT_FALSE(true);
	} catch(...) {
		ASSERT_FALSE(false);
	}
	
}
TEST(IntegerFixture, pow5){
	try{
		Integer<int> x(3);
		Integer<int> y = x.pow(-3);
		ASSERT_FALSE(true);
	} catch(...) {
		ASSERT_FALSE(false);
	}
}

TEST(IntegerFixture, pow6){
	Integer<int> x(0);
	Integer<int> y = x.pow(3);
	ASSERT_EQ(y, 0);
}

TEST(IntegerFixture, abs1){
	Integer<int> x(-7);
	ASSERT_EQ(abs(x), 7);
}

TEST(IntegerFixture, abs2){
	Integer<int> x(7);
	ASSERT_EQ(abs(x), 7);
}

TEST(IntegerFixture, abs3){
	Integer<int> x(0);
	ASSERT_EQ(abs(x),0);
}


TEST(IntegerFixture, abs4){
	Integer<int> x(-733333333);
	ASSERT_EQ(abs(x), 733333333);
}

TEST(IntegerFixture, plusequal1){
	Integer<int> x(-7);
	x += 7;
	ASSERT_EQ(x, 0);
}

TEST(IntegerFixture, plusequal2){
	Integer<int> x("33333");
	x += 1;
	ASSERT_EQ(x, 33334);
}

TEST(IntegerFixture, plusequal3){
	Integer<int> x(90);
	x += 0;
	ASSERT_EQ(x, 90);
}

TEST(IntegerFixture, plusequal4){
	Integer<int> x(0);
	x += -8;
	ASSERT_EQ(x, -8);
}

TEST(IntegerFixture, minusequal1){
	Integer<int> x(-7);
	x -= 7;
	ASSERT_EQ(x, -14);
}

TEST(IntegerFixture, minusequal2){
	Integer<int> x("33333");
	x -= 1;
	ASSERT_EQ(x, 33332);
}

TEST(IntegerFixture, minusequal3){
	Integer<int> x(90);
	x -= 0;
	ASSERT_EQ(x, 90);
}

TEST(IntegerFixture, minusequal4){
	Integer<int> x(0);
	x -= -8;
	ASSERT_EQ(x, 8);
}

TEST(IntegerFixture, timeequal1){
	Integer<int> x(-7);
	x *= 7;
	ASSERT_EQ(x,-49);
}

TEST(IntegerFixture, timeequal2){
	Integer<int> x("33333");
	x *= 2;
	ASSERT_EQ(x,66666);
}

TEST(IntegerFixture, timeequal3){
	Integer<int> x(99);
	x *= 3;
	ASSERT_EQ(x ,297);
}

TEST(IntegerFixture, timeequal4){
	Integer<int> x(0);
	x *= 8;
	ASSERT_EQ(x , 0);
}

TEST(IntegerFixture, timeequal5){
	Integer<int> x(666);
	x *= 0;
	ASSERT_EQ(x ,0);
}

TEST(IntegerFixture, timeequal6){
	Integer<int> x(334);
	x *= -8;
	ASSERT_EQ(x ,-2672);
}

TEST(IntegerFixture, timeequal7){
	Integer<int> x(-334);
	x *= -8;
	ASSERT_EQ(x ,2672);
}

TEST(IntegerFixture, negate1){
	Integer<int> x(-334);
	Integer<int> y = -x;
	ASSERT_EQ(y, 334);
}

TEST(IntegerFixture, negate2){
	Integer<int> x(33);
	Integer<int> y = -x;
	ASSERT_EQ(y,-33);
}

TEST(IntegerFixture, negate3){
	Integer<int> x("0");
	Integer<int> y = -x;
	ASSERT_EQ(abs(y), 0);
}

