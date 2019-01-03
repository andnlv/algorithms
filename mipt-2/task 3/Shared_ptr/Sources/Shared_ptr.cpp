//
//  Shared_ptr.cpp
//  Shared_ptr
//
//  Created by Andrey Danilov on 28.04.16.
//  Copyright © 2016 Andrey Danilov. All rights reserved.
//

#include "Shared_ptr.hpp"

template <class T>
Shared_ptr<T>:: Shared_ptr(){
    ptr = new T;
    counter = new int(1);
}

template <class T>
Shared_ptr<T>:: Shared_ptr(T *placementPtr){
    ptr = placementPtr;
    counter = new int(1);
}

template <class T>
Shared_ptr<T>:: ~Shared_ptr(){
    --*counter;
    if(*counter == 0){
        delete counter;
        delete ptr;
    }
}

template <class T>
Shared_ptr<T>:: Shared_ptr(const Shared_ptr &x){
    counter = x.counter;
    ++*counter;
    ptr = x.ptr;
}

template <class T>
Shared_ptr<T>:: Shared_ptr(Shared_ptr && x){
    ptr = x.ptr;
    counter = x.counter;
    ++*counter;
}

template <class T>
Shared_ptr<T>& Shared_ptr<T>:: operator= (const Shared_ptr &x){
    --*counter;
    if(*counter == 0){
        delete ptr;
        delete counter;
    }
    counter = x.counter;
    ++*counter;
    ptr = x.ptr;
    return *this;
}

template <class T>
Shared_ptr<T>& Shared_ptr<T>:: operator= (Shared_ptr &&x){
    std::swap(ptr, x.ptr);
    std::swap(counter, x.counter);
    return *this;
}

template <class T>
T Shared_ptr<T>:: operator*(){
    return *ptr;
}

template <class T>
const T Shared_ptr<T>:: operator*() const{
    return *ptr;
}

template <class T>
T* Shared_ptr<T>:: operator->(){
    return ptr;
}

template <class T>
const T* Shared_ptr<T>:: operator->() const{
    return ptr;
}

template <class T>
T*& Shared_ptr<T>:: get(){
    return ptr;
}

template <class T>
const T* Shared_ptr<T>:: get() const{
    return ptr;
}

template <class T, class ... Args>
T* create_ptr(const Args& ... args){
    return new T(args ...);
}




















