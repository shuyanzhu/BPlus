//
// Created by eureka on 18-12-20.
//

#ifndef BPLUS_BPT_INSERT_H
#define BPLUS_BPT_INSERT_H

#include "BPTNode.h"
#include "BPT.h"

template <typename T>
bool BPT<T>::insert(const T &e) {
    BPTNode<T> *v = search(e);if(v)return false; // 确认目标节点不存在
    Rank r = _hot->key.search(e); // 找到叶子节点
    _hot->key.insert(r+1, e); // 将新的关键码插入对应的位置
    _hot->child.insert(r+1, NULL); // 将空节点插入叶子节点中
    _size++; // 全树高度+1
    sovleOverflow(_hot); // 处理新插入节点分裂操作
    return true;
}
#endif //BPLUS_BPT_INSERT_H
