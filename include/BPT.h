#pragma once

#include "BPTNode.h"

// B+ Tree, 增删查，阶次、大小、根节点、判空
template <typename T>
class BPT{
private:
    int _size;
    int _order;
    BPTNode<T> *_root;
    void release(void *);
    void sovleOverflow(BPTNode<T> *);
    void sovleUnderflow(BPTNode<T> *);

public:
    BPT(int order=3):_order(3), _size(0){
        _root = new BPTNode<T>();
    }
    ~BPT(){if(_root)release(_root);}
    // 阶次、大小、根节点、判空
    const int order(){ return _order;}
    const int size(){ return _size;}
    BPTNode<T> * &root(){ return _root;}
    bool empty() const {return !_root;}
    // 增删查
    BPTNode<T> search(const T &e);
    bool insert(const T &e);
    bool remove(const T &e); 
};// B+ Tree

#include "BPT_implementation.h"

