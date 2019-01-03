//
//  Big_Int.cpp
//  big_int
//
//  Created by Andrey Danilov on 05.03.16.
//  Copyright © 2016 Andrey Danilov. All rights reserved.
//

#include "Big_Int.hpp"
#include <stack>
#include <istream>
BigInt:: BigInt(){}

BigInt:: BigInt(const int &x){
    *this = x;
}

BigInt:: BigInt(const BigInt &x){
    *this = x;
}

BigInt:: BigInt(const char *s){
    setSize(strlen(s));
    memcpy(number, s, strlen(s));
    sign = false;
}

BigInt:: BigInt(const unsigned long &x){
    *this = x;
};

BigInt:: ~BigInt(){
    delete[] number;
}

void BigInt:: setSize(const size_t &newSize){
    size_t oldSize = size;
    size = newSize;
    unsigned char* newNumber = new unsigned char[newSize];
    memcpy(newNumber, number, oldSize < newSize ? oldSize : newSize);
    for(size_t i = oldSize; i < newSize; ++i)
        newNumber[i] = 0;
    delete[] number;
    number = newNumber;
}

int BigInt:: findLastBit() const{
    unsigned char k = 128;
    int i;
    for(i = 7; i>= -1 && !(k & number[size-1]); --i){
        k >>= 1;
    }
    return i;
}

const BigInt& BigInt:: operator<<=(const int &n){
    
    setSize(size+n/8);
    memmove(number + n/8, number, size-n/8);
    for(int i = 0; i < n/8; ++i)
        number[i] = 0;
    
    for(int i = 0; i < n%8; ++i){
        if(number[size-1] & 128){
            setSize(size+1);
        }
        bool lastBit = false;
        for(int byteNumber = (int) size-1; byteNumber >= 0; --byteNumber){
            lastBit = number[byteNumber] & 128;
            number[byteNumber] <<= 1;
            if(lastBit)
                ++number[byteNumber+1];
        }
    }
    return *this;
}

const BigInt BigInt:: operator<< (const int &n) const{
    BigInt x = *this;
    x <<= n;
    return x;
}

const BigInt& BigInt:: operator>>=(const int &n){
    memmove(number, number+n/8, size-n/8);
    setSize(size-n/8);
    for(int i = 0; i < n%8; ++i){
        number[0] &= 254;
        for(int byteNumber = 0; byteNumber < size; ++byteNumber){
            if(number[byteNumber] & 1)
                number[byteNumber-1] |= 128;
            number[byteNumber] >>= 1;
        }
        if(number[size - 1] == 0)
            setSize(size - 1);
    }
    return *this;
}

const BigInt BigInt:: operator>> (const int &n) const{
    BigInt x = *this;
    x >>= n;
    return x;
}

BigInt& BigInt:: operator= (const BigInt &x){
    setSize(x.size);
    sign = x.sign;
    memcpy(number, x.number, size);
    return (*this);
}

BigInt& BigInt:: operator= (int x){
    sign = false;
    if(x < 0){
        sign = true;
        x = -x;
    }
    setSize(sizeof(int));
    memcpy(number, &x, sizeof(int));
    while(number[size-1] == 0 && size > 1)
        setSize(size-1);
    return *this;
}

BigInt& BigInt:: operator= (const unsigned long &x){
    sign = false;
    setSize(sizeof(unsigned long));
    memcpy(number, &x, sizeof(unsigned long));
    while(number[size-1] == 0 && size > 1)
        setSize(size-1);
    return *this;
}

const BigInt BigInt:: operator+ (const BigInt &x) const {
    if(sign xor x.sign){
        return *this - -x;
    }
    BigInt max = *this, min = x;
    BigInt result;
    result.sign = sign;
    int d = 0;
    if(size < x.size){
        max = x;
        min = *this;
    }
    result.setSize(max.size);
    for(size_t i = 0; i < min.size; ++i){
        if(d + int(number[i]) + int(x.number[i]) > 255){
            result.number[i] = d + int(number[i]) + int(x.number[i]) - 256;
            d = 1;
        }
        else{
            result.number[i] = char(d + int(number[i]) + int(x.number[i]));
            d = 0;
        }
    }
    for(size_t i = min.size; i < max.size; ++i){
        if(d + int(max.number[i]) > 255){
            result.number[i] = d + int(max.number[i]) - 256;
            d = 1;
        }
        else{
            result.number[i] = d + int(max.number[i]);
            d = 0;
        }
    }
    if(d == 1){
        result.setSize(size+1);
        result.number[result.size-1] = d;
    }
    return result;
}

const BigInt BigInt:: operator- () const{
    BigInt x(*this);
    if(*this == 0)
        return x;
    x.sign = !x.sign;
    return x;
}

const BigInt BigInt:: operator- (const BigInt &x) const{
    if(x == 0)
        return (*this);
    if(sign xor x.sign){
        return *this + -x;
    }
    if((x > *this) xor sign){
        return -x - -(*this);
    }
    BigInt result;
    result.sign = sign;
    result.setSize(size);
    int d = 0;
    
    for(size_t i = 0; i < x.size; ++i){
        if(int(number[i]) - int(x.number[i]) - d < 0){
            result.number[i] = int(number[i]) - int(x.number[i]) - d + 256;
            d = 1;
        }
        else{
            result.number[i] = int(number[i]) - int(x.number[i]) - d;
            d = 0;
        }
    }
    
    for(size_t i = x.size; i < (*this).size; ++i){
        if(int((*this).number[i] - d) < 0){
            result.number[i] = int((*this).number[i]) - d + 256;
            d = 1;
        }
        else{
            result.number[i] = int((*this).number[i]) - d;
            d = 0;
        }
    }
    while(result.size > 1 && result.number[result.size-1] == 0){
        result.setSize(result.size-1);
    }
    if(result.size == 1 && result.number[0] == 0)
        result.sign = false;
    return result;
}
    
const BigInt BigInt:: operator*(const BigInt &x) const{
    BigInt result(0);
    BigInt y = *this;
    for(int byteNumber = 0; byteNumber < x.size; ++byteNumber){
        for(int bitNumber = 1; bitNumber < 256; bitNumber *= 2){
            if(x.number[byteNumber] & bitNumber){
                result = result + y;
            }
            y <<= 1;
        }
    }
    result.sign = (sign xor x.sign) && (result != 0);
    return result;
}

const BigInt BigInt:: operator/ (const BigInt &x0) const{
    BigInt result(0);
    BigInt y(*this);
    BigInt x(x0);
    bool oldXsign = x0.sign;
    x.sign = false;
    y.sign = false;
    while(x <= y){
        BigInt d = x;
        BigInt i = 1;
        int delta = int(y.size*8) - int(d.size*8) + y.findLastBit() - d.findLastBit();
        d <<= delta;
        i <<= delta;
        if(d > y){
            d >>= 1;
            i >>= 1;
        }
        y = y - d;
        result = result + i;
    }
    result.sign = (sign xor oldXsign) && (result != 0);
    return result;
}

const BigInt BigInt:: operator% (const BigInt &x0) const{
    BigInt result(*this);
    BigInt x(x0);
    bool oldXsign = x0.sign;
    x.sign = false;
    result.sign = false;
    while(x <= result){
        BigInt d = x;
        int delta = int(result.size*8) - int(d.size*8) + result.findLastBit() - d.findLastBit();
        d <<= delta;
        if(d > result){
            d >>= 1;
        }
        result = result - d;
    }
    if(this->sign xor oldXsign && result != 0){
        result = x - result;
    }
    return result;
}

bool BigInt:: operator> (const BigInt &x) const{
    if(sign != x.sign){
        return sign < x.sign;
    }
    if(size != x.size){
        return (size > x.size) xor sign;
    }
    for(size_t i = size-1; i < size; --i){
        if(number[i] > x.number[i]){
            return !sign;
        }
        else if(number[i] < x.number[i]){
            return sign;
        }
    }
    return false;
}

bool BigInt:: operator>= (const BigInt &x) const{
    return !(*this < x);
}

bool BigInt:: operator==(const BigInt &x) const{
    if(size != x.size || sign != x.sign)
        return false;
    for(int i = 0; i < size; ++i){
        if(number[i] != x.number[i])
            return false;
    }
    return true;
}

bool BigInt:: operator!= (const BigInt &x) const{
    return !(*this == x);
}

bool BigInt:: operator<(const BigInt &x) const{
    if(sign != x.sign){
        return sign > x.sign;
    }
    if(size != x.size){
        return (size < x.size) xor sign;
    }
    for(size_t i = size-1; i < size; --i){
        if(number[i] < x.number[i]){
            return !sign;
        }
        else if(number[i] > x.number[i]){
            return sign;
        }
    }
    return false;
}

bool BigInt:: operator<= (const BigInt &x) const{
    return !(*this > x);
}

std:: istream& operator>> (std::istream &input, BigInt &x){
    char c;
    x = 0;
    BigInt buf;
    //c = getchar();
    input.get(c);
    x.sign = false;
    bool sign = false;
    if(c == '-'){
        sign = true;
    }
    else if(c >= '0' && c <= '9')
        x = c - '0';
    
    while(true){
        input.get(c);
        if(c == '\n') break;
        assert(c >= '0' && c <= '9');
        buf = c - '0';
        x = x*10 + buf;
    }
    x.sign = sign;
    
    return input;
}

std:: ostream& operator<< (std::ostream &output, BigInt x){
    std::stack <unsigned long> a;
    if(x == 0){
        output << 0;
        return output;
    }
    if(x < 0){
        output << "-";
        x = -x;
    }
    while(x > 0){
        BigInt y = x% (unsigned long) 10e18;
        unsigned long z = 0;
        memcpy(&z, y.number, y.size);
        a.push(z);
        x = x / (unsigned long) 10e18;
    }
    while(!a.empty()){
        output << a.top();
        a.pop();
    }
    return output;
}

void BigInt:: print() const{
    long x = 0;
    long k = 1;
    int max = sizeof(long) > size ? int(size) : sizeof(long);
    for(int i = 0; i < max; ++i){
        x += k*number[i];
        k *= 256;
    }
    if(sign)
        x = -x;
    printf("%ld\n", x);
}