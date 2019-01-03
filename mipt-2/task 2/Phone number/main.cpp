//
//  main.cpp
//  Phone number
//
//  Created by Andrey Danilov on 08.04.16.
//  Copyright © 2016 Andrey Danilov. All rights reserved.
//

#include <iostream>
#include <assert.h>
#include <algorithm>
#include <math.h>
#include <stack>
#include <stack>
#include <vector>
using namespace std;
class BigInt{
private:
    vector<int> number;
public:
    BigInt(){};
    BigInt(int x){
        number.clear();
        while(x){
            number.push_back(x%10);
            x /= 10;
        }
    }
    BigInt operator+ (const BigInt &x) const{
        int d = 0;
        const vector<int> &a = this->number;
        const vector<int> &b = x.number;
        BigInt result;
        vector<int> &c = result.number;
        int i = 0;
        for(; i < a.size() && i < b.size(); ++i){
            c.push_back((a[i]+b[i]+d)%10);
            d = (a[i]+b[i]+d)/10;
        }
        for(; i < a.size(); ++i){
            c.push_back((a[i]+d)%10);
            d = (a[i]+d)/10;
        }
        for(; i < b.size(); ++i){
            c.push_back((b[i]+d)%10);
            d = (b[i]+d)/10;
        }
        if(d)
            c.push_back(d);
        return result;
    }
    
    BigInt operator* (const BigInt &x) const{
        BigInt result;
        BigInt y;
        int d;
        for(int i = 0; i < x.number.size(); ++i){
            y = 0;
            for(int j = 0; j < i; ++j)
                y.number.push_back(0);
            d = 0;
            for(int j = 0; j < number.size(); ++j){
                y.number.push_back((x.number[i]*number[j] + d)%10);
                d = (x.number[i]*number[j] + d)/10;
            }
            
            if(d)
                y.number.push_back(d);
            result = result + y;
        }
        
        return result;
    }
    friend ostream& operator<< (ostream& out, const BigInt &x);
};

ostream& operator<< (ostream& out, const BigInt &x){
    if(x.number.size() == 0)
        out << 0;
    for(long i = x.number.size()-1; i >= 0; --i){
        out << x.number[i];
    }
    return out;
}

//#############################################################

template <class T>
class matrix {
private:
    T **data;
    size_t  n,
            m;
public:
    void set_size(size_t n, size_t m);
    matrix();
    matrix(size_t n, size_t m);
    matrix(size_t n);
    ~matrix();
    
    const T* operator[] (size_t i) const;
    T*& operator[] (size_t i);
    
    matrix<T>& operator= (const matrix<T> &x);
    matrix<T>& operator= (const T &x);
    
    matrix(const matrix<T> &x);
    
    const matrix<T> operator+ (const matrix<T> &x) const;
    const matrix<T> operator- (const matrix<T> &x) const;
    const matrix<T> operator* (const matrix<T> &x) const;
    
    matrix<T>& operator+= (const matrix<T> &x);
    matrix<T>& operator-= (const matrix<T> &x);
    matrix<T>& operator*= (const matrix<T> &x);
    
    matrix<T> operator* (const T &x) const;
    
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


template<class T>
void matrix<T>:: set_size(size_t n, size_t m){
    
    if(data != 0){
        for(int i = 0; i < this->n; ++i){
            delete[] data[i];
        }
        delete[] data;
    }
    if(n*m == 0)
        data = 0;
    else{
        this->n = n;
        this->m = m;
        data = new T* [n];
        for(int i = 0; i < n; ++i){
            data[i] = new T [m];
        }
    }
}

template <class T>
matrix<T>::matrix(){
    n = m = 0;
    data = 0;
};

template <class T>
matrix<T>::matrix(size_t n, size_t m){
    this->n = this->m = 0;
    data = 0;
    set_size(n, m);
};

template <class T>
matrix<T>::matrix(size_t n){
    this->n = m = 0;
    data = 0;
    set_size(n, n);
};

template <class T>
matrix<T>::~matrix(){
    if(data == 0) return;
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

//template <class T>
//matrix<T>& matrix<T>::operator= (std::initializer_list<T> list){
//    assert(n*m == list.size());
//    for(int i = 0; i < n; ++i){
//        for(int j = 0; j < m; ++j){
//            (*this)[i][j] = *(list.begin()+i*m + j);
//        }
//    }
//    return *this;
//};

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
            (*this)[i][j] = x*(i == j);
    return *this;
}

template <class T>
matrix<T>::matrix(const matrix<T> &x){
    this->n = 0;
    this->m = 0;
    data = 0;
    *this = x;
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
                summ = summ + (*this)[i][k]*x[k][j];
            result[i][j] = summ;
        }
    }
    return result;
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
matrix<T> matrix<T>::operator* (const T &x) const{
    matrix result(*this);
    result *= x;
    return result;
}

template<class T>
T power(T x, unsigned long p){
    T result(x);
    result = 1;
    if(p == 0) return result;
    while (p){
        if(p & 1)
            result *= x;
        x *= x;
        p >>= 1;
    }
    return result;
}

template<>
matrix<BigInt> power(matrix<BigInt> x, unsigned long p){
    matrix<BigInt> result(10, 10);
    result = BigInt(1);
    if(p == 0) return result;
    while (p){
        if(p & 1)
            result *= x;
        x *= x;
        p >>= 1;
    }
    return result;
}


using namespace std;
int main(){
    int n;
    cin >> n;
    matrix<BigInt> start(10, 1);
    BigInt start_[10] = {0, 1, 1, 1, 1, 1, 1, 1, 0, 1};
    for(int i = 0; i < 10; ++i)
        start[i][0] = start_[i];
            //              0  1  2  3  4  5  6  7  8  9
   BigInt step_[10][10] =  {0, 0, 0, 0, 1, 0, 1, 0, 0, 0, // 0
                            0, 0, 0, 0, 0, 0, 1, 0, 1, 0, // 1
                            0, 0, 0, 0, 0, 0, 0, 1, 0, 1, // 2
                            0, 0, 0, 0, 1, 0, 0, 0, 1, 0, // 3
                            1, 0, 0, 1, 0, 0, 0, 0, 0, 1, // 4
                            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 5
                            1, 1, 0, 0, 0, 0, 0, 1, 0, 0, // 6
                            0, 0, 1, 0, 0, 0, 1, 0, 0, 0, // 7
                            0, 1, 0, 1, 0, 0, 0, 0, 0, 0, // 8
                            0, 0, 1, 0, 1, 0, 0, 0, 0, 0};// 9
    
    matrix<BigInt> step(10, 10);
    for(int i = 0; i < 10; ++i){
        for(int j = 0; j < 10; ++j){
            step[i][j] = step_[i][j];
        }
    }
    
    matrix<BigInt> end(10, 1);
    end = power(step, n-1)*start;
    BigInt result = 0;
    for(int i = 0; i < 10; ++i){
        result = result + end[i][0];
    }
        
    cout << result << "\n";
    return 0;
}

















