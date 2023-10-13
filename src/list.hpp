#pragma once
/*
Author:vv12138vv
Comment:Implement a List,i think need something following.
1. ListNode
2. List
*/


#include <cstddef>
#include <exception>
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
        : data_(std::move(data))
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
    virtual ~ListNode() {}
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
    size_t size_ = 0;   // according to stl,use it for O(1)

public:
    explicit List() noexcept
        : head_(nullptr)
        , tail_(nullptr)
        , size_(0) {}

    virtual ~List() noexcept {
        ListNode<T>* cur = head_;
        while (cur != tail_ && cur != nullptr) {
            ListNode<T>* next = cur->next_;
            delete cur;
            cur = next;
        }
        delete cur;
        head_ = nullptr;
        tail_ = nullptr;
    }
    explicit List(const List<T>& that) {}
    explicit List(List<T>&& that) {}
    List& operator=(const List<T>& that) {}
    List& operator=(List<T>&& that) {}

    void push_back(const T& data) {
        if (head_ == nullptr) {
            head_ = new ListNode<T>(data);
            tail_ = head_;
            head_->next_ = head_;
            head_->pre_ = head_;
            size_ += 1;
            return;
        }
        ListNode<T>* temp = new ListNode<T>(data);
        tail_->next_ = temp;
        temp->pre_ = tail_;
        tail_ = temp;
        tail_->next_ = head_;
        head_->pre_ = tail_;
        size_ += 1;
    }
    void push_back(T&& data) {
        if (head_ == nullptr) {
            head_ = new ListNode<T>(std::move(data));
            tail_ = head_;
            head_->next_ = head_;
            head_->pre_ = head_;
            size_ += 1;
            return;
        }
        ListNode<T>* temp = new ListNode<T>(std::move(data));
        tail_->next_ = temp;
        temp->pre_ = tail_;
        tail_ = temp;
        tail_->next_ = head_;
        head_->pre_ = tail_;
        size_ += 1;
    }
    void push_front(const T& data) {
        if (head_ == nullptr) {
            head_ = new ListNode<T>(data);
            tail_ = head_;
            head_->next_ = head_;
            head_->pre_ = head_;
            size_ += 1;
            return;
        }
        ListNode<T>* temp = new ListNode<T>(data);
        head_->pre_ = temp;
        temp->next_ = head_;
        temp->pre_ = tail_;
        tail_->next_ = temp;
        head_ = temp;
        size_ += 1;
    }
    void push_front(T&& data) {
        if (head_ == nullptr) {
            head_ = new ListNode<T>(std::move(data));
            tail_ = head_;
            head_->next_ = head_;
            head_->pre_ = head_;
            size_ += 1;
            return;
        }
        ListNode<T>* temp = new ListNode<T>(std::move(data));
        head_->pre_ = temp;
        temp->next_ = head_;
        temp->pre_ = tail_;
        tail_->next_ = temp;
        head_ = temp;
        size_ += 1;
    }
    void pop_back() {
        if (tail_ == nullptr) {
            return;
        }
        if (head_ == tail_) {
            // tail_->data_.~T();//no need to call the destructor explicityly
            delete tail_;   // when delete, it will be called automatically
            head_ = nullptr;
            tail_ = nullptr;
            size_ -= 1;
            return;
        }
        ListNode<T>* temp = tail_->pre_;
        // tail_->data_.~T();
        temp->next_ = tail_->next_;
        head_->pre_ = temp;
        delete tail_;
        size_ -= 1;
        tail_ = temp;
    }
    void pop_front() {
        if (head_ == nullptr) {
            return;
        }
        if (head_ == tail_) {
            delete head_;
            head_ = nullptr;
            tail_ = nullptr;
            size_ -= 1;
            return;
        }
        ListNode<T>* temp = head_->next_;
        tail_->next_ = temp;
        temp->pre_ = tail_;
        delete head_;
        size_ -= 1;
        head_ = temp;
    }
    bool empty() { return head_ == nullptr; }
    size_t size() const { return size_; }
    T& operator[](size_t index) {
        if (index > size_ - 1 || index < 0) {
            return tail_->data_;
        }
        int count = 0;
        ListNode<T>* cur = head_;
        while (count != index) {
            cur = cur->next_;
            count += 1;
        }
        return cur->data_;
    }
    T& front() { return head_->data_; }
    T& back() { return tail_->data_; }
    void insert(const T& data, size_t index) {
        if (index > size_ - 1 || index < 0) {
            return;
        }
        ListNode<T>* cur = head_;
        size_t count = 0;
        while (count != index) {
            cur = cur->next_;
            count += 1;
        }
        ListNode<T>* pre = cur->pre_;
        ListNode<T>* temp = new ListNode<T>(data);
        pre->next_ = temp;
        temp->pre_ = pre;
        temp->next_ = cur;
        cur->pre_ = temp;
        size_ += 1;
    }
    void insert(T&& data, size_t index) {
        if (index > size_ - 1 || index < 0) {
            return;
        }
        ListNode<T>* cur = head_;
        size_t count = 0;
        while (count != index) {
            cur = cur->next_;
            count += 1;
        }
        ListNode<T>* pre = cur->pre_;
        ListNode<T>* temp = new ListNode<T>(std::move(data));
        pre->next_ = temp;
        temp->pre_ = pre;
        temp->next_ = cur;
        cur->pre_ = temp;
        size_ += 1;
    }

};   // namespace vvstl
}