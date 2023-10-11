#pragma once
#include <iostream>
#include <utility>

namespace vv_memory {
/*
实现一个简单的unique_ptr
特点：可以独享其指向的对象，在智能指针的生命周期结束时，对象的生命周期也结束。
独占所有权意味着无法通过复制的方式获得对象管理指针，只能通过移动。
对象删除器：不同的对象可能有不同的删除函数，若不指定对象删除器，则使用默认的对象删除器。
*/
class Deleter {
public:
    Deleter() = default;

    template<typename T>
    void operator()(T* p) noexcept {   // noexcept表示不会引发异常
        if (p) {
            delete p;
        }
    }
};

template<typename T, typename D = Deleter>
class UniquePtr {
private:
    T* raw_;       // 裸指针
    D  deleter_;   // 删除器

public:
    explicit UniquePtr();   // explicit表示禁止隐式类型转换，尤其是单参数构造函数
    explicit UniquePtr(T* p);
    explicit UniquePtr(const UniquePtr& that) = delete;   // 拷贝构造函数,delete表示不支持,此处的const有妙用：1.为了强调不会对变量产生变化。2.const &使得可以引用左值和右值
    UniquePtr& operator=(const UniquePtr& that) = delete;   // 赋值构造函数
    explicit UniquePtr(UniquePtr&& that);                   // 移动构造函数
    UniquePtr& operator=(UniquePtr&& that);                       // 移动赋值构造函数
    T*   get() noexcept;
    D&   get_deleter() noexcept;
    void reset(T* p) noexcept;
    T* release() noexcept;
    explicit operator bool() const noexcept;
    T& operator*() const noexcept;
    T* operator->() const noexcept;
    virtual ~UniquePtr();
};

template<typename T, typename D>
UniquePtr<T, D>::UniquePtr()
    : raw_(nullptr) {}

template<typename T, typename D>
UniquePtr<T, D>::UniquePtr(T* p)
    : raw_(p) {}

template<typename T, typename D>
UniquePtr<T, D>::UniquePtr(
    UniquePtr&& that) {   // 被移动的对象已经失去了所有权，一定要将内部指针设置为nullptr
    raw_ = std::forward<T*>(that.raw_);
    deleter_ = std::forward<D>(that.deleter_);
    that.raw_ = nullptr;
}

template<typename T, typename D>
UniquePtr<T,D>& UniquePtr<T, D>::operator=(UniquePtr&& that) {
    raw_ = std::forward<T*>(that.raw_);
    deleter_ = std::forward<D>(that.deleter_);
    that.raw_ = nullptr;
    return *this;
}

template<typename T, typename D>
UniquePtr<T, D>::~UniquePtr<T, D>() {
    if (raw_) {
        deleter_(raw_);   // 使用删除器去释放内存
    }
    raw_ = nullptr;
}

template<typename T, typename D>
T* UniquePtr<T, D>::get() noexcept {
    return raw_;
}

template<typename T, typename D>
D& UniquePtr<T, D>::get_deleter() noexcept {
    return deleter_;
}

template<typename T, typename D>
UniquePtr<T, D>::operator bool() const noexcept {
    if (raw_) {
        return true;
    } else {
        return false;
    }
}

template<typename T, typename D>
T& UniquePtr<T, D>::operator*() const noexcept {
    return *raw_;
}

template<typename T, typename D>
T* UniquePtr<T, D>::operator->() const noexcept {
    return raw_;
}

template<typename T, typename D>
void UniquePtr<T, D>::reset(T* p) noexcept {
    if (raw_) {
        deleter_(raw_);
    }
    raw_ = p;
}
template<typename T, typename D>
T* UniquePtr<T,D>::release() noexcept{//消除UniquePtr对对象的管理
    T* new_ptr=raw_;
    raw_=nullptr;
    return new_ptr;
}
template<typename T,typename ...Args>
UniquePtr<T> make_unique(Args &&...args){
    return UniquePtr<T>(new T(std::forward<Args>(args)...));
}
}   // namespace vvmemory
