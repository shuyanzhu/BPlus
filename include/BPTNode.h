#pragma once

//#include "vector/vector.h"
#include "Array.h"
int num = 0;
template <typename T>
struct BPTNode {
    BPTNode<T> *parent;
  //  Vector<T> key;
   // Vector<BPTNode<T> *> child;
	Array<T> key;
	Array<BPTNode<T> *> child;
    BPTNode<T> *prev, *next;
    // 默认构造函数只在根节点创建时被调用
	BPTNode(int order) :key(order + 1), child(order + 1), parent(NULL), prev(NULL), next(NULL) { num++; }
	BPTNode(BPTNode &from) :key(from.key), child(from.child), parent(NULL), prev(NULL), next(NULL) {}
	~BPTNode() { num--; }
	int seek() {
		return sizeof(BPTNode<T> *) * 3 + key.seek() + child.seek();
	}
};
