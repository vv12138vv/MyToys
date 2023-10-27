#ifndef TIMER_H
#define TIMER_H

#include <bits/chrono.h>
#include <chrono>
#include <iostream>

class Timer {
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> start_;
    std::chrono::time_point<std::chrono::high_resolution_clock> end_;

public:
    explicit Timer() { start_ = std::chrono::high_resolution_clock::now(); }
    ~Timer() {
        end_ = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_ - start_);
        std::cout <<"function time is: "<<duration.count() << "\n";
    }
};

#endif   // TIMER_H