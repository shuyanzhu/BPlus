#pragma once

#pragma once
#include "vector/vector.h"

template <typename T>
struct BPTNode {
    BPTNode<T> *parent;
    Vector<T> key
    Vector<BPTNode<T> *> child;

    BPTNode():parent(NULL){}
//    BPTNode(T e, BPTNode<T> *child=NULL){
//        parent = NULL;
//        key.insert(0, e);
//    }

};
