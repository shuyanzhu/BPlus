#pragma once
#include "BPT.h"

template <typename T>
bool BPT<T>::rec_insert(BPTNode<T> *v, const T &e)
{
    int s = (_order + 1) / 2;
    auto r = v->key.search(e);
    BPTNode<T> *u = NULL;
    if (_size == 0 || v->child[0] == NULL) { // 递归基
        if (r >= 0 && v->key[r] == e) return false;
        v->key.insert(r + 1, e);
        v->child.insert(r + 1, NULL);
        _size++;
        if (v == _root) goto change_root;
        return true;
    }
    if (r < 0) r = r + 1;
    u = v->child[r];
    if (false == rec_insert(u, e)) return false; // 递归插入
    if (u->child.size() > _order) {
        BPTNode<T> *next = new BPTNode<T>(_order);
        u->key.split(next->key, s);
        u->child.split(next->child, s);
        if (next->child[0])
            for (Rank i = 0; i < next->key.size(); i++)
                next->child[i]->parent = next;
        next->next = u->next;
        next->prev = u;
        if (u->next) u->next->prev = next;
        u->next = next;
        v->key.insert(r + 1, next->key[0]);
        v->child.insert(r + 1, next);
        next->parent = v;
    }
    if (v->child[r]->key[0] < v->key[r]) v->key[r] = v->child[0]->key[0];
change_root:
    if (v == _root && v->key.size() > _order) { // 如果是根节点已满
        BPTNode<T> *next = new BPTNode<T>(_order);
        v->key.split(next->key, s);
        v->child.split(next->child, s);
        if (next->child[0])
            for (Rank i = 0; i < next->key.size(); i++)
                next->child[i]->parent = next;
        next->next = v->next;
        next->prev = v; // 指针互指
        if (v->next) v->next->prev = next;
        v->next = next;
        auto newroot = new BPTNode<T>(_order);
        newroot->key.insert(v->key[0]);
        newroot->child.insert(v);
        v->parent = newroot;
        newroot->key.insert(next->key[0]);
        newroot->child.insert(next);
        next->parent = newroot;
        _root = newroot;
        h++;
    }
    return true;
}
