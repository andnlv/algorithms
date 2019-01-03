//
//  BST.hpp
//  BST
//
//  Created by Andrey Danilov on 09.05.16.
//  Copyright © 2016 Andrey Danilov. All rights reserved.
//

#ifndef BST_hpp
#define BST_hpp
#include <iostream>
#include <memory>
#include <cassert>
using namespace std;
template<class T, class Cmp = less<T>>
class BST{
private:
    Cmp cmp;
    class Node{
    public:
        T data;
        shared_ptr<Node> left = nullptr;
        shared_ptr<Node> right = nullptr;
        shared_ptr<Node> parent;
        Node(const T &d, shared_ptr<Node> p){
            data = d;
            parent = p;
        }
    };
    shared_ptr<Node> head = nullptr;
    shared_ptr<Node> _find(const T& x){ // find place for insert
        shared_ptr<Node> ptr = head;
        if(ptr == nullptr)
            return nullptr;
        while(true){
            if(cmp(ptr->data, x)){
                if(ptr->right == nullptr)
                    return ptr;
                else
                    ptr = ptr->right;
            }
            else{
                if(ptr->left == nullptr)
                    return ptr;
                else
                    ptr = ptr->left;
            }
        }
    }
    
    void _print(const shared_ptr<Node> x) const{
        if(x == nullptr)
            return;
        _print(x->left);
        cout << x->data << " ";
        _print(x->right);
    }
    
    const shared_ptr<Node> find_min(const T& x, shared_ptr<Node> ptr) const{
        if(ptr == nullptr)
            return nullptr;
        if(cmp(ptr->data, x)){
            return find_min(x, ptr->right);
        }
        else{
            shared_ptr<Node> rightPtr = find_min(x, ptr->left);
            if(rightPtr == nullptr)
                return ptr;
            else
                return rightPtr;
        }
    }

public:
    const shared_ptr<Node> find(const T& x) const{
        return find_min(x, head);
    }
    
    const shared_ptr<Node> insert(const T &x){
        if(head == nullptr){
            head = make_shared<Node>(x, nullptr);
            return head;
        }
        shared_ptr<Node> ptr = _find(x);
        if(cmp(x, ptr->data) || ptr->right != nullptr){
            ptr->left = make_shared<Node>(x, ptr);
            return ptr->left;
        }
        else{
            ptr->right = make_shared<Node>(x, ptr);
            return ptr->right;
        }
        return nullptr;
    }
    
    bool erase(const T &x){
        shared_ptr<Node> ptr = find(x);
        if(cmp(ptr->data, x) || cmp(x, ptr->data))
            return false;
        shared_ptr<Node> &parentsPtr = ptr->parent != nullptr ?
        (ptr->parent->right == ptr ? ptr->parent->right : ptr->parent->left) : head;
        if(ptr->left == nullptr && ptr->right == nullptr){ // случай 0
            parentsPtr = nullptr;
            ptr->parent = nullptr;
        }
        else if(ptr->left != nullptr && ptr->right == nullptr){ // случай 1
            parentsPtr = ptr->left;
            ptr->left->parent = ptr->parent;
            ptr->parent = nullptr;
        }
        else if(ptr->left == nullptr && ptr->right != nullptr){ // случай 1
            parentsPtr = ptr->right;
            ptr->right->parent = ptr->parent;
            ptr->parent = nullptr;
        }
        else if(ptr->right->left == nullptr){ // случай 2
            ptr->right->parent = ptr->parent;
            ptr->right->left = ptr->left;
            parentsPtr = ptr->right;
            ptr->parent = nullptr;
        }
        else if(ptr->left->right == nullptr){ // случай 2
            ptr->left->parent = ptr->parent;
            ptr->left->right = ptr->right;
            parentsPtr = ptr->left;
            ptr->parent = nullptr;
        }
        else{                                   //случай 3
            shared_ptr<Node> ptr2 = ptr->right;
            while(ptr2->left != nullptr)
                ptr2 = ptr2->left;
            ptr2->parent->left = ptr2->right;
            if(ptr2->right != nullptr)
                ptr2->right->parent = ptr2->parent;
            ptr2->parent = ptr->parent;
            ptr2->right = ptr->right;
            ptr2->left = ptr-> left;
            parentsPtr = ptr2;
            ptr2->right->parent = ptr2;
            ptr2->left->parent = ptr2;
            ptr->parent = nullptr;
        }
        return true;
    }
    
    void print() const{
        _print(head);
        cout << "\n";
    }
};

#endif /* BST_hpp */
