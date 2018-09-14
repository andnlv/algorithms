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

class Robot {
public:
    void StepLeft();
    void StepRight();
private:
    std::mutex mt_;
    bool leg_ = true; // true, если ход левой ноги
    std::condition_variable condvar_;
};

void Robot::StepLeft() {
    std::unique_lock<std::mutex> lock(mt);
    condvar_.wait(lock, [this]{return leg;});
    std::cout << "left" << std::endl;
    leg_ = false;
    condvar_.notify_one();
}

void Robot::StepRight() {
    std::unique_lock<std::mutex> lock(mt_);
    condvar_.wait(lock, [this]{return !leg;});
    std::cout << "right" << std::endl;
    leg_ = true;
    condvar_.notify_one();
}

#endif /* solution_hpp */
