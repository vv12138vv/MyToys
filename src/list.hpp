#pragma once
/*
Author:vv12138vv
Comment:Implement a List,i think need something following.
1. ListNode
2. List
*/


#include <cstddef>
#include <utility>
namespace vvstl {
using namespace std;
template<typename T>
class ListNode {
public:
    T data_;
    ListNode<T>* next_ = nullptr;
    ListNode<T>* pre_ = nullptr;

public:
    explicit ListNode(const T& data)
        : data_(data)
        , next_(nullptr)
        , pre_(nullptr) {}
    explicit ListNode(T&& data)
        : data_(data)
        , next_(nullptr)
        , pre_(nullptr) {}
    explicit ListNode(const ListNode<T>& that) {
        data_ = that.data_;
        next_ = that.next_;
        pre_ = that.pre_;
    }
    ListNode& operator=(const ListNode<T>& that) {
        data_ = that.data_;
        next_ = that.next_;
        pre_ = that.pre_;
    }
    explicit ListNode(ListNode<T>&& that) {
        data_ = std::move(that.data_);
        next_ = std::move(that.next_);
        pre_ = std::move(that.pre_);
        that.next_ = nullptr;
        that.pre_ = nullptr;
    }
    ListNode& operator=(ListNode<T>&& that) {
        data_ = std::move(that.data_);
        next_ = std::move(that.next_);
        pre_ = std::move(that.pre_);
        that.next_ = nullptr;
        that.pre_ = nullptr;
        return *this;
    }
};

template<typename T>
class List {
private:
    ListNode<T>* head_ = nullptr;
    ListNode<T>* tail_ = nullptr;

public:
    explicit List() noexcept
        : head_(nullptr)
        , tail_(nullptr) {}

    virtual ~List() noexcept {}
    explicit List(const List<T>& that) {}
    explicit List(List<T>&& that) {}
    List& operator=(const List<T>& that){
        
    }
    List& operator=(List<T>&& that){

    }
    void push_back(const T& data) {
        if (head_ == nullptr) {
            head_ = new ListNode<T>(data);
            tail_ = head_;
            head_->next_ = head_;
            head_->pre_ = head_;
            return;
        }
        ListNode<T>* temp = new ListNode<T>(data);
        tail_->next_ = temp;
        temp->pre_ = tail_;
        tail_ = temp;
        tail_->next_ = head_;
        head_->pre_ = tail_;
    }
    void push_back(T&& data) {
        if (head_ == nullptr) {
            head_ = new ListNode<T>(std::move(data));
            tail_ = head_;
            head_->next_ = head_;
            head_->pre_ = head_;
            return;
        }
        ListNode<T>* temp = new ListNode<T>(std::move(data));
        tail_->next_ = temp;
        temp->pre_ = tail_;
        tail_ = temp;
        tail_->next_ = head_;
        head_->pre_ = tail_;
    }
    void push_front(const T& data) {
        if (head_ == nullptr) {
            head_ = new ListNode<T>(data);
            tail_ = head_;
            head_->next_ = head_;
            head_->pre_ = head_;
            return;
        }
        ListNode<T>* temp = new ListNode<T>(data);
        head_->pre_ = temp;
        temp->next_ = head_;
        temp->pre_ = tail_;
        tail_->next_ = temp;
        head_ = temp;
    }
    void push_front(T&& data) {
        if (head_ == nullptr) {
            head_ = new ListNode<T>(std::move(data));
            tail_ = head_;
            head_->next_ = head_;
            head_->pre_ = head_;
            return;
        }
        ListNode<T>* temp = new ListNode<T>(std::move(data));
        head_->pre_ = temp;
        temp->next_ = head_;
        temp->pre_ = tail_;
        tail_->next_ = temp;
        head_ = temp;
    }
    bool empty() {
        return head_==nullptr;
    }
    size_t size() {
        ListNode<T>* cur = head_;
        if (cur == nullptr) {
            return 0;
        }
        size_t res = 0;
        do {
            res += 1;
            cur = cur->next_;
        } while (cur != head_);
        return res;
    }
};
}   // namespace vvstl