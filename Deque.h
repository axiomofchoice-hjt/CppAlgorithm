#ifndef DEQUE_H
#define DEQUE_H

#include <algorithm>
#include <iostream>
#include <optional>

#include "Iter.h"

template <class Type>
class Deque {
   private:
    Type *_pointer;
    size_t _begin, _size, _capacity;

    size_t getIndex(size_t i) const {
        return _begin + i < _capacity ? _begin + i : _begin + i - _capacity;
    }

    void _recapacity(size_t _new_capacity) {
        Type *_new_pointer =
            reinterpret_cast<Type *>(new char[_new_capacity * sizeof(Type)]);

        for (size_t i = 0; i < _size; i++) {
            _new_pointer[i] = std::move(_pointer[getIndex(i)]);
        }
        if (_pointer != nullptr) {
            delete[] reinterpret_cast<char *>(_pointer);
        }
        _pointer = _new_pointer;
        _capacity = _new_capacity;
        _begin = 0;
    }

    Deque(Type *_pointer, size_t _begin, size_t _size, size_t _capacity)
        : _pointer(_pointer),
          _begin(_begin),
          _size(_size),
          _capacity(_capacity) {}

    void deconstruct() {
        if (_pointer != nullptr) {
            for (size_t i = 0; i < _size; i++) {
                _pointer[getIndex(i)].~Type();
            }
            delete[] reinterpret_cast<char *>(_pointer);
        }
    }

    void moved() {
        _pointer = nullptr;
        _begin = _size = _capacity = 0;
    }

   public:
    using type_value = Type;

    Deque() : _pointer(nullptr), _begin(0), _size(0), _capacity(0) {}

    Deque(Deque<Type> &&_other)
        : _pointer(_other._pointer),
          _begin(_other._begin),
          _size(_other._size),
          _capacity(_other._capacity) {
        _other.moved();
    }

    Deque<Type> &operator=(Deque<Type> &&_other) {
        deconstruct();
        _pointer = _other._pointer;
        _begin = _other._begin;
        _size = _other._size;
        _capacity = _other._capacity;
        _other.moved();
        return *this;
    }

    Deque<Type> clone() const {
        Deque<Type> new_Deque;
        new_Deque._recapacity(_size);
        for (size_t i = 0; i < _size; i++) {
            new_Deque[i] = _pointer[getIndex(i)].clone();
        }
        new_Deque._size = _size;
        return std::move(new_Deque);
    }

    virtual ~Deque() { deconstruct(); }

    template <class T>
    void push_back(T &&_value) {
        if (_size == _capacity) {
            _recapacity(std::max(_capacity * 2, static_cast<size_t>(1)));
        }
        new (_pointer + getIndex(_size)) Type(std::forward<Type>(_value));
        _size++;
    }

    void pop_back() {
        _size--;
        _pointer[getIndex(_size)].~Type();
    }

    template <class T>
    void push_front(T &&_value) {
        if (_size == _capacity) {
            _recapacity(std::max(_capacity * 2, static_cast<size_t>(1)));
        }
        _begin = getIndex(_capacity - 1);
        new (_pointer + _begin) Type(std::forward<Type>(_value));
        _size++;
    }

    void pop_front() {
        _size--;
        _pointer[_begin].~Type();
        _begin = getIndex(1);
    }

    size_t size() const { return _size; }

    Type &operator[](size_t _index) { return _pointer[getIndex(_index)]; }

    const Type &operator[](size_t _index) const {
        return _pointer[getIndex(_index)];
    }

    friend std::ostream &operator<<(std::ostream &cout, const Deque<Type> &v) {
        cout << "[";
        for (size_t i = 0; i < v._size; i++) {
            cout << v._pointer[v.getIndex(i)];
            if (i != v._size - 1) cout << ", ";
        }
        cout << "]";
        return cout;
    }

    void resize(size_t _new_size, const Type &_value) {
        if (_capacity < _new_size) {
            _recapacity(std::max(_capacity * 2, _new_size));
        }

        for (size_t i = _size; i < _new_size; i++) {
            new (_pointer + getIndex(i)) Type(_value.clone());
        }
        _size = _new_size;
    }

    void assign(size_t _new_size, const Type &_value) {
        if (_capacity < _new_size) {
            _recapacity(std::max(_capacity * 2, _new_size));
        }

        for (size_t i = 0; i < _size; i++) {
            _pointer[getIndex(i)].~Type();
        }
        for (size_t i = 0; i < _new_size; i++) {
            new (_pointer + i) Type(_value.clone());
        }
        _begin = 0;
        _size = _new_size;
    }

    void clear() {
        for (size_t i = 0; i < _size; i++) {
            _pointer[getIndex(i)].~Type();
        }
        _begin = 0;
        _size = 0;
    }

    ConcatIter<RangeIter<Type *>, RangeIter<Type *>> iter_mut() {
        if (_begin + _size < _capacity) {
            return ConcatIter(
                RangeIter(_pointer + _begin, _pointer + _begin + _size),
                RangeIter(_pointer, _pointer));
        } else {
            return ConcatIter(
                RangeIter(_pointer + _begin, _pointer + _capacity),
                RangeIter(_pointer, _pointer + _begin + _size - _capacity));
        }
    }

    ConcatIter<RangeIter<const Type *>, RangeIter<const Type *>> iter() const {
        if (_begin + _size < _capacity) {
            return ConcatIter(RangeIter<const Type *>(
                                  _pointer + _begin, _pointer + _begin + _size),
                              RangeIter<const Type *>(_pointer, _pointer));
        } else {
            return ConcatIter(
                RangeIter<const Type *>(_pointer + _begin,
                                        _pointer + _capacity),
                RangeIter<const Type *>(_pointer,
                                        _pointer + _begin + _size - _capacity));
        }
    }
};

#endif
