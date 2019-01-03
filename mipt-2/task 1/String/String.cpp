//
//  String.cpp
//  String
//
//  Created by Andrey Danilov on 10.03.16.
//  Copyright © 2016 Andrey Danilov. All rights reserved.
//

#include "String.hpp"
#include <assert.h>

String:: String(){};

String:: String(const char &c){
    *this = c;
}

String:: String(const char *s){
    *this = s;
}

String:: String(const String &string){
    *this = string;
}

String:: ~String(){
    delete [] buf;
}

size_t String:: getSize() const{
    return size;
}

void String:: setSize(const size_t &newSize, const bool &cpy){
    const double k = 2;
    char* prevBuf = buf;
    size_t prevCapacity = capacity;
    if(newSize == 0){
        capacity = 0;
        size = 0;
        if(buf) delete [] buf;
        buf = nullptr;
        return;
    }
    if(capacity == 0)
        capacity = 1;
    while(newSize > capacity){
        capacity *= k;
    }
    while(newSize*k*k < capacity){
        capacity /= k;
    }
    if(prevCapacity != capacity){
        buf = new char[capacity];
    }
    
    if(cpy && prevBuf && prevBuf != buf){
        memcpy(buf, prevBuf, size > capacity ? capacity : size);
    }
    size = newSize;
    if(prevCapacity != capacity){
        delete [] prevBuf;
    }
}

const String& String:: operator= (const char &c){
    setSize(1, false);
    buf[0] = c;
    return (*this);
}

const String& String:: operator= (const char *s){
    setSize(strlen(s), false);
    memcpy(buf, s, strlen(s));
    return (*this);
}

const String& String:: operator= (const String &string){
    setSize(string.size, false);
    memcpy(buf, string.buf, size);
    return (*this);
}

const String& String:: operator+=(const char &c){
    setSize(size+1, true);
    buf[size-1] = c;
    return *this;
}

const String& String:: operator+=(const char *s){
    setSize(size + strlen(s), true);
    memcpy(buf + size - strlen(s), s, strlen(s));
    return *this;
}

const String& String:: operator+=(const String &string){
    setSize(size + string.size, true);
    memcpy(buf + size - string.size, string.buf, string.size);
    return *this;
}

const String String:: operator+ (const char &c) const{
    String result = *this;
    result += c;
    return result;
}
const String String:: operator+ (const char *s) const{
    String result = *this;
    result += s;
    return result;
}
const String String:: operator+ (const String &string) const{
    String result = *this;
    result += string;
    return result;
}

const String operator+ (const char &c, const String &string){
    return String(c) + string;
}

const String operator+ (const char *s, const String &string){
    return String(s) + string;

}

const String& String:: operator*= (const int &n){
    String startString = *this;
    for(int i = 0; i < n-1; ++i){
        *this += startString;
    }
    return *this;
}

const String String:: operator* (const int &n) const{
    String result = *this;
    result *= n;
    return result;
}

char& String:: operator[] (const size_t &n){
    return buf[n];
}

const char& String:: operator[] (const size_t &n) const{
    return buf[n];
}

std::istream& operator>> (std::istream &input, String &string){
    char c;
    
    string.setSize(0, false);
    
    while((c = getchar()) != '\n')
        string += c;
    return input;
}

std::ostream& operator<< (std::ostream &output, const String &string){
    for(int i = 0; i < string.size; ++i){
        printf("%c", string.buf[i]);
    }
    return output;
}

bool String:: operator!= (const String &string) const{
    if(size != string.size)
        return true;
    for(int i = 0; i < size; ++i){
        if(buf[i] != string.buf[i])
            return true;
    }
    return false;
}

bool String:: operator== (const String &string) const{
    return !(*this != string);
}

bool String:: operator< (const String &string) const{
    size_t minSize = size < string.size ? size : string.size;
    for(int i = 0; i < minSize; ++i){
        if(buf[i] < string.buf[i])
            return true;
        else if(buf[i] > string.buf[i])
            return false;
    }
    if(size < string.size)
        return true;
    else
        return false;
}

bool String:: operator> (const String &string) const{
    size_t minSize = size < string.size ? size : string.size;
    for(int i = 0; i < minSize; ++i){
        if(buf[i] > string.buf[i])
            return true;
        else if(buf[i] < string.buf[i])
            return false;
    }
    if(size > string.size)
        return true;
    else
        return false;
}

bool String:: operator<= (const String &string) const{
    return !(*this > string);
}

bool String:: operator>= (const String &string) const{
    return !(*this < string);
}

String& String:: cut(const size_t &begin, const size_t &lenght){
    if(begin >= size)
        return *this;
    if(begin + lenght >= size){
        setSize(begin, true);
        return *this;
    }
    memmove(buf + begin, buf + begin + lenght, size - begin - lenght);
    setSize(size-lenght, true);
    return *this;
}
String& String:: put(size_t begin, String string){
    if(begin > size)
        begin = size;
    setSize(size + string.size, true);
    memmove(buf + begin + string.size, buf + begin, string.size);
    memcpy(buf+begin, string.buf, string.size);
    return *this;
}
const String String:: select(const size_t &begin, size_t length){
    String string;
    if(begin >= size)
        return string;
    if(begin + length > size)
        length = size - begin;
    char *s = new char[length+1];
    memcpy(s, buf+begin, length);
    s[length] = '\0';
    string = s;
    return string;
}
