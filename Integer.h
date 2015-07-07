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
#include <algorithm>    // std::reverse

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
    advance(b, n);
    x = copy(b, e, x);
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
    FI originalX = x;
    advance(x, n);
    FI finalX = copy(b, e, x);
    fill(originalX, x, 0);
    return finalX;}


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
    int carry = 0;
    int plus1 = 0;
    int plus2 = 0;
    int num = 0;
    while (b1 != e1 || b2 != e2) {
        if (b1 == e1) {
            // b1 done, rest are from b2
            plus1 = 0;
            plus2 = *b2;
            ++b2;
        }
        else if (b2 == e2) {
            // b2 done, rest are from b1
            plus1 = *b1;
            plus2 = 0;
            ++b1;
        }
        else {
            // both have digits
            plus1 = *b1;
            plus2 = *b2;
            ++b1;
            ++b2;
        }
        num = plus1 + plus2 + carry;
        carry = num / 10;
        *x = num % 10;
        ++x;
    }
    if (carry) {
        *x = carry;
        ++x;
    }
    return x;
}

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
 * requirement: first sequence > second sequence => positive answer
 * output the difference of the two input sequences into the output sequence
 * ([b1, e1) - [b2, e2)) => x
 */
template <typename II1, typename II2, typename FI>
FI minus_digits (II1 b1, II1 e1, II2 b2, II2 e2, FI x) {
    FI originalX = x;
    int zeroCount = 0;
    int borrow = 0;
    int sub1 = 0;
    int sub2 = 0;
    bool empty = true;
    // b2 guaranteed to reach end before or same time as b1
    while (b1 != e1) {
        if (b2 == e2) {
            // b2 done, rest are from b1
            sub1 = *b1;
            sub2 = 0;
            ++b1;
            if (borrow) {
                sub1 -= borrow;
                borrow = 0;
            }
            if (sub1 == 0 && b1 == e1) {
                break;
            }
        }
        else {
            // both have digits
            sub1 = *b1;
            sub2 = *b2;
            ++b1;
            ++b2;
            if (borrow) {
                sub1 -= borrow;
                borrow = 0;
            }
        }
        if (sub1 < sub2) {
            borrow++;
            sub1 += 10;
        }
        if ((sub1-sub2) != 0 || !empty) {
            if (b1 == e1 && sub1-sub2 == 0) {
                break;
            }
            *x = sub1 - sub2;
            ++x;
            empty = false;
        }
        else {
            zeroCount++;
        }
    }
    if (empty) {
        // diff was 0
        *x = 0;
        ++x;
    }
    else if (zeroCount){
        x = shift_right_digits(originalX, x, zeroCount, originalX);
    }
    return x;
}

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

    /*cout << "vec1: ";
    for(int i : vec1){
        cout << i << " ";
    }
    cout << endl;
    cout << "vec2: ";
    for(int i : vec2){
        cout << i << " ";
    }
    cout << endl;*/

    vector<int> total(vec1.size()+vec2.size());
    vector<int>::iterator totalEnd = total.begin() + 1;

    //cout << "Made vectors 1 and 2"<< endl;
    if(vec1.size() < 2 || vec2.size() < 2){
        //cout << "Size vec1: " << vec1.size() << " Size vec2: " << vec2.size() << endl;
        vector<int> product(0);
        vector<int>::iterator productEnd;
        if(vec1.size() < vec2.size()){
            if(vec1.size() == 0){
                product = vec2;
                productEnd = product.end();
            }else{
                product.resize(vec2.size() + 1);
                productEnd = product.begin() + 1;
                for(int i = 0; i < vec1[0]; ++i){
                    productEnd = plus_digits(product.begin(), productEnd, vec2.begin(), vec2.end(), product.begin());
                }
            }
        }else{
            if(vec2.size() == 0){
                product = vec1;
                productEnd = product.end();
            }else{
                product.resize(vec1.size() + 1,0);
                productEnd = product.begin() + 1;
                vector<int>::iterator g = product.begin();
                for(int i = 0; i < vec2[0]; ++i){
                    //cout << "product digits: " << productEnd-product.begin() << endl;
                    productEnd = plus_digits(product.begin(), productEnd, vec1.begin(), vec1.end(), product.begin());
                }
            }
        }
        vector<int>::iterator i = product.begin();
        while(i != productEnd){
            //cout << "Writing " << *i << " to x" << endl;
            *x = *i;
            ++x;
            ++i;
        }
        //cout << "Done storing into x" << endl;
        return x;
    }
        
    int m = max(vec1.size(), vec2.size());
    int m2 = ceil(m/2.0);
    if(min(vec1.size(), vec2.size()) <= m2){
        m2 = min(vec1.size(), vec2.size()) - 1; 
    }
    //cout << "m2: " << m2 << " m: " << m << endl;
    //cout << "Calcualted m and m2" << endl;
    vector<int>::iterator low1B  = vec1.begin();
    vector<int>::iterator low1E  = vec1.begin() + m2;
    vector<int>::iterator high1B  = vec1.begin() + m2;
    vector<int>::iterator high1E  = vec1.end();
    vector<int>::iterator low2B  = vec2.begin();
    vector<int>::iterator low2E  = vec2.begin() + m2;
    vector<int>::iterator high2B  = vec2.begin() + m2;
    vector<int>::iterator high2E  = vec2.end();
    //cout << "set up half iterators" << endl;
    vector<int> z0(2*m);
    vector<int>::iterator z0e = multiplies_digits(low1B, low1E, low2B, low2E, z0.begin());
    //cout << "done with z0" << endl;
    vector<int> z1(2*m+1);
    vector<int> multi1(m+2);
    vector<int> multi2(m+2);
    vector<int>::iterator one = plus_digits (low1B, low1E, high1B, high1E, multi1.begin());
    /*vector<int>::iterator i = multi1.begin();
    cout << "multi1: ";
    while(i != one){
        cout << *i << " ";
        ++i;
    }
    cout << endl;*/
    vector<int>::iterator two = plus_digits (low2B, low2E, high2B, high2E, multi2.begin());
    /*i = multi2.begin();
    cout << "multi2: ";
    while(i != two){
        cout << *i << " ";
        ++i;
    }
    cout << endl;*/
    vector<int>::iterator z1e = multiplies_digits(multi1.begin(), one, multi2.begin(), two, z1.begin());
    //cout << "done with z1" << endl;
    vector<int> z2(2*m);
    vector<int>::iterator z2e = multiplies_digits(high1B, high1E, high2B, high2E, z2.begin());
    //cout << "done with z2" << endl;
    vector<int> partOne(2*m);
    vector<int>::iterator partOneEnd = shift_right_digits (z2.begin(), z2e, 2*m2, partOne.begin());
    
    /*i = partOne.begin();
    cout << "partOne: ";
    while(i != partOneEnd){
        cout << *i << " ";
        ++i;
    }
    cout << endl;*/

    vector<int> subOne(2*m);
    /*cout << "Finished part one" <<endl;
    i = z1.begin();
    cout << "z1: ";
    while(i != z1e){
        cout << *i << " ";
        ++i;
    }
    cout << endl;
    i = z2.begin();
    cout << "z2: ";
    while(i != z2e){
        cout << *i << " ";
        ++i;
    }
    cout << endl;*/
    vector<int>::iterator subOneEnd = minus_digits (z1.begin(), z1e, z2.begin(), z2e, subOne.begin());
    /*i = subOne.begin();
    cout << "subOne: ";
    while(i != subOneEnd){
        cout << *i << " ";
        ++i;
    }
    cout << endl;
    i = z0.begin();
    cout << "z0: ";
    while(i != z0e){
        cout << *i << " ";
        ++i;
    }
    cout << endl;*/
    vector<int> subTwo(2*m);
    //cout << "Halfway through part two" <<endl;
    vector<int>::iterator subTwoEnd = minus_digits (subOne.begin(), subOneEnd, z0.begin(), z0e, subTwo.begin());
    /*i = subTwo.begin();
    cout << "subTwo: ";
    while(i != subTwoEnd){
        cout << *i << " ";
        ++i;
    }
    cout << endl;*/
    vector<int> partTwo(subTwo.size() + m2);
    vector<int>::iterator partTwoEnd = shift_right_digits (subTwo.begin(), subTwoEnd, m2, partTwo.begin());
    /*i = partTwo.begin();
    cout << "partTwo: ";
    while(i != partTwoEnd){
        cout << *i << " ";
        ++i;
    }
    cout << "Finished part two" << endl;*/
    vector<int> addOne(partOne.size());
    vector<int>::iterator addOneEnd = plus_digits(partOne.begin(), partOneEnd, partTwo.begin(), partTwoEnd, addOne.begin());
    /*cout << "about to return at end" <<endl;
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
    cout << endl;*/
    return plus_digits(addOne.begin(), addOneEnd, z0.begin(), z0e, x);
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
    //simpile solution is to use subtraction 
    vector<int> numerator(b1, e1);
    vector<int> denominator(b2, e2);
    vector<int> quotient(numerator.size());
    vector<int> one(1, 1);
    vector<int>::iterator quotientEnd = quotient.begin() + 1;
    vector<int>::iterator numEnd = numerator.end();
    
    while (true) {
        if((numEnd - numerator.begin()) < denominator.size()){
            //cout << "in if" << endl;
            break;
        }
        else if ((numEnd - numerator.begin()) == denominator.size()){
            //cout << "In that one else if" << endl;
            for(int i = (numEnd - numerator.begin()) - 1; i >= 0; --i){
                //cout << "numerator: " << numerator[i] << " denom: " << denominator[i] << endl;
                if (numerator[i] > denominator[i])
                    break;
                else if((numerator[i] < denominator[i])){
                    //cout << "In that one final if" << endl;
                    goto finish;
                }
            }
        }

        numEnd = minus_digits(numerator.begin(), numEnd, denominator.begin(), denominator.end(), numerator.begin());
        quotientEnd = plus_digits(quotient.begin(), quotientEnd, one.begin(), one.end(), quotient.begin());
        vector<int>::iterator i = quotient.begin();
        /*cout << "Quotient: ";
        while(i != quotientEnd){
            cout << *i << " ";
            ++i;
        }
        cout << endl;
        i = numerator.begin();
        cout << "Numerator: ";
        while(i != numEnd){
            cout << *i << " ";
            ++i;
        }
        cout << endl;*/
        
    }
    finish:
    /*vector<int>::iterator i = quotient.begin();
    while(i != quotientEnd){
        cout << "Writing " << *i << " to x" << endl;
        ++i;
    }
    cout << "end numb" << endl;*/
    return copy(quotient.begin(), quotientEnd, x);
}

// -------
// Integer
// -------

template < typename T, typename C = std::vector<T> >
class Integer {
    // -----------
    // operator ==
    // -----------

    /**
     * @param lhs   Integer to be compared
     * @param rhs   Integer to be compared
     * @return      true if lhs equals rhs, false otherwise
     */
    friend bool operator == (const Integer& lhs, const Integer& rhs) {
        return !(lhs < rhs) && !(lhs > rhs);}

    // -----------
    // operator !=
    // -----------

    /**
     * @param lhs   Integer to be compared
     * @param rhs   Integer to be compared
     * @return      true if lhs does not equal rhs, false otherwise
     */
    friend bool operator != (const Integer& lhs, const Integer& rhs) {
        return !(lhs == rhs);}

    // ----------
    // operator <
    // ----------

    /**
     * @param lhs   Integer to be compared
     * @param rhs   Integer to be compared
     * @return      true if lhs is less than rhs, false otherwise
     */
    friend bool operator < (const Integer& lhs, const Integer& rhs) {
        if (lhs._n && !rhs._n)
            return true;
        if (!lhs._n && rhs._n)
            return false;
        bool less = true;
        if (lhs._n && rhs._n)
            less = false;
        if(lhs._x.size() > rhs._x.size()){
            return !less;
        }else if(lhs._x.size() < rhs._x.size()){
            return less;
        }else{
            for(int i = lhs._x.size()-1; i > 0; --i){
                if(lhs._x[i] > rhs._x[i]){
                    return !less;
                }else if(lhs._x[i] < rhs._x[i]){
                    return less;
                }
            }
        }
        return false;}

    // -----------
    // operator <=
    // -----------

    /**
     * @param lhs   Integer to be compared
     * @param rhs   Integer to be compared
     * @return      true if lhs is less than or equal to rhs, false otherwise
     */
    friend bool operator <= (const Integer& lhs, const Integer& rhs) {
        return !(rhs < lhs);}

    // ----------
    // operator >
    // ----------

    /**
     * @param lhs   Integer to be compared
     * @param rhs   Integer to be compared
     * @return      true if lhs is greater than rhs, false otherwise
     */
    friend bool operator > (const Integer& lhs, const Integer& rhs) {
        return (rhs < lhs);}

    // -----------
    // operator >=
    // -----------

    /**
     * @param lhs   Integer to be compared
     * @param rhs   Integer to be compared
     * @return      true if lhs is greater than or equal to rhs, false otherwise
     */
    friend bool operator >= (const Integer& lhs, const Integer& rhs) {
        return !(lhs < rhs);}

    // ----------
    // operator +
    // ----------

    /**
     * @param lhs   Integer to be compared
     * @param rhs   Integer to be compared
     * @return      Integer value of lhs + rhs
     */
    friend Integer operator + (Integer lhs, const Integer& rhs) {
        return lhs += rhs;}

    // ----------
    // operator -
    // ----------

    /**
     * @param lhs   Integer to be compared
     * @param rhs   Integer to be compared
     * @return      Integer value of lhs - rhs
     */
    friend Integer operator - (Integer lhs, const Integer& rhs) {
        return lhs -= rhs;}

    // ----------
    // operator *
    // ----------

    /**
     * @param lhs   Integer to be compared
     * @param rhs   Integer to be compared
     * @return      Integer value of lhs - rhs
     */
    friend Integer operator * (Integer lhs, const Integer& rhs) {
        return lhs *= rhs;}

    // ----------
    // operator /
    // ----------

    /**
     * @param lhs   Integer to be compared
     * @param rhs   Integer to be compared
     * @return      true if lhs equals rhs, false otherwise
     * @throws invalid_argument if (rhs == 0)
     */
    friend Integer operator / (Integer lhs, const Integer& rhs) {
        return lhs /= rhs;}

    // ----------
    // operator %
    // ----------

    /**
     * @param lhs   Integer to be compared
     * @param rhs   Integer to be compared
     * @return      true if lhs equals rhs, false otherwise
     * @throws invalid_argument if (rhs <= 0)
     */
    friend Integer operator % (Integer lhs, const Integer& rhs) {
        return lhs %= rhs;}

    // -----------
    // operator <<
    // -----------

    /**
     * @param lhs   Integer to be compared
     * @param rhs   Integer to be compared
     * @return      true if lhs equals rhs, false otherwise
     * @throws invalid_argument if (rhs < 0)
     */
    friend Integer operator << (Integer lhs, int rhs) {
        return lhs <<= rhs;}

    // -----------
    // operator >>
    // -----------

    /**
     * @param lhs   Integer to be compared
     * @param rhs   Integer to be compared
     * @return      true if lhs equals rhs, false otherwise
     * @throws invalid_argument if (rhs < 0)
     */
    friend Integer operator >> (Integer lhs, int rhs) {
        return lhs >>= rhs;}

    // -----------
    // operator <<
    // -----------

    /**
     * @param lhs   ostream to write to
     * @param rhs   Integer to be written
     * @return      true if lhs equals rhs, false otherwise
     */
    friend std::ostream& operator << (std::ostream& lhs, const Integer& rhs) {
        for (int i = rhs._x.size()-1; i >= 0; --i) {
            lhs << rhs._x[i];
        }
        return lhs;}

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
        bool _n; //for negativity. 

    private:
        // -----
        // valid
        // -----

        bool valid () const { // class invariant
            // each digit should be in [0,9]
            for (int digit : _x)
                if (digit < 0 || digit > 9)
                    return false;
            // there should be no leading 0s
            if ((_x.size() != 1) && !(_x.front()))
                return false;
            return true;}

    public:
        // ------------
        // constructors
        // ------------

        /**
         * <your documentation>
         */
        Integer (int value) {
            if (value < 0)
                _n = true;
            else
                _n = false;
            value = std::abs(value);

            int i = 1000000000;
            for (; i > 1; i/=10) {
                if (value / i != 0)
                    break;
            }
            for (; i>0; i/=10) {
                _x.push_back(value/i);
                value %= i;
            }
            reverse(_x.begin(), _x.end());
            assert(valid());
        }

        /**
         * <your documentation>
         * @throws invalid_argument if value is not a valid representation of an Integer
         */
        explicit Integer (const std::string& value) {
            string s(value);
            if(value[0] == '-'){
                _n = true;
                s = value.substr(1);
            }else{
                _n = false;
            }
            for(char c : s)
                _x.push_back(int(c-'0'));
            reverse(_x.begin(), _x.end());
            if (!valid())
                throw std::invalid_argument("Integer::Integer()");
        }
            
            

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
            Integer x = *this;
            x._n = !x._n;
            return x;}

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
            if (_n && !rhs._n) {
                
            }
            else {
                //adding negative to negative => neg
                //    or positive to positive => pos
                _x.push_back(0);
                typename C::iterator addEnd = plus_digits(_x.begin(), _x.end()-1, rhs._x.begin(), rhs._x.end(), _x.begin());
                if(_x.end() != addEnd){
                    //if so we did not use the last place.
                    _x.pop_back();
                }
            }
            return *this;}

        // -----------
        // operator -=
        // -----------

        /**
         * <your documentation>
         */
        Integer& operator -= (const Integer& rhs) {
            return *this += -rhs;

            typename C::iterator minusEnd = minus_digits(_x.begin(), _x.end(), rhs._x.begin(), rhs._x.end(), _x.begin());
            //remove the empty space if there is one. 
            if(*minusEnd == 0){
                _x.pop_back();
            }
            return *this;}

        // -----------
        // operator *=
        // -----------

        /**
         * <your documentation>
         */
        Integer& operator *= (const Integer& rhs) {
            // check for negativity of answer
            if ((_n && !rhs._n) || (!_n && rhs._n))
                _n = true;
            else
                _n = false;

            C product(_x.size()+rhs._x.size());
            typename C::iterator productEnd = multiplies_digits(_x.begin(), _x.end(), rhs._x.begin(), rhs._x.end(), product.begin()); 
            _x = C(product.begin(), productEnd);

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
            if (((this == 0) && (e == 0)) || (e < 0))
                throw invalid_argument("exponent < 0 or exponent = 0 and Integer = 0");
            if (e != 0) {
                Integer<int, C> product = 1;
                product *= *this;
                --e;
                while( e != 0){
                    *this *= product;
                    --e;
                }
            }
            else {
                _x = C(1, 1);
            }
            return *this;}};

#endif // Integer_h
