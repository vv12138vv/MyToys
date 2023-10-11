#pragma once
#include <iostream>

/*
mytoy:implement a SharedPtr to better understand shared_ptr;
As a SharedPtr,it needs the following aspects:
tips:
1. T* ptr point the object
2. a shared count (must be new,otherwise there weill be many different couts)
*/


namespace vv_memory {
template<typename T>
class SharedPtr {
private:
    T*      raw_;
    size_t* count_;//size_t is a unsigned integer and the size is dependent on the os and compiler
public:
    explicit SharedPtr();
    explicit SharedPtr(T* p);
    explicit SharedPtr(const SharedPtr& that);
    SharedPtr& operator=(const SharedPtr& thar);
    explicit SharedPtr(SharedPtr&& that);
    SharedPtr& operator=(SharedPtr&& that);
    T* operator->() noexcept;
    T& operator*() noexcept;
};
template <typename T>

}   // namespace vv_memory