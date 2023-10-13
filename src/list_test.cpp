#include<iostream>
#include <utility>

int main(){
    int * p=new int(1);
    int * m;
    m=std::move(p);
    std::cout<<p<<"\n";
    std::cout<<m<<"\n";
}