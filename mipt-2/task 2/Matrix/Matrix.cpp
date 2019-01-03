//
//  Matrix.cpp
//  Matrix
//
//  Created by Andrey Danilov on 31.03.16.
//  Copyright © 2016 Andrey Danilov. All rights reserved.
//

#include "Matrix.hpp"

template<class T>
void matrix<T>:: set_size(size_t n, size_t m){
    
    if(data != nullptr){
        for(int i = 0; i < this->n; ++i){
            delete[] data[i];
        }
        delete[] data;
    }
    if(n*m == 0)
        data = nullptr;
    else{
        data = new T* [n];
        this->n = n;
        this->m = m;
        for(int i = 0; i < n; ++i){
            data[i] = new T [m];
        }
    }
}

template <class T>
matrix<T>::matrix(){
    n = m = 0;
};

template <class T>
matrix<T>::matrix(size_t n, size_t m){
    set_size(n, m);
};

template <class T>
matrix<T>::matrix(size_t n)
:matrix(n, n){};

template <class T>
matrix<T>::~matrix(){
    for(int i = 0; i < n; ++i){
        delete[] data[i];
    }
    delete[] data;
};

template <class T>
const T* matrix<T>::operator[] (size_t i) const{
    return data[i];
};

template <class T>
T*& matrix<T>::operator[] (size_t i){
    return data[i];
};

template <class T>
matrix<T>& matrix<T>::operator= (std::initializer_list<T> list){
    assert(n*m == list.size());
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < m; ++j){
            (*this)[i][j] = *(list.begin()+i*m + j);
        }
    }
    return *this;
};

template <class T>
matrix<T>& matrix<T>::operator= (const matrix<T> &x){
    if(n != x.n || m != x.m){
        this-> set_size(x.n, x.m);
    }
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < m; ++j){
            (*this)[i][j] = x[i][j];
        }
    }

    return *this;
};

template<class T>
matrix<T>& matrix<T>::operator= (const T &x){
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < m; ++j)
            (*this)[i][j] = (i == j)*x;
    return *this;
}

template <class T>
matrix<T>::matrix(const matrix<T> &x){
    *this = x;
}

template<class T>
template<class T2>
matrix<T>::operator matrix<T2>() const{
    matrix<T2> result(n, m);
    if(std::is_floating_point<T>::value && std::is_integral<T2>::value){
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; ++j){
                result[i][j] = round((*this)[i][j]);
            }
        }
    }
    else{
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; ++j){
                result[i][j] = (*this)[i][j];
            }
        }
    }
    return result;
}

template <class T>
const matrix<T> matrix<T>::operator+ (const matrix<T> &x) const{
    assert(n == x.n && m == x.m);
    matrix<T> result(n, m);
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < m; ++j){
            result[i][j] = (*this)[i][j] + x[i][j];
        }
    }
    return result;
}

template <class T>
const matrix<T> matrix<T>::operator- (const matrix<T> &x) const{
    assert(n == x.n && m == x.m);
    matrix<T> result(n, m);
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < m; ++j){
            result[i][j] = (*this)[i][j] - x[i][j];
        }
    }
    return result;
}

template <class T>
const matrix<T> matrix<T>::operator* (const matrix<T> &x) const{
    assert(m == x.n);
    matrix<T> result(n, x.m);
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < x.m; ++j){
            T summ = 0;
            for(int k = 0; k < m; ++k)
                summ += (*this)[i][k]*x[k][j];
            result[i][j] = summ;
        }
    }
    return result;
}

template <class T>
const matrix<T> matrix<T>::operator/ (const matrix<T> &y) const{
    matrix x(y.reverse());
    return *this * x;
}
template<class T>
matrix<T>& matrix<T>::operator+= (const matrix<T> &x){
    *this = (*this)+x;
    return *this;
}

template<class T>
matrix<T>& matrix<T>::operator-= (const matrix<T> &x){
    *this = (*this)-x;
    return *this;
}

template<class T>
matrix<T>& matrix<T>::operator*= (const matrix<T> &x){
    *this = (*this)*x;
    return *this;
}

template<class T>
matrix<T>& matrix<T>::operator/= (const matrix<T> &x){
    *this = (*this)/x;
    return *this;
}

template<class T>
matrix<T> matrix<T>::operator* (const T &x) const{
    matrix result(*this);
    result *= x;
    return result;
}

template<class T>
matrix<T> matrix<T>::operator/ (const T &x) const{
    matrix result(*this);
    result /= x;
    return result;
}

template<class T>
matrix<T>& matrix<T>::operator*= (const T &x){
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < m; ++j){
            (*this)[i][j] = (*this)[i][j]*x;
        }
    }
    return *this;
}

template<class T>
matrix<T>& matrix<T>::operator/= (const T &x){
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < m; ++j){
            (*this)[i][j] = (*this)[i][j]/x;
        }
    }
    return *this;
}

template<class T>
T matrix<T>::det() const{
    assert(n == m);
    if(std::is_integral<T>::value){
        matrix<double> x = *this;
        double result = 1;
        
        for(int i = 0; i < n; ++i){
            if(x[i][i] == 0){
                for(int j = i; j < n && x[i][i] == 0; ++j){
                    if(x[j][i] != 0){
                        std::swap(x[i], x[j]);
                        if(i%2 != j%2)
                            result *= -1;
                    }
                }
                if(x[i][i] == 0)
                    return 0;
            }
            for(int j = i+1; j < n; ++j){
                double factor = x[j][i]/x[i][i];
                for(int k = i; k < n; ++k){
                    x[j][k] -= factor*x[i][k];
                }
            }
        }
        for(int i = 0; i < n; ++i){
            result *= x[i][i];
        }
        return round(result);
    }
    else{
        matrix<T> x = *this;
        T result = 1;
        for(int i = 0; i < n; ++i){
            if(x[i][i] == 0){
                for(int j = i; j < n && x[i][i] == 0; ++j){
                    if(x[j][i] != 0){
                        std::swap(x[i], x[j]);
                        if(i%2 != j%2)
                            result *= -1;
                    }
                }
                if(x[i][i] == 0)
                    return 0;
            }
            for(int j = i+1; j < n; ++j){
                T factor = x[j][i]/x[i][i];
                for(int k = i; k < n; ++k){
                    x[j][k] -=factor*x[i][k];
                }
            }
        }
        for(int i = 0; i < n; ++i){
            result *= x[i][i];
        }
        return result;
    }
}

template<class T>
matrix<T> matrix<T>:: subMatrix(size_t i, size_t j) const{
    assert(n > 1 && m > 1 && i < n && j < m);
    matrix<T> result(n-1, m-1);
    for(int p = 0; p < n; ++p){
        for(int q = 0; q < m; ++q){
            if(q < i){
                if(p < j)
                    result[q][p] = (*this)[q][p];
                if(p > j)
                    result[q][p-1] = (*this)[q][p];
            }
            if(q > i){
                if(p < j)
                    result[q-1][p] = (*this)[q][p];
                if(p > j)
                    result[q-1][p-1] = (*this)[q][p];
            }
        }
    }
    return result;
}

template<class T>
matrix<T> matrix<T>::reverse() const{
    assert(n == m);
    assert(this->det());
    matrix<T> result(n);
    T k = 1;
    for(int i = 0; i < n; ++i){
        int k2 = k;
        k *= -1;
        for(int j = 0; j < n; ++j){
            result[j][i] = k2*(*this).subMatrix(i, j).det();
            k2 *= -1;
        }
    }
    return result/(*this).det();
}

template<class T>
matrix<T> matrix<T>:: transpone() const{
    matrix<T> result(m, n);
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < m; ++j)
            result[j][i] = (*this)[i][j];
    return result;
}

template<class T>
T matrix<T>::trace() const{
    assert(n == m);
    T result = 0;
    for(int i = 0; i < n; ++i)
        result += (*this)[i][i];
    return result;
}

template<class T>
T power(T x, unsigned long p){
    if(p == 0) return 1;
    T result(x);
    result = 1;
    while (p){
        if(p & 1)
            result *= x;
        x *= x;
        p >>= 1;
    }
    return result;
}