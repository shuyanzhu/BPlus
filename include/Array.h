#pragma once
typedef int Rank; //÷»
#include <assert.h>
#define DEFAULT_CAPACITY 2
template <typename T>
class Array {
private:
	int _capacity;
	int _size;
	T *_elem;
public:
	Array(int capacity = DEFAULT_CAPACITY) :_capacity(capacity), _size(0), _elem(NULL) {
		_elem = new T[_capacity]; for (int i = 0; i < _capacity; _elem[i++] = 0);
	}
	~Array() { delete[] _elem; }
	Rank size() { return _size; };
	bool empty() { return _size == 0; }
	Rank capacity() { return _capacity; }
	Rank insert(Rank r, const T &e) {
	//	if (r < 0 || r > _size || _capacity == _size)return -1;
		for (Rank i = _size; i != r;i--)_elem[i] = _elem[i-1];
		_elem[r] = e;
		_size++;
		return r;
	}
	Rank insert(const T &e){ return insert(_size, e); }
	T remove(Rank r) {
	//	if (r < 0)return (T);
		T e = _elem[r];
		for (int i = r; i < _size - 1; i++)_elem[i] = _elem[i + 1];
		_size--;
	//	return _elem[r];
		return e;
	}
	Rank search(const T &e) {
		int lo = 0, hi = _size;
		while (lo < hi) {
			Rank mi = (hi + lo) >> 1;
			_elem[mi] <= e ? lo = mi + 1 : hi = mi;
		}
		return --lo;
	}
	T &operator[](Rank r) { return _elem[r]; }
	void print() {
		for (int i = 0; i < _size; i++)
			std::cout << _elem[i] << "-->";
		std::cout << std::endl;
	}

};