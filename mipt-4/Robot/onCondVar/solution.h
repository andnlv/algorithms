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
    explicit Robot(const std::size_t num_foots);
    void Step(const std::size_t foot);
private:
    const size_t num_foots_;
    size_t current_foot_;
    std::condition_variable condvar_;
    std::mutex mt_;
};

Robot::Robot(const std::size_t num_foots)
        : num_foots_(num_foots),
          current_foot_(0) {};
    

void Robot::Step(const std::size_t foot) {
    std::unique_lock<std::mutex> lock(mt_);
    condvar_.wait(lock, [this, foot]{return current_foot_ == foot;});
    std::cout << "foot " << foot << std::endl;
    current_foot_ = (current_foot_ + 1) % num_foots_;
    condvar_.notify_all();
}

#endif /* solution_hpp */
