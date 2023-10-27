#include "thread_pool.hpp"
#include <cstddef>
#include <mutex>
#include <thread>
#include <utility>

using namespace vvmemory;


TaskQueue::TaskQueue() {}


void TaskQueue::addTask(Task&& task) {
    mtx_.lock();
    taskQueue_.push(std::move(task));
    mtx_.unlock();
}


Task TaskQueue::getTask() {
    mtx_.lock();
    Task task;
    if (!taskQueue_.empty()) {
        task = taskQueue_.front();
        taskQueue_.pop();
    }
    mtx_.unlock();
    return task;
}

ThreadPool::ThreadPool(size_t min, size_t max)
    : minThreadNum_(min)
    , maxThreadNum_(max) {
    busyNum_ = 0;
    aliveNum_ = min;
    std::thread managerTh;
    threads_[0] = std::move(managerTh);
    managerIndex_ = 0;
    for (size_t i = 1; i < min; i += 1) {
        std::thread th;
        threads_[i] = std::move(th);
    }
}

void ThreadPool::addTask(Task &&task){
    if(shutDown_){
        return;
    }
    taskQueue_.addTask(std::move(task));
    
}
