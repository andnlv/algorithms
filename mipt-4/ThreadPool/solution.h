//
//  solution.hpp
//  Threads
//
//  Created by Andrey Danilov on 20.03.17.
//  Copyright © 2017 Andrey Danilov. All rights reserved.
//

#ifndef solution_hpp
#define solution_hpp


#include "BlockingQueue/solution.h"
#include <condition_variable>
#include <deque>
#include <future>
#include <iostream>
#include <thread>
#include <vector>

template <class T>
class ThreadPool {
public:
    ThreadPool();
    explicit ThreadPool(const size_t num_threads, size_t max_tasks = std::numeric_limits<size_t>::max());
    std::future<T> Submit(std::function<T()> task);
    void Shutdown();
    ~ThreadPool();
private:
    BlockingQueue<std::packaged_task<T()>> queue_;
    std::vector<std::thread> threads_;
    void worker_();
};

template <class T>
ThreadPool<T>::ThreadPool()
    : ThreadPool(std::thread::hardware_concurrency()) {};

template <class T>
ThreadPool<T>::ThreadPool(const size_t num_threads, size_t max_tasks)
    : queue_(max_tasks),
      threads_(num_threads) {
    for (auto& thread : threads_) {
        t = std::move(std::thread(&ThreadPool<T>::worker_, this));
    }
};

template <class T>
std::future<T> ThreadPool<T>::Submit(std::function<T()> function) {
    std::packaged_task<T()> task(function);
    std::future<T> future = task.get_future();
    queue_.Put(std::move(task));
    return future;
}

template <class T>
void ThreadPool<T>::Shutdown() {
    queue_.Shutdown();
    for (auto &thread : threads_) {
        if(t.joinable()) {
            t.join();
        }
    }
}

template <class T>
ThreadPool<T>::~ThreadPool() {
    Shutdown();
}

template <class T>
void ThreadPool<T>::worker_() {
    std::packaged_task<T()> task;
    while (queue_.Get(task)) {
        task();
    }
}

int main(){
    return 0;
}

#endif /* solution_hpp */
