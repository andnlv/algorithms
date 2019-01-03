//
//  HashTable3.hpp
//  associative_array
//
//  Created by Andrey Danilov on 26.05.16.
//  Copyright © 2016 Andrey Danilov. All rights reserved.
//

#ifndef HashTable3_hpp
#define HashTable3_hpp

#include <iostream>
#include <vector>
#include <cmath>
#include <cassert>

namespace HTWС { //Hash table with cuckoo
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
        struct Node{
            int hashNumber;
            bool visited;
            std::shared_ptr<std::pair<const Key, T>> data;
            Node()
            : data(nullptr), visited(0) {};
            Node(Key k, int hashNumber)
            : data(std::make_shared<std::pair<const Key, T>>(k, T())), hashNumber(hashNumber), visited(0){};
        };
        std::vector<Node> table;
        size_t _size;
        Hash hash1;
        Hash hash2;
        bool tryToInsert(size_t position);
        const static double max_load_factor;
        const static double resize_factor;
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
        while(it != table->end() && it->data == nullptr)
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
        } while(it->data == nullptr);
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
    : hash1(next_prime(1)), hash2(next_prime(1)){
        assert(resize_factor > 1);
        assert(max_load_factor < 1);
        table.resize(next_prime(1));
        _size = 0;
    }
    
    template <class Key, class T, class Hash>
    HashTable<Key, T, Hash>:: HashTable(const HashTable &other){
        hash1 = other.hash1;
        hash2 = other.hash2;
        table = other.table;
        _size = other.size;
    }
    
    template <class Key, class T, class Hash>
    HashTable<Key, T, Hash>:: HashTable(HashTable &&other){
        hash1 = other.hash1;
        hash2 = other.hash2;
        table = move(other.table);
        _size = other.size;
    }
    
    template <class Key, class T, class Hash>
    HashTable<Key, T, Hash>& HashTable<Key, T, Hash>:: operator=(const HashTable &other){
        hash1 = other.hash1;
        hash2 = other.hash2;
        table = other.table;
        _size = other.size;
        return *this;
    }
    
    template <class Key, class T, class Hash>
    HashTable<Key, T, Hash>& HashTable<Key, T, Hash>:: operator=(HashTable &&other){
        hash1 = other.hash1;
        hash2 = other.hash2;
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
            hash1 = Hash(next_prime(newSize));
            hash2 = Hash(next_prime(newSize));
            table.resize(next_prime(newSize));
            return;
        }
        HashTable<Key, T, Hash> newTable;
        newTable.resize(newSize);
        for(auto it = table.begin(); it != table.end(); ++it){
            if(it->data == nullptr)
                continue;
            while (true){
                if(newTable.tryToInsert(newTable.hash1(it->data->first))){
                    newTable.table[newTable.hash1(it->data->first)].data = it->data;
                    newTable.table[newTable.hash1(it->data->first)].visited = false;
                    newTable.table[newTable.hash1(it->data->first)].hashNumber = 1;
                    break;
                }
                if(newTable.tryToInsert(newTable.hash2(it->data->first))){
                    newTable.table[newTable.hash2(it->data->first)].data = it->data;
                    newTable.table[newTable.hash2(it->data->first)].visited = false;
                    newTable.table[newTable.hash2(it->data->first)].hashNumber = 2;
                    break;
                }
                newTable.resize(newTable.table.size()*resize_factor);
            }
        }
        newTable._size = _size;
        *this = move(newTable);
    }
    
    template <class Key, class T, class Hash>
    T& HashTable<Key, T, Hash>:: operator[](const Key& key){
        if(1.*_size/table.size() >= max_load_factor){
            resize(table.size()*resize_factor);
        }
        if(table[hash1(key)].data != nullptr && table[hash1(key)].data->first == key){
            return table[hash1(key)].data->second;
        }
        if(table[hash2(key)].data != nullptr && table[hash2(key)].data->first == key){
            return table[hash2(key)].data->second;
        }
        while (true){
            if(tryToInsert(hash1(key))){
                ++_size;
                table[hash1(key)] = Node(key, 1);
                return table[hash1(key)].data->second;
            }
            else if(tryToInsert(hash2(key))){
                ++_size;
                table[hash2(key)] = Node(key, 2);
                return table[hash2(key)].data->second;;
            }
            resize(table.size()*resize_factor);
        }

    }
    
    template <class Key, class T, class Hash>
    const T& HashTable<Key, T, Hash>:: operator[](const Key& key) const{
        if(table[hash1(key)].data != nullptr && table[hash1(key)].data->first == key){
            return table[hash1(key)].data->second;
        }
        if(table[hash2(key)].data != nullptr && table[hash2(key)].data->first == key){
            return table[hash2(key)].data->second;
        }
        assert(false);
    }
    
    template <class Key, class T, class Hash>
    typename HashTable<Key, T, Hash>::iterator HashTable<Key, T, Hash>:: find (const Key& key){
        iterator resultIterator;
        resultIterator.table = &table;
        if(table[hash1(key)].data != nullptr && table[hash1(key)].data->first == key){
            resultIterator.it = table.begin() + hash1(key);
            return resultIterator;
        }
        if(table[hash2(key)].data != nullptr && table[hash2(key)].data->first == key){
            resultIterator.it = table.begin() + hash2(key);
            return resultIterator;
        }
        return end();
    }
    
    template <class Key, class T, class Hash>
    const typename HashTable<Key, T, Hash>::iterator HashTable<Key, T, Hash>:: find (const Key& key) const{
        iterator resultIterator;
        resultIterator.table = &table;
        if(table[hash1(key)].data != nullptr && table[hash1(key)].data->first == key){
            resultIterator.it = table.begin() + hash1(key);
            return resultIterator;
        }
        if(table[hash2(key())]->data != nullptr && table[hash2(key)].data->first == key){
            resultIterator.it = table.begin() + hash2(key);
            return resultIterator;
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
        if(table[hash1(key)].data != nullptr && table[hash1(key)].data->first == key){
            --_size;
            resultIterator.it = table.begin() + hash1(key) + 1;
            table[hash1(key)].data = nullptr;
            return resultIterator;
        }
        if(table[hash2(key)].data != nullptr && table[hash2(key)].data->first == key){
            --_size;
            resultIterator.it = table.begin() + hash2(key) + 1;
            table[hash1(key)].data = nullptr;
            return resultIterator;
        }
        return end();
    }
    
    template <class Key, class T, class Hash>
    typename HashTable<Key, T, Hash>::iterator HashTable<Key, T, Hash>::begin(){
        iterator resultIterator;
        resultIterator.table = &table;
        resultIterator.it = table.begin();
        while(resultIterator.it->data == nullptr && resultIterator.it != table.end())
            ++resultIterator.it;
        return resultIterator;
    }
    
    template <class Key, class T, class Hash>
    typename HashTable<Key, T, Hash>::iterator HashTable<Key, T, Hash>::end(){
        iterator resultIterator;
        resultIterator.table = &table;
        resultIterator.it = table.end();
        return resultIterator;
    }
    
    template <class Key, class T, class Hash>
    const typename HashTable<Key, T, Hash>::iterator HashTable<Key, T, Hash>::begin() const{
        iterator resultIterator;
        resultIterator.table = &table;
        resultIterator.it = table.begin();
        while(resultIterator.it->data == nullptr && resultIterator.it != table.end())
            ++resultIterator.it;
        return resultIterator;
    }
    
    template <class Key, class T, class Hash>
    const typename HashTable<Key, T, Hash>::iterator HashTable<Key, T, Hash>::end() const{
        iterator resultIterator;
        resultIterator.table = &table;
        resultIterator.it = table.end();
        return resultIterator;
    }
    
    template <class Key, class T, class Hash>
    bool HashTable<Key, T, Hash>::tryToInsert(size_t position){
        if(table[position].data == nullptr)
            return true;
        if(table[position].visited == true)
            return false;
        table[position].visited = true;
        bool result;
        if(table[position].hashNumber == 1){
            result = tryToInsert(hash2(table[position].data->first));
            table[position].visited = false;
            if(result == false)
                return false;
            table[hash2(table[position].data->first)].data = table[position].data;
            table[hash2(table[position].data->first)].hashNumber = 2;
            return true;
        }
        else{
            result = tryToInsert(hash1(table[position].data->first));
            table[position].visited = false;
            if(result == false)
                return false;
            table[hash1(table[position].data->first)].data = table[position].data;
            table[hash1(table[position].data->first)].hashNumber = 1;
            return true;
        }
    }
    
    template <class Key, class T, class Hash>
    const double HashTable<Key, T, Hash>::max_load_factor = 0.1;
    
    template <class Key, class T, class Hash>
    const double HashTable<Key, T, Hash>::resize_factor = 6;
}

#endif /* HashTable3_hpp */
