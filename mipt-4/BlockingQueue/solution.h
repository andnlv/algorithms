//
//  solution.hpp
//  Threads
//
//  Created by Andrey Danilov on 20.03.17.
//  Copyright © 2017 Andrey Danilov. All rights reserved.
//

#ifndef solution_hpp
#define solution_hpp

#include <condition_variable>
#include <deque>
#include <iostream>
#include <thread>

template <class T, class Container = std::deque<T>>
class BlockingQueue {
public:
    explicit BlockingQueue(size_t capacity);
    void Put(T&& element);
    bool Get(T& result);
    void Shutdown();
    class BlockingQueueException : public std::exception {};
private:
    Container container_;
    std::condition_variable if_empty_;
    std::condition_variable  if_full_;
    const size_t capacity_;
    std::mutex mt_;
    std::atomic<bool> turned_off_;
};

template <class T, class Container>
BlockingQueue<T, Container>::BlockingQueue(size_t capacity)
        : capacity_(capacity),
          turned_off_(false) {};

template <class T, class Container>
void BlockingQueue<T, Container>::Put(T&& element) {
    std::unique_lock<std::mutex> lock(mt_);
    if_full_.wait(lock, [this]{return container_.size() < capacity_ || turned_off_;});
    if (turned_off_) {
        throw exception();
    }
    container_.push_back(std::move(element));
    if_empty_.notify_one();
}

template <class T, class Container>
bool BlockingQueue<T, Container>::Get(T& result) {
    std::unique_lock<std::mutex> lock(mt_);
    if_empty_.wait(lock, [this]{return container_.size() > 0 || turned_off_;});
    if (container_.empty()) {
        return false;
    }
    result = std::move(container_.front());
    container_.pop_front();
    if_full_.notify_one();
    return true;
}

template <class T, class Container>
void BlockingQueue<T, Container>::Shutdown() {
    turned_off_ = true;
    if_full_.notify_all();
    if_empty_.notify_all();
}

#endif /* solution_hpp */
