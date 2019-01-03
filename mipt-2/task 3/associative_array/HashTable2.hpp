//
//  HashTable2.h
//  associative_array
//
//  Created by Andrey Danilov on 24.05.16.
//  Copyright © 2016 Andrey Danilov. All rights reserved.
//

#ifndef HashTable2_hpp
#define HashTable2_hpp
#include <iostream>
#include <vector>
#include <cmath>
#include <cassert>

namespace HTWOA { //Hash table with open adressing
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
        enum State{busy, erased, free};
        struct Node{
            std::shared_ptr<std::pair<const Key, T>> data;
            State state;
            Node()
            : data(nullptr), state(free){};
            Node(Key k, T t)
            : data(std::make_shared<std::pair<const Key, T>>(k, t)), state(busy){};
        };
        std::vector<Node> table;
        size_t _size;
        Hash hash;
        const static double max_load_factor;
        const static double resize_factor;
        size_t delta;
        size_t count_delta(){
            return next_prime(sqrt(table.size())*10);
        }
    public:
        class iterator{
        private:
            typename std::vector<Node>::iterator it;
            const std::vector<Node> * table;
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
            std::shared_ptr<std::pair<const Key, T>> operator -> ();
            const std::shared_ptr<std::pair<const Key, T>> operator -> () const;
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
        assert(it != table->end());
        ++it;
        while(it != table->end() && it->state != busy)
            ++it;
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
        do{
        assert(it != table->begin());
        --it;
        } while(it->state != busy);
        return *this;
    }
    
    template <class Key, class T, class Hash>
    typename HashTable<Key, T, Hash>::iterator HashTable<Key, T, Hash>::iterator:: operator--(int){
        auto result = *this;
        --(*this);
        return result;
    }
    
    template <class Key, class T, class Hash>
    std::pair<const Key, T>& HashTable<Key, T, Hash>::iterator:: operator* (){
        return *it->data;
    }
    
    template <class Key, class T, class Hash>
    const std::pair<const Key, T>& HashTable<Key, T, Hash>::iterator:: operator* () const{
        return *it->data;
    }
    
    template <class Key, class T, class Hash>
    bool HashTable<Key, T, Hash>::iterator:: operator < (const iterator& other) const{
        return it < other.it;
    }
    
    template <class Key, class T, class Hash>
    bool HashTable<Key, T, Hash>::iterator:: operator == (const iterator& other) const{
        return it == other.it;
    }
    
    template <class Key, class T, class Hash>
    bool HashTable<Key, T, Hash>::iterator:: operator != (const iterator& other) const{
        return it != other.it;
    }
    
    template <class Key, class T, class Hash>
    std::shared_ptr<std::pair<const Key, T>> HashTable<Key, T, Hash>::iterator:: operator-> (){
        return it->data;
    }
    
    template <class Key, class T, class Hash>
    const std::shared_ptr<std::pair<const Key, T>> HashTable<Key, T, Hash>::iterator:: operator-> () const{
        return &(it->data);
    }
    
    template <class Key, class T, class Hash>
    HashTable<Key, T, Hash>:: HashTable()
    : hash(next_prime(1)){
        assert(resize_factor > 1);
        assert(max_load_factor < 1);
        table.resize(next_prime(1));
        _size = 0;
        delta = count_delta();
    }
    
    template <class Key, class T, class Hash>
    HashTable<Key, T, Hash>:: HashTable(const HashTable &other){
        hash = other.hash;
        table = other.table;
        _size = other.size;
        delta = other.delta;
    }
    
    template <class Key, class T, class Hash>
    HashTable<Key, T, Hash>:: HashTable(HashTable &&other){
        hash = other.hash;
        table = move(other.table);
        _size = other.size;
        delta = other.delta;
    }
    
    template <class Key, class T, class Hash>
    HashTable<Key, T, Hash>& HashTable<Key, T, Hash>:: operator=(const HashTable &other){
        hash = other.hash;
        table = other.table;
        _size = other.size;
        delta = other.delta;
        return *this;
    }
    
    template <class Key, class T, class Hash>
    HashTable<Key, T, Hash>& HashTable<Key, T, Hash>:: operator=(HashTable &&other){
        hash = other.hash;
        table = move(other.table);
        _size = other._size;
        delta = other.delta;
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
            delta = count_delta();
            return;
        }
        HashTable<Key, T, Hash> newTable;
        newTable.resize(newSize);
        for(auto it = table.begin(); it != table.end(); ++it){
            if(it->state != busy)
                continue;
            for(size_t i = 0; i < newTable.table.size(); i += newTable.delta){
                if(newTable.table[(newTable.hash(it->data->first)+i)%newTable.table.size()].state != busy){
                    newTable.table[(newTable.hash(it->data->first)+i)%newTable.table.size()].state = busy;
                    newTable.table[(newTable.hash(it->data->first)+i)%newTable.table.size()].data = it->data;
                    break;
                }
            }
        }
        *this = move(newTable);
    }
    
    template <class Key, class T, class Hash>
    T& HashTable<Key, T, Hash>:: operator[](const Key& key){
        if(1.*_size/table.size() >= max_load_factor)
            resize(table.size()*resize_factor);
        int delta = sqrt(table.size());
        for(size_t i = 0; i < table.size(); i += delta){ //попытка найти ключ k
            if(table[(hash(key)+i)%table.size()].state == free)
                break;
            if(table[(hash(key)+i)%table.size()].state == busy and
               table[(hash(key)+i)%table.size()].data->first == key){
                //t2 = clock();
                //cout << t2 - t1 << "\n";
                return table[(hash(key)+i)%table.size()].data->second;
            }
        }
        for(size_t i = 0; i < table.size(); i += delta){ //поиск ближайшего свободного места
            if(table[(hash(key)+i)%table.size()].state != busy){
                ++_size;
                table[(hash(key)+i)%table.size()] = Node(key, T());
                return table[(hash(key)+i)%table.size()].data->second;
            }
        }
        assert(false);
    }
    
    template <class Key, class T, class Hash>
    const T& HashTable<Key, T, Hash>:: operator[](const Key& key) const{
        for(size_t i = 0; i < table.size(); i += delta){
            assert(table[(hash(key)+i)%table.size()] != nullptr and
                   table[(hash(key)+i)%table.size()].state != free);
            if(table[(hash(key)+i)%table.size()]->data->first == key){
                return table[(hash(key)+i)%table.size()]->data->second;
            }
        }
        assert(false);
    }
    
    template <class Key, class T, class Hash>
    typename HashTable<Key, T, Hash>::iterator HashTable<Key, T, Hash>:: find (const Key& key){
            iterator resultIterator;
            resultIterator.table = &table;
            for(size_t i = 0; i < table.size(); i += delta){
                if(table[(hash(key)+i)%table.size()].state ==  busy &&
                   table[(hash(key)+i)%table.size()].data->first == key){
                    resultIterator.it = table.begin() + (hash(key)+i)%table.size();
                    return resultIterator;
                }
            }
            return end();
    }
    
    template <class Key, class T, class Hash>
    const typename HashTable<Key, T, Hash>::iterator HashTable<Key, T, Hash>:: find (const Key& key) const{
        iterator resultIterator;
        resultIterator.table = &table;
        for(size_t i = 0; i < table.size(); i += delta){
            if(table[(hash(key)+i)%table.size()].state ==  busy &&
               table[(hash(key)+i)%table.size()].data->first == key){
                resultIterator.it = table.begin() + (hash(key)+i)%table.size();
                return resultIterator;
            }
        }
        return end();
    }
    
    template <class Key, class T, class Hash>
    typename HashTable<Key, T, Hash>::iterator HashTable<Key, T, Hash>:: erase (const Key& key){
        if(1.*_size/table.size() < 1.* max_load_factor/(resize_factor*resize_factor)){
            resize(table.size()/resize_factor);
        }
        iterator resultIterator;
        resultIterator.table = &table;
        for(size_t i = 0; i < table.size(); i += delta){
            if(table[(hash(key)+i)%table.size()].state == free)
                break;
            if(table[(hash(key)+i)%table.size()].state == busy and
               table[(hash(key)+i)%table.size()].data->first == key){
                --_size;
                table[(hash(key)+i)%table.size()].state = erased;
                table[(hash(key)+i)%table.size()].data = nullptr;
                iterator result;
                result.table = &table;
                result.it = table.begin() + hash(key) + i + 1;
                return result;
            }
        }
        return end();
    }
    
    template <class Key, class T, class Hash>
    typename HashTable<Key, T, Hash>::iterator HashTable<Key, T, Hash>::begin(){
        iterator resultIterator;
        resultIterator.table = &table;
        resultIterator.it = table.begin();
        while(resultIterator.it->state != busy && resultIterator.it != table.end())
            ++resultIterator.it;
        return resultIterator;
    }
    
    template <class Key, class T, class Hash>
    typename HashTable<Key, T, Hash>::iterator HashTable<Key, T, Hash>::end(){
        iterator resultIterator;
        resultIterator.it = table.end();
        resultIterator.table = &table;
        return resultIterator;
    }
    
    template <class Key, class T, class Hash>
    const typename HashTable<Key, T, Hash>::iterator HashTable<Key, T, Hash>::begin() const{
        iterator resultIterator;
        resultIterator.table = &table;
        resultIterator.it = table.begin();
        while(resultIterator.it->state != busy && resultIterator.it != table.end())
            ++resultIterator.it;
        return resultIterator;
    }
    
    template <class Key, class T, class Hash>
    const typename HashTable<Key, T, Hash>::iterator HashTable<Key, T, Hash>::end() const{
        iterator resultIterator;
        resultIterator.it = table.end();
        resultIterator.table = &table;
        return resultIterator;
    }
    
    template <class Key, class T, class Hash>
    const double HashTable<Key, T, Hash>::max_load_factor = 0.1;
    
    template <class Key, class T, class Hash>
    const double HashTable<Key, T, Hash>::resize_factor = 6;
}



#endif /* HashTable2_h */
