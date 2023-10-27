#ifndef THREAD_POOL_HPP
#define THREAD_POOL_HPP

#include <condition_variable>
#include <corecrt.h>
#include <cstddef>
#include <functional>
#include <iostream>
#include <list>
#include <mutex>
#include <queue>
#include <thread>
#include <unordered_map>

/*
author:vv12138vv
learning thread and code my thread pool
as a thread pool ,we need:
1. task queue
2. worker thread:also called consumer
3. manager thread:also called producer
*/
namespace vvmemory {
class Task {
private:
    std::function<void(void*)> callBack_;
    void* arg_;

public:
    Task() {
        callBack_ = nullptr;
        arg_ = nullptr;
    }
    Task(std::function<void(void*)> func, void* arg)
        : callBack_(func)
        , arg_(arg) {}
};

class TaskQueue {
private:
    std::queue<Task> taskQueue_;
    std::mutex mtx_;
public:
    TaskQueue();
    ~TaskQueue();
    void addTask(Task&&);
    Task getTask();
    inline size_t getTaskNum(){
        return taskQueue_.size();
    }

};

class ThreadPool {
private:
    TaskQueue taskQueue_;
    std::unordered_map<size_t, std::thread> threads_;
    std::mutex threadMtx;
    std::condition_variable cv;
    size_t minThreadNum_;
    size_t maxThreadNum_;
    size_t busyNum_;
    size_t aliveNum_;
    size_t managerIndex_;
    bool shutDown_;
    
public:
    ThreadPool(size_t min=3,size_t max=20);
    ~ThreadPool();
    void addTask(Task&&); 
    size_t getBusyNum();
    size_t getAliveNum();
};



}   // namespace vvmemory




#endif