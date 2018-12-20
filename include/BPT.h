#pragma once

#include "BPTNode.h"

// B+ Tree, 增删查，阶次、大小、根节点、判空
template <typename T>
class BPT{
private:
    int _size; // 规模
    int _order; // 阶数
    BPTNode<T> *_root, *_hot; // 根节点，热节点
    void release(void *);
    void sovleOverflow(BPTNode<T> *);
    void sovleUnderflow(BPTNode<T> *);

public:
    BPT(int order=3):_order(order), _size(0){
        _root = new BPTNode<T>();
    }
//    ~BPT(){if(_root)release(_root);}
    // 阶次、大小、根节点、判空
    const int order(){ return _order;}
    const int size(){ return _size;}
    BPTNode<T> * &root(){ return _root;}
    bool empty() const {return !_size;}
    // 增删查
    BPTNode<T> *search(const T &e);
    bool insert(const T &e);
    bool remove(const T &e);
	// 遍历
	void print() {
		BPTNode<T> *v = _root;
		for (v; v != NULL; v = v->child[0]) {
			for (BPTNode<T> *u = v; u != NULL; u = u->next) {
				for (int i = 0; i < u->key.size(); i++)
					printf("%d ", u->key[i]);
				printf("--->");
			}
			printf("\n");
		}
	}
};// B+ Tree

#include "BPT_implementation.h"

