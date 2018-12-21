#pragma once
#include "BPTNode.h"
#include "BPT.h"
template <typename T>
bool BPT<T>::rec_remove(BPTNode<T> *v, const T &e) {
	int s = (1 + _order) / 2;
	// �ݹ��
	if (v->child[0] == NULL) { // �ݹ��
		Rank r = v->key.search(e);
		if (r < 0)return false; // û��������Ԫ��
		v->key.remove(r);
		v->child.remove(r);
		if (v->key.size() < s) { // �ƶ���ϲ�
			if (v->prev && v->prev->key.size() > s) {
				v->key.insert(0, v->prev->key.remove(v->prev->key.size() - 1)); // ����key
				v->child.insert(0, v->prev->child.remove(v->prev->child.size() - 1)); // ����child
			}
			else if (v->next && v->next->key.size() > s) {
				v->key.insert(0, v->next->key.remove(v->next->key.size() - 1)); // ����key
				v->child.insert(0, v->next->child.remove(v->next->child.size() - 1)); // ����child
			}
			else if(v->prev || v->next){ // �����ڵ��ֵ���뵽�ϸ��ڵ㣬�ȵ����ڵ�ʱɾ�����ڵ�
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
	// �ݹ�
	Rank r = v->key.search(e);
	if (r < 0)return false;
	bool ret = rec_remove(v->child[r], e); // �ݹ�ɾ��
	if (!ret)return false;
	if (v->child.size() > r+1&& v->child[r+1] && v->child[r]->key[0] == v->child[r + 1]->key[0])v->key[r+1] = v->child[r + 1]->key[0];
	if (v->child[r]->key.size() < s) { // �ӽڵ����С��s
		delete v->child[r];
		v->key.remove(r);
		v->child.remove(r);
		if (v->key.size() < s) { // �ƶ���ϲ�
			if (v->prev && v->prev->key.size() > s) {
				v->key.insert(0, v->prev->key.remove(v->prev->key.size() - 1)); // ����key
				v->child.insert(0, v->prev->child.remove(v->prev->child.size() - 1)); // ����child
			}
			else if (v->next && v->next->key.size() > s) {
				v->key.insert(0, v->next->key.remove(v->next->key.size() - 1)); // ����key
				v->child.insert(0, v->next->child.remove(v->next->child.size() - 1)); // ����child
			}
			else if(v->prev || v->next){ // �����ڵ��ֵ���뵽�ϸ��ڵ㣬�ȵ����ڵ�ʱɾ�����ڵ�
				if (v->prev) {
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
	}
	if (v == _root && v->key.size() == 1) { // ���߽���
		_root = v->child[0];
		_root->parent = NULL;
		delete v;
	}
	return true;
}