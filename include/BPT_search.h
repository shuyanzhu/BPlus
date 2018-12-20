//
// Created by eureka on 18-12-20.
//

#ifndef BPLUS_BPT_SEARCH_H
#define BPLUS_BPT_SEARCH_H

#include "BPTNode.h"
#include "BPT.h"
template <typename T>
BPTNode<T> *BPT<T>::search(const T &e) {
    BPTNode<T> *v = _root; _hot = v;
    while(v){// 逐层查找
        Rank r = v->key.search(e);
        if(r == -1)break;
        if(e == v->key[r] && v->child[r] == NULL)return v;
        _hot = v; v = v->child[r];
    }
    return NULL; // 失败返回
}
#endif //BPLUS_BPT_SEARCH_H
