
#include <any>
#include <cmath>
#include <cstddef>
#include <list>
#include <string>
#include <vector>


namespace vvstl {
using namespace std;
struct HashNode {
    string key_;
    int val_;
    HashNode(const string& key, int val)
        : key_(key)
        , val_(val) {}
    HashNode(const HashNode& that) {
        key_ = that.key_;
        val_ = that.val_;
    }
    HashNode& operator=(const HashNode& that) {
        key_ = that.key_;
        val_ = that.val_;
        return *this;
    }
};
class Hash {   // a simple hash for <string,int>
private:
    vector<list<HashNode>> container_;
    size_t size_ = 0;

public:
    Hash() {
        container_.resize(4);
        size_ = 0;
    }
    Hash(size_t size){
        container_.resize(size);
        size_=0;
    }
    ~Hash() = default;
    Hash(const Hash& that){
        size_=that.size_;
        container_=that.container_;
    }
    size_t hashFunc(const string& key,int size) {
        size_t sum = 0;
        for (auto i : key) {
            sum += i;
        }
        size_t index = sum % size;
        return index;
    }
    void insert(const string& key, int val) {
        size_t index = hashFunc(key,container_.size());
        for (auto i : container_[index]) {
            if (i.key_ == key) {
                i.val_ = val;
                return;
            }
        }
        HashNode temp(key, val);
        container_[index].push_back(temp);
        size_ += 1;
        if(hashFactor()>=1){
            reHash();
        }
    }
    size_t count(const string& key) {
        size_t res = 0;
        size_t index = hashFunc(key,container_.size());
        for (auto i : container_[index]) {
            if (i.key_ == key) {
                res = 1;
                break;
            }
        }
        return res;
    }
    HashNode get(const string& key) {
        size_t index = hashFunc(key,container_.size());
        HashNode res(key, -1);
        for (auto i : container_[index]) {
            if (i.key_ == key) {
                res = i;
                break;
            }
        }
        return res;
    }
    int getVal(const string& key) {
        HashNode temp = get(key);
        return temp.val_;
    }
    void remove(const string& key) {
        size_t index = hashFunc(key,container_.size());
        for (auto it = container_[index].begin(); it != container_[index].end(); it++) {
            if (it->key_ == key) {
                container_[index].erase(it);
                size_ -= 1;
                break;
            }
        }
    }
    float hashFactor(){
        return static_cast<float>(size_)/static_cast<float>(container_.size());
    }
    void reHash() {

        vector<list<HashNode>> newContainer(container_.size()*2);
        for(auto& list:container_){
            for(auto& node:list){
                size_t newIndex=hashFunc(node.key_,newContainer.size());
                newContainer[newIndex].push_back(node);
            }
        }
        std::swap(container_, newContainer);
    }
    size_t size(){
        return size_;
    }
    int operator[](const string& key){
        return getVal(key);
    }
};
}   // namespace vvstl