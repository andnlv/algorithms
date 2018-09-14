//
//  main.cpp
//  TreeMutex
//
//  Created by Andrey Danilov on 17.05.17.
//  Copyright © 2017 Andrey Danilov. All rights reserved.
//

#include <atomic>
#include <iostream>
#include <thread>
#include <vector>


class TreeMutex {
public:
    TreeMutex(std::size_t num_threads) {
        first_thread_index_ = 1;
        while(2*first_thread_index_ < num_threads) {
            first_thread_index_ *= 2;
        }
        tree_ = std::vector<Mutex>(first_thread_index_ * 2);
    }
    
    void lock(std::size_t current_thread) {
        size_t current_lock = first_thread_index_ + current_thread/2;
        bool thread_id = current_thread % 2;
        while(current_lock > 0) {
            tree_[current_lock].want[thread_id] = true;
            tree_[current_lock].victim = thread_id;
            while ((tree_[current_lock].want[!thread_id] &&
                    tree_[current_lock].victim == thread_id)) {
                std::this_thread::yield();
            }
            thread_id = current_lock % 2;
            current_lock = current_lock / 2;
        }
    }
    
    void unlock(std::size_t current_thread) {
        size_t current_lock = 1;
        size_t depth_bit = first_thread_index_;
        while (depth_bit > 0) {
            bool thread_id = current_thread & depth_bit;
            tree_[current_lock].want[thread_id] = false;
            current_lock = current_lock * 2 + thread_id;
            depth_bit >>= 1;
        }
    }
private:
    struct Mutex{
        std::atomic<bool> want[2];
        std::atomic<bool> victim;
        Mutex() {
            want[0] = want[1] = victim = false;
        }
    };
    size_t first_thread_index_;
    std::vector<Mutex> tree_;
};



