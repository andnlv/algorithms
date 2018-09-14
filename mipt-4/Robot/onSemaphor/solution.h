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
#include <iostream>
#include <thread>

class Semaphore {
public:
    explicit Semaphore(int initial_value);
    void Wait();
    void Post();
private:
    std::mutex mt_;
    std::condition_variable condvar_;
    int counter_;
};

Semaphore::Semaphore(int initial_value)
        : counter_(initial_value) {};

void Semaphore::Wait() {
    std::unique_lock<std::mutex> lock(mt_);
    condvar_.wait(lock, [this]{return counter_ > 0;});
    --counter_;
}

void Semaphore::Post() {
    std::unique_lock<std::mutex> lock(mt_);
    ++counter_;
    condvar_.notify_one();
}

class Robot {
public:
    Robot();
    void StepLeft();
    void StepRight();
private:
    Semaphore left_;
    Semaphore right_;
};

Robot::Robot()
        : left_(1),
          right_(1) {
    right_.Wait();
}

void Robot::StepLeft() {
    left_.Wait();
    std::cout << "left" << std::endl;
    right_.Post();
}

void Robot::StepRight() {
    right_.Wait();
    std::cout << "right" << std::endl;
    left_.Post();
}

#endif /* solution_hpp */
