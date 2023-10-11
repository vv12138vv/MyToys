#pragma once
#include <corecrt.h>
#include <cstddef>
#include <iostream>
#include <new>

namespace vvstl {
using namespace std;
template <typename T> class Vector {
private:
  T * memory_;
  size_t capacity_;
  size_t size_;

public:
  Vector() {
	this->capacity_=0;
	this->size_=0;
	this->memory_=nullptr;
  }

  Vector(size_t capacity,size_t init){

  }
  void reserve(size_t capacity){
  }

};
} // namespace vvstl