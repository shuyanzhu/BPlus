#pragma once
#include "BPTNode.h"
#include "BPT.h"
template <typename T>
bool BPT<T>::rec_remove(BPTNode<T> *v, const T &e) {
	int s = (1 + _order) / 2;

	// ƽ�����, ��Ҷ�ӽڵ�
	if (v->child[0] == NULL) { // �ݹ��
		Rank r = v->key.search(e);
		if (r < 0 || v->key[r] != e)return false; // û��������Ԫ��
		v->key.remove(r);
		v->child.remove(r);
		_size--;
		if (v->key.size() < s) { // �ƶ���ϲ�
			if (v->prev && v->prev->parent == v->parent && v->prev->key.size() > s) {
				v->key.insert(0, v->prev->key.remove(v->prev->key.size() - 1)); // ����key
				v->child.insert(0, v->prev->child.remove(v->prev->child.size() - 1)); // ����child
			}
			else if (v->next && v->next->parent == v->parent && v->next->key.size() > s) {
				v->key.insert( v->next->key.remove(0)); // ����key
				v->child.insert( v->next->child.remove(0)); // ����child
			}
			else if(v->prev || v->next){ // �����ڵ��ֵ���뵽�ϸ��ڵ㣬�ȵ����ڵ�ʱɾ�����ڵ�
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
	// ��ƽ����������ڲ��ڵ�
	Rank r = v->key.search(e);
	if (r < 0)return false;
	if(rec_remove(v->child[r], e) == NULL)return false; // �ݹ�
	v->key[r] = v->child[r]->key[0]; // ���ڵ����
	if (v->child.size() > r+1 && v->child[r+1])v->key[r+1] = v->child[r + 1]->key[0]; // ����ϲ�����һ���ڵ�Ҳ��Ҫ����
	if (v->child[r]->key.size() < s) { // �ӽڵ����С��s
		delete v->child[r];
		v->key.remove(r);
		v->child.remove(r);
		if (v->key.size() < s) { // �ƶ���ϲ�
			if (v->prev && v->prev->parent == v->parent && v->prev->key.size() > s) {
				v->prev->child[v->prev->child.size() - 1]->parent = v;
				v->key.insert(0, v->prev->key.remove(v->prev->key.size() - 1)); // ����key
				v->child.insert(0, v->prev->child.remove(v->prev->child.size() - 1)); // ����child
			}
			else if (v->next && v->next->parent == v->parent && v->next->key.size() > s) {
				v->next->child[0]->parent = v;
				v->key.insert(v->next->key.remove(0)); // ����key
				v->child.insert(v->next->child.remove(0)); // ����child
			}
			else if(v->prev || v->next){ // �����ڵ��ֵ���뵽�ϸ��ڵ㣬�ȵ����ڵ�ʱɾ�����ڵ�
				if (v->prev && v->prev->parent == v->parent) {
					for (Rank r = 0; r < v->key.size(); r++) {
						v->child[r]->parent = v->prev; // �ı丸�ڵ�
						v->prev->key.insert(v->key[r]);
						v->prev->child.insert(v->child[r]);
					}
					if (v->prev)v->prev->next = v->next;
					if (v->next)v->next->prev = v->prev;
				}
				else {
					for (Rank r = 0; r < v->key.size(); r++) {
						v->child[r]->parent = v->next; // �ı丸�ڵ�
						v->next->key.insert(r, v->key[r]);
						v->next->child.insert(r, v->child[r]);
					}
					if (v->prev)v->prev->next = v->next;
					if (v->next)v->next->prev = v->prev;
				}

			}
		}
	} // �����Ҫ�Ļ���ɾ���Ѿ����ϲ����ӽڵ�

	if (v == _root && v->key.size() == 1) { // ���߽���
		_root = v->child[0];
		_root->parent = NULL;
		delete v;
		h--;
	}
	return true;
}