#pragma once
#include "BPTNode.h"
#include "Array.h"
#include <assert.h>
#include <stdio.h>

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
    bool rec_insert(BPTNode<T> *v, const T &e);
    void release(BPTNode<T> *&p)
    {
        if (p == NULL) return;
        for (BPTNode<T> *v = p; p != NULL;) {
            BPTNode<T> *next = p->next;
            delete p;
            p = next;
        }
    }

  public:
    int h; // 树高
    BPT(int order = 3)
        : _node_num(1)
        , h(1)
        , _order(order)
        , _size(0)
    {
        // _root = new BPTNode<T>();
        _root = new BPTNode<T>(_order);
    }
    ~BPT()
    {
        if (_root) release(_root);
    }
    // 阶次、大小、根节点、判空
    const int order() { return _order; }
    const int size() { return _size; }
    BPTNode<T> *root() { return _root; }
    bool empty() const { return !_size; }
    // 增删查
    BPTNode<T> *search(const T &e);
    bool insert(const T &e);
    // bool insert(const T &e) { return rec_insert(_root, e); }
    bool remove(const T &e) { return rec_remove(_root, e); }

    struct Meta
    {
        int BPnode_num;
        int BPsize;  // 规模
        int BPorder; // 阶数
        int BPh;
    };
    int serialize(const char *path)
    {
        FILE *fp = fopen(path, "wb+");
        Meta meta{_node_num, _size, _order, h};
        Array<int> layerseek(h);
        int i = 0, seek = sizeof(Meta) + layerseek.seek();
        fseek(fp, seek, SEEK_SET);
        for (BPTNode<T> *layer = _root; layer != NULL;
             layer = layer->child[0]) {
            assert(i < h);
            int num = 0;
            for (BPTNode<T> *v = layer; v != NULL; v = v->next) {
                seek += v->key.serialize(fp);
                num++;
            }
            layerseek.insert(num);
        }
        fseek(fp, 0, SEEK_SET);
        fwrite(&meta, sizeof(Meta), 1, fp);
        layerseek.serialize(fp);
        fclose(fp);
        return seek;
    }
    int deserialize(const char *path)
    {
        release(_root);
        FILE *fp = fopen(path, "rb");
        Meta meta;
        fread(&meta, sizeof(Meta), 1, fp);
        _node_num = meta.BPnode_num;
        _size = meta.BPsize;
        _order = meta.BPorder;
        h = meta.BPh;
        Array<T> layernum(h);
        layernum.deserialize(fp);
        Array<BPTNode<T> *> layerp(h);
        for (int i = 0; i < h; i++) {
            BPTNode<T> *prev = new BPTNode<T>(_order);
            layerp.insert(prev);
            prev->key.deserialize(fp);
            for (int k = 0; k < prev->key.size(); k++)
                prev->child.insert(NULL);
            for (int j = 0; j < layernum[i] - 1; j++) {
                BPTNode<T> *next = new BPTNode<T>(_order);
                next->key.deserialize(fp);
                for (int k = 0; k < next->key.size(); k++)
                    next->child.insert(NULL);
                next->prev = prev;
                prev->next = next;
                prev = next;
            }
        }
        _root = layerp[0];
        for (int i = 0; i < h - 1; i++) {
            BPTNode<T> *cur = layerp[i + 1];
            for (BPTNode<T> *p = layerp[i]; p != NULL; p = p->next) {
                for (int j = 0; j < p->key.size(); j++) {
                    p->child[j] = cur;
                    cur->parent = p;
                    cur = cur->next;
                }
            }
        }
        int seek = ftell(fp);
        fclose(fp);
        return seek;
    }

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
                    int iii = u->key[i];
                    assert(u->key[i] > oldi);
                    if (prnt) printf("%d ", oldi = u->key[i]);
                }
                if (prnt) printf("--->");
            }
            if (prnt) printf("\n");
        }
    }
}; // B+ Tree

#include "BPT_implementation.h"

