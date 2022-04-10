#ifndef MATRIX_H
#define MATRIX_H

#include <algorithm>

namespace MatrixTools {

/// 将 n * p 矩阵 a 与 p * m 矩阵 b 相乘，保存至矩阵 c
template <class A, class B, class C>
void Multiply(const A &a, const B &b, C &c, size_t n, size_t p, size_t m) {
    for (size_t i = 0; i < n; i++) {
        for (size_t k = 0; k < p; k++) {
            auto temp = a[i][k];
            for (size_t j = 0; j < m; j++) {
                c[i][j] += temp * b[k][j];
            }
        }
    }
}

/// 破坏性地计算行列式
template <class Type, class A>
Type Det(A &a, size_t n) {
    Type det = 1;
    for (size_t i = 0; i < n; i++) {
        size_t t = n;
        for (size_t j = i; j < n; j++) {
            if (a[j][i] != 0) {
                t = j;
                break;
            }
        }
        if (t == n) {
            det = 0;
            return 0;
        }
        if (t != i) {
            for (size_t j = i; j < n; j++) {
                std::swap(a[i][j], a[t][j]);
            }
            det = -det;
        }
        det *= a[i][i];
        Type r = 1 / a[i][i];
        for (size_t j = i; j < n; j++) {
            a[i][j] *= r;
        }
        for (size_t j = i + 1; j < n; j++) {
            if (a[j][i] != 0) {
                Type c = -a[j][i];
                for (size_t k = i; k < n; k++) {
                    a[j][k] += a[i][k] * c;
                }
            }
        }
    }
    return det;
}

/// 高斯消元，原地保存
template <class A>
void Gauss(A &a, size_t n, size_t m) {
    using Type = decltype(a[0][0] + 0);

    for (size_t i = 0; i < n; i++) {
        size_t t = n;
        for (size_t j = i; j < n; j++) {
            if (a[j][i] != 0) {
                t = j;
                break;
            }
        }
        if (t == n) {
            return;
        }
        if (t != i) {
            for (size_t j = i; j < m; j++) {
                std::swap(a[i][j], a[t][j]);
            }
        }
        Type r = 1 / a[i][i];
        for (size_t j = i; j < m; j++) {
            a[i][j] *= r;
        }
        for (size_t j = 0; j < n; j++) {
            if (j != i && a[j][i] != 0) {
                Type c = -a[j][i];
                for (size_t k = i; k < m; k++) {
                    a[j][k] += a[i][k] * c;
                }
            }
        }
    }
}

}  // namespace MatrixTools

#endif
