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
    BPTNode<T> *u = new BPTNode<T>(); // 需要分裂一个新节点
    for(Rank j=0;j<_order-s;j++){ // 分裂当前节点
        u->key.insert(j, v->key.remove(s));
        u->child.insert(j, v->child.remove(s));
    }
    v->next = u; u->prev = v;
    BPTNode<T> *p = v->parent;
    if(!p){
        _root = p = new BPTNode<T>(); // 当前节点为根节点
        p->key.insert(v->key[0]);
        p->child.insert(v);
        v->parent = p;
    }
    p->key.insert(u->key[0]);
    p->child.insert(u);
    u->parent = p;
    sovleOverflow(p); // 向上迭代，最多为logn
}
#endif//BPLUS_BPT_SOLVEOVERFLOW_H
