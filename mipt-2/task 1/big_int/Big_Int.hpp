//
//  Big_Int.hpp
//  big_int
//
//  Created by Andrey Danilov on 05.03.16.
//  Copyright © 2016 Andrey Danilov. All rights reserved.
//

#ifndef Big_Int_hpp
#define Big_Int_hpp
#include <iostream>
#include "assert.h"
class BigInt{
private:
    unsigned char   *number = nullptr;
    bool            sign = false;
public:
    size_t          size = 0;
    
    void setSize(const size_t &newSize);
    int findLastBit() const;
public:
    BigInt();
    BigInt(const unsigned long &x);
    BigInt(const int &x);
    BigInt(const BigInt &x);
    BigInt(const char *s);
    
    ~BigInt();
    
    const BigInt& operator<<= (const int &n);
    const BigInt operator<< (const int &n) const;
    const BigInt& operator>>= (const int &n);
    const BigInt operator>> (const int &n) const;
    
    BigInt& operator= (const BigInt &x);
    BigInt& operator= (int x);
    BigInt& operator= (const unsigned long &x);
    
    const BigInt operator+ (const BigInt &x) const;
    
    const BigInt operator- () const;
    
    const BigInt operator- (const BigInt &x) const;
    
    const BigInt operator* (const BigInt &x) const;

    const BigInt operator/ (const BigInt &x) const;
    
    const BigInt operator% (const BigInt &x) const;
    
    bool operator> (const BigInt &x) const;
    bool operator>= (const BigInt &x) const;
    bool operator== (const BigInt &x) const;
    bool operator!= (const BigInt &x) const;
    bool operator< (const BigInt &x) const;
    bool operator<= (const BigInt &x) const;
    
    friend std:: istream& operator>> (std::istream &input, BigInt &x);
    friend std:: ostream& operator<< (std::ostream &output, BigInt x);
    
    void print() const;
};
std:: istream& operator>> (std::istream &input, BigInt &x);
std:: ostream& operator<< (std::ostream &output, BigInt x);

#endif /* Big_Int_hpp */
