//
//  matrix.hpp
//  matrix
//
//  Created by Andrey Danilov on 31.03.16.
//  Copyright © 2016 Andrey Danilov. All rights reserved.
//

#ifndef Matrix_hpp
#define Matrix_hpp
#include <iostream>
#include <assert.h>
#include <initializer_list>
#include <algorithm>
#include <math.h>

template <class T>
class matrix {
private:
    T **data = nullptr;
    size_t n, m;
public:
    void set_size(size_t n, size_t m);
    matrix();
    matrix(size_t n, size_t m);
    matrix(size_t n);
    ~matrix();
    
    const T* operator[] (size_t i) const;
    T*& operator[] (size_t i);
    
    matrix<T>& operator= (std::initializer_list<T> list);
    matrix<T>& operator= (const matrix<T> &x);
    matrix<T>& operator= (const T &x);

    matrix(const matrix<T> &x);
    
    template<class T2>
    operator matrix<T2> () const;
    
    const matrix<T> operator+ (const matrix<T> &x) const;
    const matrix<T> operator- (const matrix<T> &x) const;
    const matrix<T> operator* (const matrix<T> &x) const;
    const matrix<T> operator/ (const matrix<T> &x) const;
    
    matrix<T>& operator+= (const matrix<T> &x);
    matrix<T>& operator-= (const matrix<T> &x);
    matrix<T>& operator*= (const matrix<T> &x);
    matrix<T>& operator/= (const matrix<T> &x);
    
    matrix<T> operator* (const T &x) const;
    matrix<T> operator/ (const T &x) const;
    
    matrix<T>& operator*= (const T &x);
    matrix<T>& operator/= (const T &x);
    
    T det() const;
    matrix<T> subMatrix(size_t i, size_t j) const;
    matrix<T> reverse() const;
    matrix<T> transpone() const;
    T trace() const;
    
    friend std::ostream& operator<< (std::ostream &out, const matrix<T>& x){
        for(int i = 0; i < x.n; ++i){
            for(int j = 0; j < x.m; ++j){
                out << x[i][j] << " ";
            }
            out << "\n";
        }
        return out;
    };
    
    friend std::istream& operator>> (std::istream &in, matrix<T>& x){
        in >> x.n >> x.m;
        x.set_size(x.n, x.m);
        for(int i = 0; i < x.n; ++i){
            for(int j = 0; j < x.m; ++j){
                in >> x[i][j];
            }
        }
        return in;
    }
};

template<class T>
std::ostream& operator<< (std::ostream &out, const matrix<T>& x);
template<class T>
std::istream& operator>> (std::istream &in, matrix<T>& x);

#endif /* matrix_hpp */
