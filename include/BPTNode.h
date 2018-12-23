#pragma once

#pragma once
#include "vector/vector.h"
#include "Array.h"

template <typename T>
struct BPTNode {
    BPTNode<T> *parent;
    Array<T> key;
    Array<BPTNode<T> *> child;
	//Vector<T> key;
	//Vector<BPTNode<T> *> child;
    BPTNode<T> *prev, *next;
    // 默认构造函数只在根节点创建时被调用
	BPTNode(int order): key(order+1), child(order+1), parent(NULL), prev(NULL), next(NULL) {}
};
