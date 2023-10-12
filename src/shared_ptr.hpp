#pragma once
#include <mutex>

/*
Author:vv12138vv
mytoy:implement a SharedPtr to better understand shared_ptr;
As a SharedPtr,it needs the following aspects:
tips:
1. T* ptr point the object
2. a shared count (must be new,otherwise there weill be many different couts)
3. in order to protect thread safety , better to add lock in SharePtr
*/


namespace vv_memory {
template<typename T>
class SharedPtr {
private:
    T* raw_;
    size_t*
        count_;   // size_t is a unsigned integer and the size is dependent on the os and compiler
    std::mutex* mutex_;

    void release();
    inline void add_count();
    inline void del_count();

public:
    explicit SharedPtr();
    explicit SharedPtr(T* p);
    explicit SharedPtr(const SharedPtr& that);
    SharedPtr& operator=(const SharedPtr& thar);
    explicit SharedPtr(SharedPtr&& that);
    SharedPtr& operator=(SharedPtr&& that);
    virtual ~SharedPtr();
    T* operator->() noexcept;
    T& operator*() noexcept;
    inline T* get() noexcept;
    int get_count() noexcept;
};

template<typename T>
SharedPtr<T>::SharedPtr()
    : raw_(nullptr)
    , count_(new size_t(1))
    , mutex_(new std::mutex) {}

template<typename T>
SharedPtr<T>::SharedPtr(T* p)
    : raw_(p)
    , count_(new size_t(1))
    , mutex_(new std::mutex) {}


template<typename T>
inline void SharedPtr<T>::add_count() {
    mutex_->lock();
    *count_ += 1;
    mutex_->unlock();
}

template<typename T>
inline void SharedPtr<T>::del_count() {
    mutex_->lock();
    *count_ -= 1;
    mutex_->unlock();
}

template<typename T>
SharedPtr<T>::SharedPtr(const SharedPtr<T>& that)
    : raw_(that.raw_)
    , count_(that.count_)
    , mutex_(that.mutex_) {
    add_count();
}

template<typename T>
SharedPtr<T>& SharedPtr<T>::operator=(const SharedPtr<T>& that) {
    if (this != &that) {
        if (raw_ != that.raw_) {
            release();   // release the memory that this object probably have;
            raw_ = that.raw_;
            count_ = that.count_;
            mutex_ = that.mutex_;
            add_count();
        }
    }
    return *this;
}

template<typename T>
SharedPtr<T>::SharedPtr(SharedPtr<T>&& that) {
    raw_ = std::forward<T*>(that.raw_);
    count_ = std::forward<size_t*>(that.count_);
    mutex_ = std::forward<std::mutex*>(that.mutex_);
    that.raw_ = nullptr;
    that.count_ = nullptr;
    that.mutex_ = nullptr;
}

template<typename T>
SharedPtr<T>& SharedPtr<T>::operator=(SharedPtr<T>&& that) {
    raw_ = std::forward<T*>(that.raw_);
    count_ = std::forward<size_t*>(that.count_);
    mutex_ = std::forward<std::mutex*>(that.mutex_);
    that.raw_ = nullptr;
    that.count_ = nullptr;
    that.mutex_ = nullptr;
}

template<typename T>
SharedPtr<T>::~SharedPtr() {
    release();
}

template<typename T>
void SharedPtr<T>::release() {
    bool isDeleted = false;
    mutex_->lock();
    // del_count() 此处为大坑，前一句mutex加锁后，进入del_count后再次加锁会导致死锁，线程阻塞。
    *count_-=1;
    if (count_ == 0) {
        delete count_;
        delete raw_;
        count_ = nullptr;
        raw_ = nullptr;
        isDeleted = true;
    }
    mutex_->unlock();
    if (isDeleted) {
        delete mutex_;
        mutex_ = nullptr;
    }
}

template<typename T>
inline T* SharedPtr<T>::get() noexcept {
    return raw_;
}

template<typename T>
T* SharedPtr<T>::operator->() noexcept {
    return raw_;
}

template<typename T>
T& SharedPtr<T>::operator*() noexcept {
    return *raw_;
}

template<typename T>
int SharedPtr<T>::get_count() noexcept {
    return *count_;
}

}   // namespace vv_memory