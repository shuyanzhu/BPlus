#pragma once
#include "BPTNode.h"
#include "BPT.h"
template <typename T>
bool BPT<T>::rec_remove(BPTNode<T> *v, const T &e) {
	int s = (1 + _order) / 2;
	// 平凡情况, 对叶子节点/光杆的根节点
	if (v->child[0] == NULL) { // 递归基
		Rank r = v->key.search(e);
		if (r < 0 || v->key[r] != e)return false; // 没有这样的元素
		v->key.remove(r);
		v->child.remove(r);
		_size--;
		return true;
	}
	// 非平凡情况，对内部节点
	Rank r = v->key.search(e);
	if (r < 0)return false;
	if(rec_remove(v->child[r], e) == NULL)return false; // 递归删除子节点
	BPTNode<T> *u = v->child[r]; // 获得子节点
	if (u->key.size() < s) { // 移动或合并
			if (u->prev && u->prev->parent == u->parent && u->prev->key.size() > s) {
				if(u->child[0]) // v非第二层节点
					u->prev->child[u->prev->child.size() - 1]->parent = v;
				u->key.insert(0, u->prev->key.remove(u->prev->key.size() - 1)); // 传递key
				u->child.insert(0, u->prev->child.remove(u->prev->child.size() - 1)); // 传递child
			}
			else if (u->next && u->next->parent == u->parent && u->next->key.size() > s) {
				if (u->child[0]) // v非第二层节点
					u->next->child[0]->parent = v;
				u->key.insert(u->next->key.remove(0)); // 传递key
				u->child.insert(u->next->child.remove(0)); // 传递child
			}
			else if(u->prev || u->next){ // 将本节点的值并入到上个节点，等到父节点时删除本节点
				if (u->prev && u->prev->parent == u->parent) {
					for (Rank r = 0; r < u->key.size(); r++) {
						if (u->child[0]) // v非第二层节点
							u->child[r]->parent = u->prev; // 改变父节点
						u->prev->key.insert(u->key[r]);
						u->prev->child.insert(u->child[r]);
					}
					if (u->prev)u->prev->next = u->next;
					if (u->next)u->next->prev = u->prev;
				}
				else {
					for (Rank r = 0; r < u->key.size(); r++) {
						if (u->child[0]) // v非第二层节点
							u->child[r]->parent = u->next; // 改变父节点
						u->next->key.insert(r, u->key[r]);
						u->next->child.insert(r, u->child[r]);
					}
					if (u->prev)u->prev->next = u->next;
					if (u->next)u->next->prev = u->prev;
					u->parent == NULL; // 子节点被合并的指示
				}

			}
		}
	// 如果需要的话，删除已经被合并的子节点
	v->key[r] = v->child[r]->key[0]; // 本节点更新
	if (v->child.size() > r + 1 && v->child[r + 1])v->key[r + 1] = v->child[r + 1]->key[0]; // 如果合并，下一个节点也需要更新
	if (u->parent == NULL) { // 子节点已经被合并
		delete u;
		_node_num--;
		v->key.remove(r);
		v->child.remove(r);
	}
	if (v == _root && v->key.size() == 1 && v->child[0]) { // 树高降低
		_root = v->child[0];
		_root->parent = NULL;
		delete v;
		_node_num--;
		h--;
	}
	return true;
}