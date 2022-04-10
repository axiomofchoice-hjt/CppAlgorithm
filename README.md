# CppAlgorithm

（还在完善中）

随手写的 C++ STL 以及一些算法的汇总。

## 对 Rust 拙劣的模仿

### BaseInterface, BaseType

对基本类型（整数、浮点数）的封装。

模仿 Rust，为基本类型实现了 Clone、Display 特征。

### Iter

迭代器。

模仿 Rust，实现了 range 迭代器和 collect, map, filter, zip, step_by, enumerate, take 等功能。

ps: C++20 的 Ranges 库。

### Vec

变长数组。

模仿 Rust 的 Vec，移动必须显式调用 `std::move`，拷贝必须用 clone 方法。

### Deque

双端队列。

不同于 C++ 的 deque，该 Deque 使用循环队列存储，空间不够时申请两倍空间。

## 算法相关

### ZkwSegmentTree

zkw 线段树，支持单点修改、区间查询。

### YetAnotherBigInteger

将两个整数合成一个大整数的想法。（因为不会除法的原理而失败）

## 数学相关

### StaticMatrix

行数、列数是编译期常量的二维矩阵。

实现了矩阵的几个最简单的功能。

### Vector2

二维向量。

模仿 C# 的 Vector2。
