#include "vector.hpp"
#include <iostream>
#include <vector>
using namespace vvstl;

class Object {
private:
    int* a_;

public:
    Object(int value=0)
        : a_(new int[3]) {
        for (int i = 0; i < 3; i++) {
            a_[i] = value;
        }
    }
    Object(Object&& that) {
        a_ = that.a_;
        that.a_ = nullptr;
    }
    Object& operator=(Object&& that){
        a_=that.a_;
        that.a_=nullptr;
        return *this;
    }
    Object& operator=(const Object& that){
        delete [] a_;
        a_= new int[3];
        for(int i=0;i<3;i++){
            a_[i]=that.a_[i];
        }
        return *this;
    }
    Object(const Object& that){
        delete [] a_;
        a_= new int[3];
        for(int i=0;i<3;i++){
            a_[i]=that.a_[i];
        }
    }
    void print() { std::cout << "Object" << a_[0] << "\n"; }
    ~Object() {
        delete[] a_;
        // std::cout << "Obejct destruct"
        //           << "\n";
    }
};

int main() {
    int i1 = 1, i2 = 2, i3 = 3;
    Object o1(1);
    Object o2(2);
    Object o3(3);
    Vector<Object> v;
    v.push_back(std::move(o1));
    v.push_back(std::move(o2));
    v.push_back(std::move(o3));
    // Vector<Object> v2;
    // v2=v;
    // std::cout<<v.size()<<"\n";
    // std::cout<<v2.size()<<"\n";
    // v2=std::move(v);
    // std::cout<<v.size()<<"\n";
    // std::cout<<v2.size()<<'\n';
    for (size_t i = 0; i < v.size(); i++) {
        v[i].print();
    }
    Object o4(4);
    v.insert(1, std::move(o4));
    for (size_t i = 0; i < v.size(); i++) {
        v[i].print();
    }
    return 0;
}