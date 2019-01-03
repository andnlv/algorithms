//
//  String.hpp
//  String
//
//  Created by Andrey Danilov on 10.03.16.
//  Copyright © 2016 Andrey Danilov. All rights reserved.
//

#ifndef String_hpp
#define String_hpp

#include <stdio.h>
#include <iostream>

class String{
private:
    size_t  size = 0,
            capacity = 0;
    char*   buf = nullptr;
    
    void    setSize(const size_t &newSize, const bool &cpy);
public:
    String();
    String(const char &c);
    String(const char *s);
    String(const String &string);
    
    ~String();
    
    size_t getSize() const;
    
    const String& operator= (const char &c);
    const String& operator= (const char *s);
    const String& operator= (const String &string);
    
    const String& operator+= (const char &c);
    const String& operator+= (const char *s);
    const String& operator+= (const String &string);
    
    const String operator+ (const char &c) const;
    const String operator+ (const char *s) const;
    const String operator+ (const String &string) const;
    friend const String operator+ (const char &c, const String &string);
    friend const String operator+ (const char *s, const String &string);
    
    const String& operator*= (const int &n);
    
    const String operator* (const int &n) const;
    
    char& operator[] (const size_t &n);
    const char& operator[] (const size_t &n) const;
    
    friend std::istream& operator>> (std::istream &input, String &string);
    friend std::ostream& operator<< (std::ostream &output, const String &string);
    
    bool operator!= (const String &string) const;
    bool operator== (const String &string) const;
    bool operator< (const String &string) const;
    bool operator> (const String &string) const;
    bool operator<= (const String &string) const;
    bool operator>= (const String &string) const;
    
    String& cut(const size_t &begin, const size_t &lenght); // вырезает из строки кусок
    String& put(size_t begin, String string); // вставляет в строку кусок
    const String select(const size_t &begin, size_t lenght); // возращает кусок строки
};

std::istream& operator>> (std::istream &input, String &string);
std::ostream& operator<< (std::ostream &output, const String &string);

const String operator+ (const char &c, const String &string);
const String operator+ (const char *s, const String &string);

#endif /* String_hpp */
