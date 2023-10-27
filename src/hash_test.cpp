#include "hash.hpp"
#include"timer.h"
#include <iostream>
using namespace vvstl;

int main() {
    Timer time;
    Hash hash;
    hash.insert("wj1", 1);
    hash.insert("wj2", 2);
    hash.insert("wj3", 3);
    hash.insert("wj4", 4);
    hash.insert("wj5", 5);
    hash.insert("wj6", 6);

    std::cout << hash.size()<<"\n";
    std::cout<<hash.getVal("wj1")<<"\n";
    std::cout<<hash.getVal("wj2")<<"\n";
    std::cout<<hash.getVal("wj3")<<"\n";
    std::cout<<hash["wj4"]<<"\n";
    std::cout<<hash["wj5"]<<"\n";
    std::cout<<hash["wj6"]<<"\n";



    return 0;
}