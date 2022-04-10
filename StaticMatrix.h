#ifndef STATICMATRIX_H
#define STATICMATRIX_H

#include <array>
#include <cmath>
#include <initializer_list>
#include <iostream>
#include <utility>

#include "Matrix.h"

template <class Type, size_t R, size_t C>
class StaticMatrix {
   private:
    std::array<std::array<Type, C>, R> data;

   public:
    std::array<Type, C> &operator[](size_t index) { return data[index]; }

    const std::array<Type, C> &operator[](size_t index) const {
        return data[index];
    }

    StaticMatrix() : data({{}}) {}

    StaticMatrix(
        const std::initializer_list<std::initializer_list<Type>> &other)
        : data({{}}) {
        for (auto [dataIter, otherIter] =
                 std::make_pair(data.begin(), other.begin());
             dataIter != data.end() && otherIter != other.end();
             ++dataIter, ++otherIter) {
            for (auto [dataIter2, otherIter2] =
                     std::make_pair(dataIter->begin(), otherIter->begin());
                 dataIter2 != dataIter->end() && otherIter2 != otherIter->end();
                 ++dataIter2, ++otherIter2) {
                *dataIter2 = *otherIter2;
            }
        }
    }

    StaticMatrix<Type, R, C> operator+(
        const StaticMatrix<Type, R, C> &other) const {
        StaticMatrix<Type, R, C> ans;
        for (size_t i = 0; i < R; i++) {
            for (size_t j = 0; j < C; j++) {
                ans[i][j] = (*this)[i][j] + other[i][j];
            }
        }
        return ans;
    }

    StaticMatrix<Type, R, C> operator-(
        const StaticMatrix<Type, R, C> &other) const {
        StaticMatrix<Type, R, C> ans;
        for (size_t i = 0; i < R; i++) {
            for (size_t j = 0; j < C; j++) {
                ans[i][j] = (*this)[i][j] - other[i][j];
            }
        }
        return ans;
    }

    template <size_t C2>
    StaticMatrix<Type, R, C2> operator*(
        const StaticMatrix<Type, C, C2> &other) const {
        StaticMatrix<Type, R, C2> ans;
        MatrixTools::Multiply((*this), other, ans, R, C, C2);
        return ans;
    }

    StaticMatrix<Type, C, R> transposed() const {
        StaticMatrix<Type, C, R> ans;
        for (size_t i = 0; i < R; i++) {
            for (size_t j = 0; j < C; j++) {
                ans[j][i] = (*this)[i][j];
            }
        }
    }

    Type det() const {
        static_assert(R == C, "R == C must satisfied");
        StaticMatrix<Type, R, R> copy = *this;
        return MatrixTools::Det<Type>(copy, R);
    }

    StaticMatrix inverse() const {
        static_assert(R == C, "R == C must satisfied");
        StaticMatrix<Type, R, R * 2> copy;
        for (size_t i = 0; i < R; i++) {
            for (size_t j = 0; j < R; j++) {
                copy[i][j] = (*this)[i][j];
                copy[i][i + R] = 1;
            }
        }
        MatrixTools::Gauss(copy, R, R * 2);
        StaticMatrix<Type, R, R> ans;
        for (size_t i = 0; i < R; i++) {
            for (size_t j = 0; j < R; j++) {
                ans[i][j] = copy[i][j + R];
            }
        }
        return ans;
    }

    bool operator==(const StaticMatrix<Type, R, C> &other) const {
        for (size_t i = 0; i < R; i++) {
            for (size_t j = 0; j < C; j++) {
                if ((*this)[i][j] != other[i][j]) {
                    return false;
                }
            }
        }
        return true;
    }

    bool operator!=(const StaticMatrix<Type, R, C> &other) const {
        return !((*this) == other);
    }

    friend std::ostream &operator<<(std::ostream &cout,
                                    const StaticMatrix<Type, R, C> &m) {
        cout << "StaticMatrix:" << std::endl;
        bool sflag = false;
        for (auto &a : m.data) {
            bool flag = false;
            if (sflag) {
                cout << std::endl;
            } else {
                sflag = true;
            }
            cout << "  | ";
            for (auto &i : a) {
                if (flag) {
                    cout << ", ";
                } else {
                    flag = true;
                }
                cout << i;
            }
            cout << " |";
        }
        return cout;
    }
};

#endif
