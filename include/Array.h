#pragma once
typedef int Rank; //秩
#include <assert.h>
#include <string.h>
#define DEFAULT_CAPACITY 2
template <typename T>
class Array
{
  private:
    int _capacity;
    int _size;
    T *_elem;

  public:
    Array(int capacity = DEFAULT_CAPACITY)
        : _capacity(capacity)
        , _size(0)
        , _elem(NULL)
    {
        _elem = new T[_capacity];
        memset(_elem, 0, sizeof(T) * _capacity);
    }
    ~Array() { delete[] _elem; }
    Rank capacity() { return _capacity; }
    Rank size() { return _size; };
    bool empty() { return _size == 0; }

    Rank split(Array<T> &to, Rank r)
    {
        memcpy(to._elem, &_elem[r], sizeof(T) * (_size - r));
        to._size = _size - r;
        _size = r;
        return to._size;
    }

    Rank insert(Rank r, const T &e)
    {
        assert(r >= 0 && r <= _size && _size < _capacity);
        // for (Rank i = _size; i != r; i--)
        //    _elem[i] = _elem[i - 1];
        memmove(_elem + r + 1, _elem + r, sizeof(T) * (_size - r));
        _elem[r] = e;
        _size++;
        return r;
    }
    Rank insert(const T &e) { return insert(_size, e); } //默认作为末元素插入
    T remove(Rank r)
    {
        T e = _elem[r];
        remove(r, r + 1);
        return e;
    }
    Rank remove(Rank lo, Rank hi)
    {
        assert(0 <= lo && lo <= hi && hi <= _size);
        memmove(_elem + lo, _elem + hi, sizeof(T) * (_size - hi));
        _size = _size - (hi - lo);
        return hi - lo;
    }
    Rank search(const T &e) const
    {
        int lo = 0, hi = _size;
        while (lo < hi) {
            Rank mi = (hi + lo) >> 1;
            _elem[mi] <= e ? lo = mi + 1 : hi = mi;
        }
        return --lo;
    }
    T &operator[](Rank r)
    {
        if (r >= _size) _size = r + 1;
        assert(r < _capacity);
        return _elem[r];
    }
    void print()
    {
        for (int i = 0; i < _size; i++)
            std::cout << _elem[i] << "-->";
        std::cout << std::endl;
    }
    Rank seek() { return sizeof(_size) + sizeof(T) * _capacity; }

    int serialize(FILE *fp)
    {
        fwrite(&_size, sizeof(_size), 1, fp);
        fwrite(_elem, sizeof(T), _capacity, fp);
        return sizeof(_size) + sizeof(T) * _capacity;
    }
    int deserialize(FILE *fp)
    {
        fread(&_size, sizeof(_size), 1, fp);
        fread(_elem, sizeof(T), _capacity, fp);
        return sizeof(_size) + sizeof(T) * _capacity;
    }
};
