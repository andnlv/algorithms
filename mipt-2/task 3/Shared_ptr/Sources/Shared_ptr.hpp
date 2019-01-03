//
//  Shared_ptr.hpp
//  Shared_ptr
//
//  Created by Andrey Danilov on 28.04.16.
//  Copyright © 2016 Andrey Danilov. All rights reserved.
//

#ifndef Shared_ptr_hpp
#define Shared_ptr_hpp
#include <algorithm>

template<class T>
class Shared_ptr{
private:
    int * counter;
    T* ptr;
public:
    Shared_ptr();
    Shared_ptr(T* placementPtr);
    ~Shared_ptr();
    Shared_ptr(const Shared_ptr &);
    Shared_ptr(Shared_ptr &&);
    Shared_ptr<T>& operator= (const Shared_ptr &);
    Shared_ptr<T>& operator= (Shared_ptr &&);
    T operator * ();
    T* operator -> ();
    const T operator * () const;
    const T* operator -> () const;
    T*& get();
    const T* get() const;
};

template <class T, class ... Args>
T* create_ptr(const Args& ... args);

#endif /* Shared_ptr_hpp */
