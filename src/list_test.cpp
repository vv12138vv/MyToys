#include "list.hpp"
#include <iostream>
#include <utility>

using namespace vvstl;


class Object {
private:
    int* a_ = nullptr;

public:
    Object(int value = 0)
        : a_(new int[3]) {
        for (int i = 0; i < 3; i++) {
            a_[i] = value;
        }
    }
    Object(const Object& that) {
        delete[] a_;
        a_ = new int[3];
        for (int i = 0; i < 3; i++) {
            a_[i] = that.a_[i];
        }
    }
    Object(Object&& that) {
        delete [] a_;
        a_ = that.a_;
        that.a_ = nullptr;
    }
    Object& operator=(Object&& that) {
        delete [] a_;
        a_ = that.a_;
        that.a_ = nullptr;
        return *this;
    }
    Object& operator=(const Object& that) {
        delete[] a_;
        a_ = new int[3];
        for (int i = 0; i < 3; i++) {
            a_[i] = that.a_[i];
        }
        return *this;
    }
    void print() { std::cout << "Object" << a_[0] << "\n"; }
    ~Object() {
        std::cout<<"Object Destruct:"<<a_[0]<<"\n";
        delete[] a_;
        a_ = nullptr;
    }
};


int main() {
    List<Object> list;
    Object o1(1);
    Object o2(2);
    Object o3(3);
    std::cout << list.empty() << "\n";
    std::cout << list.size() << "\n";
    list.push_back(std::move(o1));
    list.push_back(std::move(o2));
    list.push_front(std::move(o3));
    Object o4(4);
    list.insert(std::move(o4),1);
    for(size_t i=0;i<list.size();i++){
        list[i].print();
    }
    return 0;
}