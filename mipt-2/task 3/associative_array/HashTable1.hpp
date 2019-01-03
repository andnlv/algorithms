//
//  HashTable.hpp
//  associative_array
//
//  Created by Andrey Danilov on 21.05.16.
//  Copyright © 2016 Andrey Danilov. All rights reserved.
//

#ifndef HashTable_hpp
#define HashTable_hpp
#include <iostream>
#include <vector>
#include <list>
#include <cmath>
#include <cassert>



namespace HTWL { // Hash table with lists
    template <class T>
    class hasher {
    private:
        size_t a;
        size_t b;
        size_t limit;
    public:
        hasher(size_t l){
            assert(l != 0);
            srand(int(time(NULL)));
            a = l > 1 ? rand()%(l-1) + 1 : 1;
            b = rand()%l;
            limit = l;
        }
        size_t operator()(T t) const{
            return (a*t + b) % limit;
        }
    };
    
    bool _is_prime(size_t n){
        int limit = ceil(sqrt(n));
        for(int i = 2; i <= limit; ++i)
            if(n%i == 0)
                return false;
        return true;
    }
    
    size_t next_prime(size_t begin){
        size_t i;
        for(i = begin+1; !_is_prime(i); ++i);
        return i;
    }
    
    template<class Key, class T, class Hash = hasher<Key>>
    class HashTable{
    private:
        std::vector<std::list<std::pair<const Key, T>>> table;
        size_t _size;
        Hash hash;
        static double max_load_factor;
        static double resize_factor;
    public:
        class iterator{
        private:
            typename std::vector<std::list<std::pair<const Key, T>>>::iterator it1;
            typename std::list<std::pair<const Key, T>>::iterator it2;
            const std::vector<std::list<std::pair<const Key, T>>> * table;
        public:
            iterator operator++ ();
            iterator operator++ (int);
            iterator operator-- ();
            iterator operator-- (int);
            std::pair<const Key, T>& operator* ();
            const std::pair<const Key, T>& operator* () const;
            bool operator < (const iterator &) const;
            bool operator == (const iterator &) const;
            bool operator != (const iterator &) const;
            std::pair<const Key, T>* operator -> ();
            const std::pair<const Key, T>* operator -> () const;
            friend HashTable;
        };
        HashTable();
        HashTable(const HashTable &);
        HashTable(HashTable &&);
        HashTable& operator= (const HashTable&);
        HashTable& operator= (HashTable&&);
        size_t size() const;
        void resize(size_t size);
        T& operator [] (const Key&);
        const T& operator [] (const Key&) const;
        iterator find(const Key&);
        const iterator find(const Key&) const;
        iterator erase(const Key&);
        iterator begin();
        iterator end();
        const iterator begin() const;
        const iterator end() const;
    };
    
    template <class Key, class T, class Hash>
    typename HashTable<Key, T, Hash>::iterator HashTable<Key, T, Hash>::iterator:: operator++(){
        assert(it1 != table->end());
        ++it2;
        while(it2 == it1->end()){
            ++it1;
            if(it1 != table->end())
                it2 = it1->begin();
            else
                break;
        }
        return *this;
    }
    
    template <class Key, class T, class Hash>
    typename HashTable<Key, T, Hash>::iterator HashTable<Key, T, Hash>::iterator:: operator++(int){
        auto result = *this;
        ++(*this);
        return result;
    }
    
    template <class Key, class T, class Hash>
    typename HashTable<Key, T, Hash>::iterator HashTable<Key, T, Hash>::iterator:: operator--(){
        while(it2 == it1->begin()){
            assert(it1 != table->begin());
            --it1;
            it2 = it1->end;
        }
        --it2;
        return *this;
    }
    
    template <class Key, class T, class Hash>
    std::pair<const Key, T>& HashTable<Key, T, Hash>::iterator:: operator* (){
        return *it2;
    }
    
    template <class Key, class T, class Hash>
    const std::pair<const Key, T>& HashTable<Key, T, Hash>::iterator:: operator* () const{
        return *it2;
    }
    
    template <class Key, class T, class Hash>
    typename HashTable<Key, T, Hash>::iterator HashTable<Key, T, Hash>::iterator:: operator--(int){
        auto result = *this;
        --(*this);
        return result;
    }
    
    template <class Key, class T, class Hash>
    bool HashTable<Key, T, Hash>::iterator:: operator < (const iterator& other) const{
        return it1 < other.it1 || (it1 == other.it1 and it2 < other.it2);
    }
    
    template <class Key, class T, class Hash>
    bool HashTable<Key, T, Hash>::iterator:: operator == (const iterator& other) const{
        return it1 == other.it1 && (it1 == table->end() || it2 == other.it2);
    }
    
    template <class Key, class T, class Hash>
    bool HashTable<Key, T, Hash>::iterator:: operator != (const iterator& other) const{
        return !(*this == other);
    }
    
    template <class Key, class T, class Hash>
    std::pair<const Key, T>* HashTable<Key, T, Hash>::iterator:: operator-> (){
        return it2.operator->();
    }
    
    template <class Key, class T, class Hash>
    const std::pair<const Key, T>* HashTable<Key, T, Hash>::iterator:: operator-> () const{
        return it2.operator->();
    }
    
    template <class Key, class T, class Hash>
    HashTable<Key, T, Hash>:: HashTable()
    : hash(next_prime(1)){
        assert(resize_factor > 1);
        table.resize(next_prime(1));
        _size = 0;
    }
    
    template <class Key, class T, class Hash>
    HashTable<Key, T, Hash>:: HashTable(const HashTable &other){
        hash = other.hash;
        table = other.table;
        _size = other.size;
    }
    
    template <class Key, class T, class Hash>
    HashTable<Key, T, Hash>:: HashTable(HashTable &&other){
        hash = other.hash;
        table = move(other.table);
        _size = other.size;
    }
    
    template <class Key, class T, class Hash>
    HashTable<Key, T, Hash>& HashTable<Key, T, Hash>:: operator=(const HashTable &other){
        hash = other.hash;
        table = other.table;
        _size = other.size;
        return *this;
    }
    
    template <class Key, class T, class Hash>
    HashTable<Key, T, Hash>& HashTable<Key, T, Hash>:: operator=(HashTable &&other){
        hash = other.hash;
        table = move(other.table);
        _size = other._size;
        return *this;
    }
    
    template <class Key, class T, class Hash>
    size_t HashTable<Key, T, Hash>:: size() const{
        return _size;
    }
    template <class Key, class T, class Hash>
    void HashTable<Key, T, Hash>:: resize(size_t newSize){
        if(_size == 0){
            hash = Hash(next_prime(newSize));
            table.resize(next_prime(newSize));
            return;
        }
        HashTable<Key, T, Hash> newTable;
        newTable.resize(newSize);
        for(auto it = begin(); it != end(); ++it){
            newTable.table[newTable.hash(it->first)].push_back(*it);
        }
        newTable._size = _size;
        *this = std::move(newTable);
    }
    
    template <class Key, class T, class Hash>
    T& HashTable<Key, T, Hash>:: operator[](const Key& k){
        for(auto it = table[hash(k)].begin(); it != table[hash(k)].end(); ++it){
            if(it->first == k)
                return it->second;
        }
        ++_size;
        if(_size/table.size() >= max_load_factor)
            resize(table.size()*resize_factor);
        table[hash(k)].push_back(std::pair<const Key, T>(k, T()));
        return table[hash(k)].back().second;
    }
    
    template <class Key, class T, class Hash>
    const T& HashTable<Key, T, Hash>:: operator[](const Key& k) const{
        for(auto it = table[hash(k)].begin(); it != table[hash(k)].end(); ++it){
            if(it->first == k)
                return it->second();
        }
    }
    
    template <class Key, class T, class Hash>
    typename HashTable<Key, T, Hash>::iterator HashTable<Key, T, Hash>:: find (const Key& k){
        iterator resultIterator;
        resultIterator.table = &table;
        for(auto it = table[hash(k)].begin(); it != table[hash(k)].end(); ++it){
            if(it->first == k){
                resultIterator.it1 = table.begin() + hash(k);
                resultIterator.it2 = it;
                return resultIterator;
            }
        }
        resultIterator.it1 = table.end();
        return resultIterator;
    }
    
    template <class Key, class T, class Hash>
    const typename HashTable<Key, T, Hash>::iterator HashTable<Key, T, Hash>:: find (const Key& k) const{
        iterator resultIterator;
        resultIterator.table = &table;
        for(auto it = table[hash(k)].begin(); it != table[hash(k)].end(); ++it){
            if(it->first() == k){
                resultIterator.it1 = table.begin + hash(k);
                resultIterator.it2 = it;
                return resultIterator;
            }
        }
        resultIterator.it1 = table.end();
        return resultIterator;
    }
    
    template <class Key, class T, class Hash>
    typename HashTable<Key, T, Hash>::iterator HashTable<Key, T, Hash>:: erase (const Key& k){
        iterator resultIterator;
        resultIterator.table = &table;
        for(auto it = table[hash(k)].begin(); it != table[hash(k)].end(); ++it){
            if(it->first == k){
                if(1.*_size/table.size() < 1.* max_load_factor/(resize_factor*resize_factor)){
                    resize(table.size()/resize_factor);
                    return erase(k);
                }
                resultIterator.it1 = table.begin() + hash(k);
                resultIterator.it2 = it;
                ++resultIterator;
                --_size;
                table[hash(k)].erase(it);
                return resultIterator;
            }
        }
        resultIterator.it1 = table.end();
        return resultIterator;
    }
    
    template <class Key, class T, class Hash>
    typename HashTable<Key, T, Hash>::iterator HashTable<Key, T, Hash>::begin(){
        iterator it;
        it.table = &table;
        it.it1 = table.begin();
        while (it.it1 != (it.table)->end() && it.it1->size() == 0) {
            ++it.it1;
        }
        if(it.it1 != (it.table)->end())
            it.it2 = it.it1->begin();
        return it;
    }
    
    template <class Key, class T, class Hash>
    typename HashTable<Key, T, Hash>::iterator HashTable<Key, T, Hash>::end(){
        iterator it;
        it.it1 = table.end();
        return it;
    }
    
    template <class Key, class T, class Hash>
    const typename HashTable<Key, T, Hash>::iterator HashTable<Key, T, Hash>::begin() const{
        iterator it;
        it.it1 = table.begin();
        if(it == table.end())
            return it;
        it.it2 = it.it1->begin();
        return it;
    }
    
    template <class Key, class T, class Hash>
    const typename HashTable<Key, T, Hash>::iterator HashTable<Key, T, Hash>::end() const{
        iterator it;
        it.it1 = table.end();
        return it;
    }
    
    template <class Key, class T, class Hash>
    double HashTable<Key, T, Hash>::max_load_factor = 1;
    
    template <class Key, class T, class Hash>
    double HashTable<Key, T, Hash>::resize_factor = 6;

}
#endif







