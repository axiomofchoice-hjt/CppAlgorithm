#ifndef AXIOMOFCHOICE_VEC_H
#define AXIOMOFCHOICE_VEC_H

#include <stdlib.h>
#include <string.h>

#include <iostream>

using std::cout;
using std::endl;

template <class Type>
class Vec {
   private:
    Type *_pointer;
    size_t _size, _capacity;

    void _recapacity(size_t _new_capacity) {
        Type *_new_pointer = static_cast<Type *>(new char[_new_capacity * sizeof(Type)]);

        for (size_t i = 0; i < _size; i++) {
            _new_pointer[i] = std::move(_pointer[i]);
        }
        if (_pointer != nullptr) {
            delete[](char *) _pointer;
        }

        _pointer = _new_pointer;
        _capacity = _new_capacity;
    }

    Vec(Type *_pointer, size_t _size, size_t _capacity)
        : _pointer(_pointer), _size(_size), _capacity(_capacity) {}

    void deconstruct() {
        if (_pointer != nullptr) {
            for (size_t i = 0; i < _size; i++) _pointer[i].~Type();
            delete[](char *) _pointer;
        }
    }

    void moved() {
        _pointer = nullptr;
        _size = _capacity = 0;
    }

   public:
    const char *name;
    using type_value = Type;

    Vec() : _pointer(nullptr), _size(0), _capacity(0) {}

    Vec(Vec<Type> &&_other)
        : _pointer(_other._pointer),
          _size(_other._size),
          _capacity(_other._capacity) {
        _other.moved();
    }

    Vec(Vec<Type> &_other)
        : _pointer(_other._pointer),
          _size(_other._size),
          _capacity(_other._capacity) {
        _other.moved();
    }

    Vec<Type> &operator=(Vec<Type> &&_other) {
        _pointer = _other._pointer;
        _size = _other._size;
        _capacity = _other._capacity;
        _other.moved();
        return *this;
    }

    Vec<Type> &operator=(Vec<Type> &_other) {
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

    virtual ~Vec() {
        if (_pointer != nullptr) {
            for (size_t i = 0; i < _size; i++) _pointer[i].~Type();
            delete[](char *) _pointer;
        }
    }

    template <class T>
    void push_back(T &&_value) {
        if (_size == _capacity) {
            if (_capacity == 0) {
                _recapacity(1);
            } else {
                _recapacity(_capacity * 2);
            }
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
        if (_capacity * 2 < _new_size) {
            _recapacity(_new_size);
        } else if (_capacity < _new_size) {
            _recapacity(_capacity * 2);
        }

        for (size_t i = _size; i < _new_size; i++) {
            new (_pointer + i) Type(_value.clone());
        }
        _size = _new_size;
    }

    void assign(size_t _new_size, const Type &_value) {
        if (_capacity * 2 < _new_size) {
            _recapacity(_new_size);
        } else if (_capacity < _new_size) {
            _recapacity(_capacity * 2);
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
};

#endif
