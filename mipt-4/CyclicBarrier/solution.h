//
//  solution.h
//  Threads
//
//  Created by Andrey Danilov on 11.03.17.
//  Copyright © 2017 Andrey Danilov. All rights reserved.
//


#include <condition_variable>
#include <iostream>
#include <thread>


template <class ConditionVariable = std::condition_variable>
class CyclicBarrier {
public:
    explicit CyclicBarrier(size_t num_threads);
    void Pass();
private:
    const size_t num_threads_;
    size_t gone_threads_;
    size_t waiting_threads_;
    ConditionVariable all_came_;
    ConditionVariable barrier_free_;
    std::mutex mt_;
};

template <class ConditionVariable>
CyclicBarrier<ConditionVariable>::CyclicBarrier(size_t num_threads)
  :num_threads_(num_threads),
  gone_threads_(num_threads),
  waiting_threads_(0){}

template <class ConditionVariable>
void CyclicBarrier<ConditionVariable>::Pass() {
    std::unique_lock<std::mutex> lock(mt_);
    // ждём пока все потоки выйдут из предыдущего барьера
    barrier_free_.wait(lock, [this]{return gone_threads_ == num_threads_;});
    barrier_free_.notify_all();
    // первый поток обнуляет переменную ждущих потоков
    waiting_threads_ %= num_threads_;
    ++waiting_threads_;
    // ждём пока все потоки зайдут в барьер
    all_came_.wait(lock, [this]{return waiting_threads_ == num_threads_;});
    all_came_.notify_all();
    // первый поток обнуляет переменную вышедших потоков
    gone_threads_ %= num_threads_;
    ++gone_threads_;
}
/* solution_h */
