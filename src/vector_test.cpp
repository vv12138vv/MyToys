#include "vector.hpp"
#include<iostream>
#include<vector>
using namespace vvstl;

class Object {
private:
    int a_;
    int b_;
    int c_;

public:
    Object(int a=1,int b=1,int c=1):a_(a),b_(b),c_(c){}
    void print(){
        std::cout<<"Object"<<a_<<"\n";
    }
    ~Object(){
        std::cout<<"Obejct destruct"<<"\n";
    }
};

int main() {
    int i1=1,i2=2,i3=3;
    Object o1{1,1,1};
    Object o2{2,2,2};
    Object o3{3,3,3};
    Vector<Object> v;
    v.push_back(std::move(o1));
    v.push_back(std::move(o2));
    v.push_back(std::move(o3));
    Vector<Object> v2;
    v2=v;
    std::cout<<v.size()<<"\n";
    std::cout<<v2.size()<<"\n";
    v2=std::move(v);
    std::cout<<v.size()<<"\n";
    std::cout<<v2.size()<<'\n';
    return 0;
}