#ifndef VECTOR2_H
#define VECTOR2_H

#include <cmath>
#include <initializer_list>
#include <iostream>

#include "StaticMatrix.h"
template <class Type>
class Vector2 {
   private:
    Type x, y;

   public:
    Vector2() : x(), y() {}

    Vector2(const Type &x, const Type &y) : x(x), y(y) {}

    Vector2(const Vector2<Type> &other) : x(other.x), y(other.y) {}

    Vector2(const std::initializer_list<Type> &other)
        : x(*other.begin()), y(*++other.begin()) {}

    Vector2(const StaticMatrix<Type, 2, 1> &other)
        : x(other[0][0]), y(other[1][0]) {}

    Type X() const { return x; }

    Type Y() const { return y; }

    Vector2<Type> &setX(Type x) { x = x; }

    Vector2<Type> &setY(Type y) { y = y; }

    /// 返回两个向量的点积（内积 或 数量积）
    static Type Dot(const Vector2<Type> &v1, const Vector2<Type> &v2) {
        return v1.x * v2.x + v1.y * v2.y;
    }

    /// 返回两个向量的叉积（外积 或 向量积）在 z 轴的分量
    static Type Cross(const Vector2<Type> &v1, const Vector2<Type> &v2) {
        return v1.x * v2.y - v1.y * v2.x;
    }

    /// 返回两个向量之间的距离
    static Type Distance(const Vector2<Type> &v1, const Vector2<Type> &v2) {
        return hypot(v1.x - v2.x, v1.y - v2.y);
    }

    /// 返回两个向量之间距离的平方
    static Type DistanceSquared(const Vector2<Type> &v1,
                                const Vector2<Type> &v2) {
        return (v1.x - v2.x) * (v1.x - v2.x) + (v1.y - v2.y) * (v1.y - v2.y);
    }

    /// 返回同一方向上的单位向量
    Vector2<Type> normalized() const { return (*this) / length(); }

    Vector2<Type> operator+() const { return *this; }

    Vector2<Type> operator-() const { return Vector2(-x, -y); }

    Vector2<Type> operator-(const Vector2<Type> &b) const {
        return Vector2(x - b.x, y - b.y);
    }

    Vector2<Type> operator+(const Vector2<Type> &b) const {
        return Vector2(x + b.x, y + b.y);
    }

    Vector2<Type> operator*(Type k) const { return Vector2(k * x, k * y); }

    friend Vector2<Type> operator*(Type k, const Vector2<Type> &v) {
        return Vector2(k * v.x, k * v.y);
    }

    Vector2<Type> operator/(Type k) const { return Vector2(x / k, y / k); }

    Vector2<Type> &operator+=(const Vector2<Type> &b) {
        x += b.x;
        y += b.y;
        return *this;
    }

    Vector2<Type> &operator-=(const Vector2<Type> &b) {
        x -= b.x;
        y -= b.y;
        return *this;
    }

    Vector2<Type> &operator*=(Type b) {
        x *= b;
        y *= b;
        return *this;
    }

    Vector2<Type> &operator/=(Type b) {
        x /= b;
        y /= b;
        return *this;
    }

    /// 返回向量长度
    Type length() const { return hypot(x, y); }

    /// 返回向量长度的平方
    Type lengthSquared() const { return x * x + y * y; }

    bool operator==(const Vector2<Type> &b) const {
        return x == b.x && y == b.y;
    }

    bool operator!=(const Vector2<Type> &b) const {
        return x != b.x || y != b.y;
    }

    /// 返回逆时针旋转给定角度后的向量
    Vector2<Type> rotatedCounterclockwise(Type angle) const {
        Type c = cos(angle), s = sin(angle);
        return Vector2(x * c - y * s, x * s + y * c);
    }

    /// 返回给定极角的单位向量
    static Vector2<Type> fromAngle(Type angle) {
        return Vector2(cos(angle), sin(angle));
    }

    /// 返回向量的极角
    Type getAngle() const { return atan2(y, x); }

    /// 返回逆时针旋转 90 度后的向量
    Vector2<Type> turnedLeft() const { return Vector2(-y, x); }

    /// 返回顺时针旋转 90 度后的向量
    Vector2<Type> turnedRight() const { return Vector2(y, -x); }

    friend std::ostream &operator<<(std::ostream &cout,
                                    const Vector2<Type> &v) {
        return cout << "(" << v.x << ", " << v.y << ")";
    }
};

#endif
