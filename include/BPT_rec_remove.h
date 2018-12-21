#pragma once
#include "BPTNode.h"
#include "BPT.h"
template <typename T>
bool BPT<T>::rec_remove(BPTNode<T> *v, const T &e) {
	int s = (1 + _order) / 2;

	// 平凡情况, 对叶子节点
	if (v->child[0] == NULL) { // 递归基
		Rank r = v->key.search(e);
		if (r < 0 || v->key[r] != e)return false; // 没有这样的元素
		v->key.remove(r);
		v->child.remove(r);
		_size--;
		if (v->key.size() < s) { // 移动或合并
			if (v->prev && v->prev->parent == v->parent && v->prev->key.size() > s) {
				v->key.insert(0, v->prev->key.remove(v->prev->key.size() - 1)); // 传递key
				v->child.insert(0, v->prev->child.remove(v->prev->child.size() - 1)); // 传递child
			}
			else if (v->next && v->next->parent == v->parent && v->next->key.size() > s) {
				v->key.insert( v->next->key.remove(0)); // 传递key
				v->child.insert( v->next->child.remove(0)); // 传递child
			}
			else if(v->prev || v->next){ // 将本节点的值并入到上个节点，等到父节点时删除本节点
				if (v->prev && v->prev->parent == v->parent) {
					for (Rank r = 0; r < v->key.size(); r++) {
						v->prev->key.insert(v->key[r]);
						v->prev->child.insert(v->child[r]);
					}
					v->prev->next = v->next;
					if(v->next)v->next->prev = v->prev;
				}
				else {
					for (Rank r = 0; r < v->key.size(); r++) {
						v->next->key.insert(r, v->key[r]);
						v->next->child.insert(r, v->child[r]);
					}
					if (v->prev)v->prev->next = v->next;
					v->next->prev = v->prev;
				}
			}
		}
		return true;
	}
	// 非平凡情况，对内部节点
	Rank r = v->key.search(e);
	if (r < 0)return false;
	if(rec_remove(v->child[r], e) == NULL)return false; // 递归
	v->key[r] = v->child[r]->key[0]; // 本节点更新
	if (v->child.size() > r+1 && v->child[r+1])v->key[r+1] = v->child[r + 1]->key[0]; // 如果合并，下一个节点也需要更新
	if (v->child[r]->key.size() < s) { // 子节点的秩小于s
		delete v->child[r];
		v->key.remove(r);
		v->child.remove(r);
		if (v->key.size() < s) { // 移动或合并
			if (v->prev && v->prev->parent == v->parent && v->prev->key.size() > s) {
				v->prev->child[v->prev->child.size() - 1]->parent = v;
				v->key.insert(0, v->prev->key.remove(v->prev->key.size() - 1)); // 传递key
				v->child.insert(0, v->prev->child.remove(v->prev->child.size() - 1)); // 传递child
			}
			else if (v->next && v->next->parent == v->parent && v->next->key.size() > s) {
				v->next->child[0]->parent = v;
				v->key.insert(v->next->key.remove(0)); // 传递key
				v->child.insert(v->next->child.remove(0)); // 传递child
			}
			else if(v->prev || v->next){ // 将本节点的值并入到上个节点，等到父节点时删除本节点
				if (v->prev && v->prev->parent == v->parent) {
					for (Rank r = 0; r < v->key.size(); r++) {
						v->child[r]->parent = v->prev; // 改变父节点
						v->prev->key.insert(v->key[r]);
						v->prev->child.insert(v->child[r]);
					}
					if (v->prev)v->prev->next = v->next;
					if (v->next)v->next->prev = v->prev;
				}
				else {
					for (Rank r = 0; r < v->key.size(); r++) {
						v->child[r]->parent = v->next; // 改变父节点
						v->next->key.insert(r, v->key[r]);
						v->next->child.insert(r, v->child[r]);
					}
					if (v->prev)v->prev->next = v->next;
					if (v->next)v->next->prev = v->prev;
				}

			}
		}
	} // 如果需要的话，删除已经被合并的子节点

	if (v == _root && v->key.size() == 1) { // 树高降低
		_root = v->child[0];
		_root->parent = NULL;
		delete v;
		h--;
	}
	return true;
}