#pragma once
#include <iostream>


namespace vvstl {
using namespace std;
template<typename T>
class Vector {
private:
    T* memory_ = nullptr;
    size_t capacity_ = 2;
    size_t size_ = 0;

private:
    void re_allocate(size_t new_capacity) {
        // 1. allocate new memory
        // 2. copy/move old memory
        // 3. delete old memory
        if (size_ > new_capacity) {   // if shrink the vector,we need update size <=
                                      // new_capacity,and it will lose some data
            size_ = new_capacity;
        }
        T* new_memory = new T[new_capacity];
        for (size_t i = 0; i < size_;
             i++) {   // why don't use memcopy?A: int or double ... primitive type is fine,but // objects may need construcotrs
            new_memory[i] = std::move(memory_[i]);   // use move so that we don't need copy entire object.
        }
        delete[] memory_;   // when use move like upside,do we need delete[]?A: i think it doesn't matter,cause we move,
        // when operator= was called the data in memory block has been move.so we ddlete memory_ will not cause problem.
        memory_ = new_memory;
        capacity_ = new_capacity;
    }

public:
    explicit Vector(size_t capacity = 2) { re_allocate(capacity); }

    Vector(size_t capacity, const T& data) {
        re_allocate(capacity);
        for (int i = 0; i < size_; i++) {
            memory_[i] = data;
        }
    }
    explicit Vector(const Vector& that) {
        delete[] memory_;
        size_ = that.size_;
        capacity_ = that.capacity_;
        memory_ = new T[that.capacity_];
        for (int i = 0; i < size_; i++) {
            memory_[i] = that.memory_[i];
        }
    }
    Vector& operator=(const Vector& that) {
        delete[] memory_;
        size_ = that.size_;
        capacity_ = that.capacity_;
        memory_ = new T[that.capacity_];
        for (int i = 0; i < size_; i++) {
            memory_[i] = that.memory_[i];
        }
        return *this;
    }
    explicit Vector(Vector&& that) {
        delete[] memory_;
        memory_ = std::forward<T*>(that.memory_);
        capacity_ = that.capacity_;
        size_ = that.size_;
        that.memory_ = nullptr;
        that.size_ = 0;
        that.capacity_ = 0;
    }

    Vector& operator=(Vector&& that) {
        delete[] memory_;
        memory_ = std::forward<T*>(that.memory_);
        capacity_ = that.capacity_;
        size_ = that.size_;
        that.memory_ = nullptr;
        that.size_ = 0;
        that.capacity_ = 0;
        return *this;
    }
    ~Vector() { delete[] memory_; }

    void push_back(const T& data) {
        if (size_ >= capacity_) {
            re_allocate(capacity_ + capacity_);   // double the capacity
        }
        memory_[size_] = data;
        size_++;
    }

    void push_back(T&& data) {
        if (size_ >= capacity_) {
            re_allocate(capacity_ + capacity_);   // double the capacity
        }
        memory_[size_] = std::move(data);
        size_++;
    }

    template<typename... Args>
    T& emplace_back(Args&&... args) {
        if (size_ >= capacity_) {
            re_allocate(capacity_ + capacity_);   // double the capacity
        }
        memory_[size_] = T(std::forward<Args>(args)...);
        size_ += 1;
        return memory_[size_ - 1];
    }

    void pop_back() {
        if (size_ > 0) {
            memory_[size_ - 1].~T();   // destructe the object
            size_ -= 1;
        }
    }

    void clear() {
        for (size_t i = 0; i < size_; i++) {
            memory_[i].~T();
        }
        size_ = 0;
    }
    bool empty(){
        if(size_){
            return false;
        }
        return false;
    }
    const T& operator[](size_t index) const { return memory_[index]; }
    T& operator[](size_t index) { return memory_[index]; }
    size_t size() const { return size_; }
};
}   // namespace vvstl
