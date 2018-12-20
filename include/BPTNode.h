#pragma once

#pragma once
#include "vector/vector.h"

template <typename T>
struct BPTNode {
    BPTNode<T> *parent;
    Vector<T> key;
    Vector<BPTNode<T> *> child;
    BPTNode<T> *prev, *next;
    // 默认构造函数只在根节点创建时被调用
	BPTNode() :parent(NULL), prev(NULL), next(NULL) {}
//    BPTNode(T e, BPTNode<T> *child=NULL){
//        parent = NULL;
//        key.insert(0, e);
//    }

};
