#ifndef VEC_H
#define VEC_H

#include <algorithm>
#include <iostream>
#include <optional>

#include "Iter.h"

using std::cout;
using std::endl;

template <class Type>
class Vec {
   private:
    Type *_pointer;
    size_t _size, _capacity;

    void _recapacity(size_t _new_capacity) {
        Type *_new_pointer =
            reinterpret_cast<Type *>(new char[_new_capacity * sizeof(Type)]);

        for (size_t i = 0; i < _size; i++) {
            _new_pointer[i] = std::move(_pointer[i]);
        }
        if (_pointer != nullptr) {
            delete[] reinterpret_cast<char *>(_pointer);
        }

        _pointer = _new_pointer;
        _capacity = _new_capacity;
    }

    Vec(Type *_pointer, size_t _size, size_t _capacity)
        : _pointer(_pointer), _size(_size), _capacity(_capacity) {}

    void deconstruct() {
        if (_pointer != nullptr) {
            for (size_t i = 0; i < _size; i++) {
                _pointer[i].~Type();
            }
            delete[] reinterpret_cast<char *>(_pointer);
        }
    }

    void moved() {
        _pointer = nullptr;
        _size = _capacity = 0;
    }

   public:
    using type_value = Type;

    Vec() : _pointer(nullptr), _size(0), _capacity(0) {}

    Vec(Vec<Type> &&_other)
        : _pointer(_other._pointer),
          _size(_other._size),
          _capacity(_other._capacity) {
        _other.moved();
    }

    Vec<Type> &operator=(Vec<Type> &&_other) {
        deconstruct();
        _pointer = _other._pointer;
        _size = _other._size;
        _capacity = _other._capacity;
        _other.moved();
        return *this;
    }

    Vec<Type> clone() const {
        Vec<Type> new_vec;
        new_vec._recapacity(_size);
        for (size_t i = 0; i < _size; i++) {
            new_vec[i] = _pointer[i].clone();
        }
        new_vec._size = _size;
        return std::move(new_vec);
    }

    virtual ~Vec() { deconstruct(); }

    template <class T>
    void push_back(T &&_value) {
        if (_size == _capacity) {
            _recapacity(std::max(_capacity * 2, static_cast<size_t>(1)));
        }
        new (_pointer + _size) Type(std::forward<Type>(_value));
        _size++;
    }

    void pop_back() {
        _size--;
        _pointer[size].~Type();
    }

    size_t size() const { return _size; }

    Type &operator[](size_t _index) { return _pointer[_index]; }

    const Type &operator[](size_t _index) const { return _pointer[_index]; }

    friend std::ostream &operator<<(std::ostream &cout, const Vec<Type> &v) {
        cout << "[";
        for (size_t i = 0; i < v._size; i++) {
            cout << v._pointer[i];
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
            new (_pointer + i) Type(_value.clone());
        }
        _size = _new_size;
    }

    void assign(size_t _new_size, const Type &_value) {
        if (_capacity < _new_size) {
            _recapacity(std::max(_capacity * 2, _new_size));
        }

        for (size_t i = 0; i < _size; i++) {
            _pointer[i].~Type();
        }
        for (size_t i = 0; i < _new_size; i++) {
            new (_pointer + i) Type(_value.clone());
        }
        _size = _new_size;
    }

    void clear() {
        for (size_t i = 0; i < _size; i++) {
            _pointer[i].~Type();
        }
        _size = 0;
    }

    RangeIter<Type *> iter_mut() {
        return RangeIter(_pointer, _pointer + _size);
    }

    RangeIter<const Type *> iter() const {
        return RangeIter<const Type *>(_pointer, _pointer + _size);
    }
};

#endif
