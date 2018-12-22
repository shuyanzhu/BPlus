#pragma once

#include "BPTNode.h"
#include <assert.h>

// B+ Tree, 增删查，阶次、大小、根节点、判空
template <typename T>
class BPT
{
  private:
    int _node_num;
    int _size;                // 规模
    int _order;               // 阶数
    BPTNode<T> *_root, *_hot; // 根节点，热节点
    void release(void *);
    void sovleOverflow(BPTNode<T> *);
    bool rec_remove(BPTNode<T> *v, const T &e);

  public:
    int h; // 树高
    BPT(int order = 3)
        : _node_num(1)
        , h(0)
        , _order(order)
        , _size(0)
    {
        _root = new BPTNode<T>();
    }
    //    ~BPT(){if(_root)release(_root);}
    // 阶次、大小、根节点、判空
    const int order() { return _order; }
    const int size() { return _size; }
    BPTNode<T> *root() { return _root; }
    bool empty() const { return !_size; }
    // 增删查
    BPTNode<T> *search(const T &e);
    bool insert(const T &e);
    bool remove(const T &e) { return rec_remove(_root, e); }
    // 遍历函数,判断B+树正确性
    void print(int prnt)
    {
        int s = (1 + _order) / 2;
        BPTNode<T> *v = _root;
        for (v; v != NULL; v = v->child[0]) {
            int oldi = -1;
            for (BPTNode<T> *u = v; u != NULL; u = u->next) {
                assert(u != (void *) 3);
                if (u != _root) {
                    assert(u->child.size() == u->key.size());
                    assert(u->child.size() >= s);
                }
                if (u->prev != NULL) assert(u->prev->next == u);
                if (u->next != NULL) assert(u->next->prev == u);
                for (int i = 0; i < u->key.size(); i++) {
                    if (u->child[0]) {
                        assert(u->key[i] == u->child[i]->key[0]);
                        assert(u->child[i]->parent == u);
                    }
                    		assert(u->key[i] > oldi);
                   // if (u->key[i] <= oldi)
                     //   printf("++++++%d-%d++++++", u->key[i], oldi);
                    if (prnt) printf("%d ", oldi = u->key[i]);
                }
                if (prnt) printf("--->");
            }
            if (prnt) printf("\n");
        }
    }
}; // B+ Tree

#include "BPT_implementation.h"

