#ifndef SINGLEBASE_H
#define SINGLEBASE_H

#include <cstddef>
#include<iostream>
class Animal{
    virtual void method()=0;

};

class Dog:public Animal{
    void method() override{
        std::cout<<"dog wdnmd"<<"\n";
    }
};

class Cat:public Animal{
    void method() override{
        std::cout<<"cat wdnmd"<<"\n";
    }
};
class SimpleFactory {
protected:
    explicit SimpleFactory(){
        std::cout<<"Single Base Construct"<<"\n";
    }
    // static SingleBase instance_;//饿汉式，在main函数前就会进行类构造。
    public:
    enum AnimalType{
        DogType,
        CatType
    };
    SimpleFactory(const SimpleFactory& that)=delete;
    SimpleFactory& operator=(const SimpleFactory& that)=delete;
    virtual ~SimpleFactory(){
        std::cout<<"Single Base Destruct"<<"\n";
    }
    static SimpleFactory& getInstance(){
        static SimpleFactory instance_;
        return instance_;
    }
    Animal* createAnimal(AnimalType type){
        switch(type){
            case DogType:
            return new Dog();
            case CatType:
            return new Cat();
            default:
            break;
        }
        return nullptr;
    }
};
// SingleBase SingleBase::instance_;

#endif