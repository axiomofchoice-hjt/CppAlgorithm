#ifndef AXIOMOFCHOICE_VEC_H
#define AXIOMOFCHOICE_VEC_H

#include <stdlib.h>
#include <string.h>

#include <iostream>
using std::cout;
using std::endl;

template <class Type, bool debug = 1>
class Vec {
   private:
    Type *_pointer;
    size_t _size, _capacity;
    void _recapacity(size_t _new_capacity) {
        Type *_new_pointer = (Type *)new char[_new_capacity * sizeof(Type)];
        // cout << "new: " << _new_pointer << endl;
        // cout << _new_capacity * sizeof(Type) << " " << _pointer << " " << x
        //      << endl;

        for (size_t i = 0; i < _size; i++) {
            _new_pointer[i] = std::move(_pointer[i]);
        }
        if (_pointer != nullptr) {
            // cout << "delete: " << _pointer << endl;
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
            // cout << "delete: " << _pointer << endl;
            delete[](char *) _pointer;
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
    Vec<Type> clone() {
        Vec<Type> new_vec;
        new_vec._recapacity(_size);
        for (size_t i = 0; i < _size; i++) {
            new_vec[i] = _pointer[i].clone();
        }
        new_vec._size = _size;
        return std::move(new_vec);
    }

    virtual ~Vec() {
        // cout << "deconstruct" << endl;
        if (_pointer != nullptr) {
            for (size_t i = 0; i < _size; i++) _pointer[i].~Type();
            // cout << "delete: " << _pointer << endl;
            delete[](char *) _pointer;
        }
    }

    // void push_back(const Type &_value) {
    //     if (_size == _capacity) {
    //         if (_capacity == 0) {
    //             _recapacity(1);
    //         } else {
    //             _recapacity(_capacity * 2);
    //         }
    //     }
    //     new (_pointer + _size) Type(_value);
    //     _size++;
    // }
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
        // cout << (void *)v._pointer << "/" << v._size << "/" << v._capacity;
        cout << "[";
        for (size_t i = 0; i < v._size; i++) {
            cout << v._pointer[i];
            if (i != v._size - 1) cout << ", ";
        }
        cout << "]";
        return cout;
    }
};

#endif