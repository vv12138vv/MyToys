#include "unique_ptr.hpp"
#include<iostream>
#include <memory>
#include <utility>
class Base {
private:

public:
    int a_;
    int b_;
    int c_;
    Base(int a=0, int b=0, int c=0)
        : a_(a)
        , b_(b)
        , c_(c) {
        std::cout<<"Base Constructor\n";
        }
    virtual ~Base(){
        std::cout<<"Base Destructor\n";
    }
    void print(){
        std::cout<<a_<<" "<<b_<<" "<<c_<<"\n";
        return;
    }


};

class Derive:public Base{
private:
    int* new_land;
public:
    Derive(){
        std::cout<<"Derive Constructor\n";
        new_land=new int [10];
        for(int i=0;i<10;i++){
            new_land[i]=1;
        }
    }
    ~Derive(){
        std::cout<<"Derive Destructor\n";
        delete [] new_land;
    }
};


int main(){
    auto ptr=vv_memory::make_unique<Base>(1,2,3);
    vv_memory::UniquePtr<Base> p(std::move(ptr));
    if(!ptr){
        std::cout<<"test";
    }
    return 0;
}