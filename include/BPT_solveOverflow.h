//
// Created by eureka on 18-12-20.
//

#ifndef BPLUS_BPT_SOLVEOVERFLOW_H
#define BPLUS_BPT_SOLVEOVERFLOW_H

#include "BPTNode.h"
#include "BPT.h"
template <typename T>
void BPT<T>::sovleOverflow(BPTNode <T> *v) {
    if(_order >= v->child.size())return;

    Rank s = (_order+1)/2; // 上整, 原来节点key的个数
    BPTNode<T> *u = new BPTNode<T>(_order); // 需要分裂一个新节点
	_node_num++;
    for(Rank j=0;j<_order + 1 -s;j++){ // 分裂当前节点
        u->key.insert(j, v->key.remove(s));
        u->child.insert(j, v->child.remove(s));
    }
	if (u->child[0]) // 非叶节点
		for (Rank j = 0; j < _order + 1 - s; j++)
			u->child[j]->parent = u;

	// 双向链表的插入！！！
	u->prev = v; u->next = v->next;
	if(u->next)u->next->prev = u;
	v->next = u;
	// 父亲节点操作
	BPTNode<T> *p = v->parent;
    if(!p){
		_node_num++;
		h++;
        _root = p = new BPTNode<T>(_order); // 当前节点为根节点
		p->key.insert(v->key[0]); // 插入key
        p->child.insert(v); // 向父节点插入child
        v->parent = p; // 指向父节点
    }
	Rank r = p->key.search(u->key[0]); // 插入u的相关信息
    p->key.insert(r+1, u->key[0]);
    p->child.insert(r+1, u);
    u->parent = p;
    sovleOverflow(p); // 向上迭代，最多为logn
}
#endif//BPLUS_BPT_SOLVEOVERFLOW_H
