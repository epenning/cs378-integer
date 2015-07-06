// ------------------------------
// projects/c++/integer/Integer.h
// Copyright (C) 2015
// Glenn P. Downing
// ------------------------------

#ifndef Integer_h
#define Integer_h

// --------
// includes
// --------

#include <cassert>   // assert
#include <iostream>  // ostream
#include <stdexcept> // invalid_argument
#include <string>    // string
#include <vector>    // vector
#include <math.h>

using namespace std;

// -----------------
// shift_left_digits
// -----------------

/**
 * @param b an iterator to the beginning of an input  sequence (inclusive)
 * @param e an iterator to the end       of an input  sequence (exclusive)
 * @param x an iterator to the beginning of an output sequence (inclusive)
 * @return  an iterator to the end       of an output sequence (exclusive)
 * the sequences are of decimal digits
 * output the shift left of the input sequence into the output sequence
 * ([b, e) << n) => x
 */
template <typename II, typename FI>
FI shift_left_digits (II b, II e, int n, FI x) {
    x = copy(b, e, x);
    for (int i=0; i<n; i++) {
        *x = 0;
        ++x;
    }
    return x;}

// ------------------
// shift_right_digits
// ------------------

/**
 * @param b an iterator to the beginning of an input  sequence (inclusive)
 * @param e an iterator to the end       of an input  sequence (exclusive)
 * @param x an iterator to the beginning of an output sequence (inclusive)
 * @return  an iterator to the end       of an output sequence (exclusive)
 * the sequences are of decimal digits
 * output the shift right of the input sequence into the output sequence
 * ([b, e) >> n) => x
 */
template <typename II, typename FI>
FI shift_right_digits (II b, II e, int n, FI x) {
    int count = 0;
    II b2 = b;
    while (b != e) {
        ++count;
        ++b;
    }
    for (int i = 0; i < count-n; i++) {
        *x = *b2;
        ++b2;
        ++x;
    }
    return x;}

// -----------
// plus_digits
// -----------

/**
 * @param b  an iterator to the beginning of an input  sequence (inclusive)
 * @param e  an iterator to the end       of an input  sequence (exclusive)
 * @param b2 an iterator to the beginning of an input  sequence (inclusive)
 * @param e2 an iterator to the end       of an input  sequence (exclusive)
 * @param x  an iterator to the beginning of an output sequence (inclusive)
 * @return   an iterator to the end       of an output sequence (exclusive)
 * the sequences are of decimal digits
 * output the sum of the two input sequences into the output sequence
 * ([b1, e1) + [b2, e2)) => x
 */
template <typename II1, typename II2, typename FI>
FI plus_digits (II1 b1, II1 e1, II2 b2, II2 e2, FI x) {
    vector<int> vec1(0);
    vector<int> vec2(0);
    deque<int> sum(0);
    while (b1 != e1) {
        vec1.push_back(*b1);
        ++b1;
    }
    while (b2 != e2) {
        vec2.push_back(*b2);
        ++b2;
    }
    int carry = 0;
    while (!vec1.empty() || !vec2.empty()) {
        if (vec1.empty()){
            sum.push_front((vec2.back() + carry) % 10);
            carry = (vec2.back()  + carry) / 10; // should be greater than one if we need to carry. 
            vec2.pop_back();
        }else if (vec2.empty()){
            sum.push_front((vec1.back() + carry) % 10);
            carry = (vec1.back()  + carry) / 10; // should be greater than one if we need to carry. 
            vec1.pop_back();
        }else{
            sum.push_front((vec1.back()  + vec2.back() + carry) % 10);
            carry = (vec1.back()  + vec2.back() + carry) / 10; // should be greater than one if we need to carry. 
            vec1.pop_back();
            vec2.pop_back();
        }
    }

    if(carry != 0)
        sum.push_front(carry);

    for(int i : sum){
        *x = i;
        ++x;
    }
    return x;}

// ------------
// minus_digits
// ------------

/**
 * @param b  an iterator to the beginning of an input  sequence (inclusive)
 * @param e  an iterator to the end       of an input  sequence (exclusive)
 * @param b2 an iterator to the beginning of an input  sequence (inclusive)
 * @param e2 an iterator to the end       of an input  sequence (exclusive)
 * @param x  an iterator to the beginning of an output sequence (inclusive)
 * @return   an iterator to the end       of an output sequence (exclusive)
 * the sequences are of decimal digits
 * output the difference of the two input sequences into the output sequence
 * ([b1, e1) - [b2, e2)) => x
 */
template <typename II1, typename II2, typename FI>
FI minus_digits (II1 b1, II1 e1, II2 b2, II2 e2, FI x) {
    vector<int> vec1(0);
    vector<int> vec2(0);
    deque<int> dif(0);
    vector<int>* bigP;
    vector<int>* littleP;
    while (b1 != e1) {
        vec1.push_back(*b1);
        ++b1;
    }
    while (b2 != e2) {
        vec2.push_back(*b2);
        ++b2;
    }

    //find out which is bigger.
    if(vec1.size() > vec2.size()){
        bigP = &vec1;
        littleP = &vec2;
    }else if(vec1.size() < vec2.size()){
        //NEED TO ADD FLIP THE NEGATIVE FLAG!!!!!!!!!
        bigP = &vec2;
        littleP = &vec1;
    }else{
        for(int i = 0; i < vec1.size(); ++i){
            if(vec1[i] > vec2[i]){
                bigP = &vec1;
                littleP = &vec2;
                break;
            }else if(vec1[i] < vec2[i]){
                bigP = &vec2;
                littleP = &vec1;
                break;
            }
        }
    }

    vector<int>& big = *bigP;
    vector<int>& little = *littleP;

    //now we subtract
    int borrow = 0;
    while(!big.empty() || !little.empty()){

        if (borrow) {
            big.back() -= borrow;
            borrow = 0;
        }
        if (little.empty()){
            dif.push_front(big.back());
            big.pop_back();
        }else{
            if(big.back() < little.back()){
                //we borrow.
                big.back() += 10;
                borrow += 1;
            }
            dif.push_front(big.back()  - little.back());
            big.pop_back();
            little.pop_back();
        }
    }

    while (!dif.front())
        dif.pop_front();

    for(int i : dif){
        *x = i;
        ++x;
    }

    return x;}

// -----------------
// multiplies_digits
// -----------------

/**
 * @param b  an iterator to the beginning of an input  sequence (inclusive)
 * @param e  an iterator to the end       of an input  sequence (exclusive)
 * @param b2 an iterator to the beginning of an input  sequence (inclusive)
 * @param e2 an iterator to the end       of an input  sequence (exclusive)
 * @param x  an iterator to the beginning of an output sequence (inclusive)
 * @return   an iterator to the end       of an output sequence (exclusive)
 * the sequences are of decimal digits
 * output the product of the two input sequences into the output sequence
 * ([b1, e1) * [b2, e2)) => x
 */
template <typename II1, typename II2, typename FI>
FI multiplies_digits (II1 b1, II1 e1, II2 b2, II2 e2, FI x) {
    vector<int> vec1(b1, e1);
    vector<int> vec2(b2, e2);
    
    cout << "Vec1: ";
    for(int i : vec1){
        cout << i << " ";
    }
    cout << endl;
    cout << "Vec2: ";
    for(int i : vec2){
        cout << i << " ";
    }
    cout << endl;
    vector<int> total(vec1.size()+vec2.size());
    vector<int>::iterator totalEnd = total.begin() + 1;
    int shift = 0;
    for (int i = vec1.size()-1; i >= 0; --i) {
        cout << "i is: " << vec1[i] << endl;
        vector<int> product(vec2.size()+1);
        vector<int>::iterator productEnd = product.begin() + 1;
        for(int j = 0; j < vec1[i]; ++j){
            cout << "j is: " << j << endl;
            productEnd = plus_digits(product.begin(), productEnd, vec2.begin(), vec2.end(), product.begin());
            vector<int>::iterator k = product.begin();
        }
        vector<int> temp(product.size() + shift);
        vector<int>::iterator tempEnd = shift_left_digits(product.begin(), productEnd, shift, temp.begin());
        ++shift;
        totalEnd = plus_digits(total.begin(), totalEnd, temp.begin(), tempEnd, total.begin());

    }
    vector<int>::iterator i = total.begin();
    while(i != totalEnd){
        cout << "Writing " << *i << " to x" << endl;
        *x = *i;
        ++x;
        ++i;
    }
    cout << "Done storing into x" << endl;
    return x;

    /*cout << "Made vectors 1 and 2"<< endl;
    if(vec1.size() < 2 || vec2.size() < 2){
        cout << "Size vec1: " << vec1.size() << " Size vec2: " << vec2.size() << endl;
        vector<int> product(0);
        vector<int>::iterator productEnd;
        if(vec1.size() < vec2.size()){
            product.resize(vec2.size() + 1);
            productEnd = product.begin() + 1;
            for(int i = 0; i < vec1[0]; ++i){
                productEnd = plus_digits(product.begin(), productEnd, vec2.begin(), vec2.end(), product.begin());
            }
        }else{
            product.resize(vec1.size() + 1);
            productEnd = product.begin() + 1;
            for(int i = 0; i < vec2[0]; ++i){
                productEnd = plus_digits(product.begin(), productEnd, vec1.begin(), vec1.end(), product.begin());
            }
        }
        vector<int>::iterator i = product.begin();
        while(i != productEnd){
            cout << "Writing " << *i << " to x" << endl;
            *x = *i;
            ++x;
            ++i;
        }
        cout << "Done storing into x" << endl;
        return x;
    }*/
        
    /*int m = max(vec1.size(), vec2.size());
    int m2 = m/2;
    cout << "Calcualted m and m2" << endl;
    vector<int>::iterator low1B  = vec1.begin();
    vector<int>::iterator low1E  = vec1.begin() + m2;
    vector<int>::iterator high1B  = vec1.begin() + m2;
    vector<int>::iterator high1E  = vec1.end();
    vector<int>::iterator low2B  = vec2.begin();
    vector<int>::iterator low2E  = vec2.begin() + m2;
    vector<int>::iterator high2B  = vec2.begin() + m2;
    vector<int>::iterator high2E  = vec2.end();
    cout << "set up half iterators" << endl;
    vector<int> z0(2*m2);
    FI z0e = multiplies_digits(low1B, low1E, low2B, low2E, z0.begin());
    vector<int> z1(2*m2+1);
    vector<int> multi1(m2+2);
    vector<int> multi2(m2+2);
    FI one = plus_digits (low1B, low1E, high1B, high1E, multi1.begin());
    FI two = plus_digits (low2B, low2E, high2B, high2E, multi2.begin());
    FI z1e = multiplies_digits(multi1.begin(), one, multi2.begin(), two, z1.begin());
    vector<int> z2(2*m2);
    FI z2e = multiplies_digits(high1B, high1E, high2B, high2E, z2.begin());
    cout << "Done with z0, z1, z2" << endl;
    vector<int> partOne(2*m);
    FI partOneEnd = shift_left_digits (z2.begin(), z2e, 2*m2, partOne.begin());
    
    vector<int>::iterator i = partOne.begin();
    cout << "partOne: ";
    while(i != partOneEnd){
        cout << *i << " ";
        ++i;
    }
    cout << endl;

    vector<int> subOne(2*m2);
    cout << "Finished part one" <<endl;
    FI subOneEnd = minus_digits (z1.begin(), z1e, z2.begin(), z2e, subOne.begin());
    vector<int> subTwo(2*m2);
    cout << "Halfway through part two" <<endl;
    FI subTwoEnd = minus_digits (subOne.begin(), subOneEnd, z0.begin(), z0e, subTwo.begin());
    vector<int> partTwo(subTwo.size() + m2);
    FI partTwoEnd = shift_left_digits (subTwo.begin(), subTwoEnd, m2, partTwo.begin());
    cout << "Finished part two" << endl;
    vector<int> addOne(partOne.size());
    FI addOneEnd = plus_digits(partOne.begin(), partOneEnd, partTwo.begin(), partTwoEnd, addOne.begin());
    cout << "about to return at end" <<endl;
    i = addOne.begin();
    cout << "addOne: ";
    while(i != addOneEnd){
        cout << *i << " ";
        ++i;
    }
    i = z0.begin();
    cout << "z0: ";
    while(i != z0e){
        cout << *i << " ";
        ++i;
    }
    cout << endl;
    return plus_digits(addOne.begin(), addOneEnd, z0.begin(), z0e, x);*/
}

// --------------
// divides_digits
// --------------

/**
 * @param b  an iterator to the beginning of an input  sequence (inclusive)
 * @param e  an iterator to the end       of an input  sequence (exclusive)
 * @param b2 an iterator to the beginning of an input  sequence (inclusive)
 * @param e2 an iterator to the end       of an input  sequence (exclusive)
 * @param x  an iterator to the beginning of an output sequence (inclusive)
 * @return   an iterator to the end       of an output sequence (exclusive)
 * the sequences are of decimal digits
 * output the division of the two input sequences into the output sequence
 * ([b1, e1) / [b2, e2)) => x
 */
template <typename II1, typename II2, typename FI>
FI divides_digits (II1 b1, II1 e1, II2 b2, II2 e2, FI x) {
    // <your code>
    return x;}

// -------
// Integer
// -------

template < typename T, typename C = std::vector<T> >
class Integer {
    // -----------
    // operator ==
    // -----------

    /**
     * <your documentation>
     */
    friend bool operator == (const Integer& lhs, const Integer& rhs) {
        // <your code>
        return false;}

    // -----------
    // operator !=
    // -----------

    /**
     * <your documentation>
     */
    friend bool operator != (const Integer& lhs, const Integer& rhs) {
        return !(lhs == rhs);}

    // ----------
    // operator <
    // ----------

    /**
     * <your documentation>
     */
    friend bool operator < (const Integer& lhs, const Integer& rhs) {
        // <your code>
        return false;}

    // -----------
    // operator <=
    // -----------

    /**
     * <your documentation>
     */
    friend bool operator <= (const Integer& lhs, const Integer& rhs) {
        return !(rhs < lhs);}

    // ----------
    // operator >
    // ----------

    /**
     * <your documentation>
     */
    friend bool operator > (const Integer& lhs, const Integer& rhs) {
        return (rhs < lhs);}

    // -----------
    // operator >=
    // -----------

    /**
     * <your documentation>
     */
    friend bool operator >= (const Integer& lhs, const Integer& rhs) {
        return !(lhs < rhs);}

    // ----------
    // operator +
    // ----------

    /**
     * <your documentation>
     */
    friend Integer operator + (Integer lhs, const Integer& rhs) {
        return lhs += rhs;}

    // ----------
    // operator -
    // ----------

    /**
     * <your documentation>
     */
    friend Integer operator - (Integer lhs, const Integer& rhs) {
        return lhs -= rhs;}

    // ----------
    // operator *
    // ----------

    /**
     * <your documentation>
     */
    friend Integer operator * (Integer lhs, const Integer& rhs) {
        return lhs *= rhs;}

    // ----------
    // operator /
    // ----------

    /**
     * <your documentation>
     * @throws invalid_argument if (rhs == 0)
     */
    friend Integer operator / (Integer lhs, const Integer& rhs) {
        return lhs /= rhs;}

    // ----------
    // operator %
    // ----------

    /**
     * <your documentation>
     * @throws invalid_argument if (rhs <= 0)
     */
    friend Integer operator % (Integer lhs, const Integer& rhs) {
        return lhs %= rhs;}

    // -----------
    // operator <<
    // -----------

    /**
     * <your documentation>
     * @throws invalid_argument if (rhs < 0)
     */
    friend Integer operator << (Integer lhs, int rhs) {
        return lhs <<= rhs;}

    // -----------
    // operator >>
    // -----------

    /**
     * <your documentation>
     * @throws invalid_argument if (rhs < 0)
     */
    friend Integer operator >> (Integer lhs, int rhs) {
        return lhs >>= rhs;}

    // -----------
    // operator <<
    // -----------

    /**
     * <your documentation>
     */
    friend std::ostream& operator << (std::ostream& lhs, const Integer& rhs) {
        // <your code>
        return lhs << "0";}

    // ---
    // abs
    // ---

    /**
     * absolute value
     * <your documentation>
     */
    friend Integer abs (Integer x) {
        return x.abs();}

    // ---
    // pow
    // ---

    /**
     * power
     * <your documentation>
     * @throws invalid_argument if ((x == 0) && (e == 0)) || (e < 0)
     */
    friend Integer pow (Integer x, int e) {
        return x.pow(e);}

    private:
        // ----
        // data
        // ----

        C _x; // the backing container
        // <your data>

    private:
        // -----
        // valid
        // -----

        bool valid () const { // class invariant
            // <your code>
            return true;}

    public:
        // ------------
        // constructors
        // ------------

        /**
         * <your documentation>
         */
        Integer (int value) {
            // <your code>
            assert(valid());}

        /**
         * <your documentation>
         * @throws invalid_argument if value is not a valid representation of an Integer
         */
        explicit Integer (const std::string& value) {
            // <your code>
            if (!valid())
                throw std::invalid_argument("Integer::Integer()");}

        // Default copy, destructor, and copy assignment.
        // Integer (const Integer&);
        // ~Integer ();
        // Integer& operator = (const Integer&);

        // ----------
        // operator -
        // ----------

        /**
         * <your documentation>
         */
        Integer operator - () const {
            // <your code>
            return Integer(0);}

        // -----------
        // operator ++
        // -----------

        /**
         * <your documentation>
         */
        Integer& operator ++ () {
            *this += 1;
            return *this;}

        /**
         * <your documentation>
         */
        Integer operator ++ (int) {
            Integer x = *this;
            ++(*this);
            return x;}

        // -----------
        // operator --
        // -----------

        /**
         * <your documentation>
         */
        Integer& operator -- () {
            *this -= 1;
            return *this;}

        /**
         * <your documentation>
         */
        Integer operator -- (int) {
            Integer x = *this;
            --(*this);
            return x;}

        // -----------
        // operator +=
        // -----------

        /**
         * <your documentation>
         */
        Integer& operator += (const Integer& rhs) {
            // <your code>
            return *this;}

        // -----------
        // operator -=
        // -----------

        /**
         * <your documentation>
         */
        Integer& operator -= (const Integer& rhs) {
            // <your code>
            return *this;}

        // -----------
        // operator *=
        // -----------

        /**
         * <your documentation>
         */
        Integer& operator *= (const Integer& rhs) {
            // <your code>
            return *this;}

        // -----------
        // operator /=
        // -----------

        /**
         * <your documentation>
         * @throws invalid_argument if (rhs == 0)
         */
        Integer& operator /= (const Integer& rhs) {
            // <your code>
            return *this;}

        // -----------
        // operator %=
        // -----------

        /**
         * <your documentation>
         * @throws invalid_argument if (rhs <= 0)
         */
        Integer& operator %= (const Integer& rhs) {
            // <your code>
            return *this;}

        // ------------
        // operator <<=
        // ------------

        /**
         * <your documentation>
         */
        Integer& operator <<= (int n) {
            // <your code>
            return *this;}

        // ------------
        // operator >>=
        // ------------

        /**
         * <your documentation>
         */
        Integer& operator >>= (int n) {
            // <your code>
            return *this;}

        // ---
        // abs
        // ---

        /**
         * absolute value
         * <your documentation>
         */
        Integer& abs () {
            // <your code>
            return *this;}

        // ---
        // pow
        // ---

        /**
         * power
         * <your documentation>
         * @throws invalid_argument if ((this == 0) && (e == 0)) or (e < 0)
         */
        Integer& pow (int e) {
            // <your code>
            return *this;}};

#endif // Integer_h
