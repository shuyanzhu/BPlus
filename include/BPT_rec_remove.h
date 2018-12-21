#pragma once
#include "BPTNode.h"
#include "BPT.h"
template <typename T>
bool BPT<T>::rec_remove(BPTNode<T> *v, const T &e) {
	int s = (1 + _order) / 2;
	// 递归基
	if (v->child[0] == NULL) { // 递归基
		Rank r = v->key.search(e);
		if (r < 0)return false; // 没有这样的元素
		v->key.remove(r);
		v->child.remove(r);
		if (v->key.size() < s) { // 移动或合并
			if (v->prev && v->prev->key.size() > s) {
				v->key.insert(0, v->prev->key.remove(v->prev->key.size() - 1)); // 传递key
				v->child.insert(0, v->prev->child.remove(v->prev->child.size() - 1)); // 传递child
			}
			else if (v->next && v->next->key.size() > s) {
				v->key.insert(0, v->next->key.remove(v->next->key.size() - 1)); // 传递key
				v->child.insert(0, v->next->child.remove(v->next->child.size() - 1)); // 传递child
			}
			else if(v->prev || v->next){ // 将本节点的值并入到上个节点，等到父节点时删除本节点
				if (v->prev) {
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
					v->next->prev = v->prev;
				}
			}
		}
		return true;
	}
	// 递归
	Rank r = v->key.search(e);
	if (r < 0)return false;
	bool ret = rec_remove(v->child[r], e); // 递归删除
	if (!ret)return false;
	if (v->child.size() > r+1&& v->child[r+1] && v->child[r]->key[0] == v->child[r + 1]->key[0])v->key[r+1] = v->child[r + 1]->key[0];
	if (v->child[r]->key.size() < s) { // 子节点的秩小于s
		delete v->child[r];
		v->key.remove(r);
		v->child.remove(r);
		if (v->key.size() < s) { // 移动或合并
			if (v->prev && v->prev->key.size() > s) {
				v->key.insert(0, v->prev->key.remove(v->prev->key.size() - 1)); // 传递key
				v->child.insert(0, v->prev->child.remove(v->prev->child.size() - 1)); // 传递child
			}
			else if (v->next && v->next->key.size() > s) {
				v->key.insert(0, v->next->key.remove(v->next->key.size() - 1)); // 传递key
				v->child.insert(0, v->next->child.remove(v->next->child.size() - 1)); // 传递child
			}
			else if(v->prev || v->next){ // 将本节点的值并入到上个节点，等到父节点时删除本节点
				if (v->prev) {
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
	}
	if (v == _root && v->key.size() == 1) { // 树高降低
		_root = v->child[0];
		_root->parent = NULL;
		delete v;
	}
	return true;
}