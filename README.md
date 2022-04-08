# CppAlgorithm

（还在完善中）

随手写的 C++ STL 以及一些算法的汇总。

## BaseType

模仿 Rust，对基本类型（整数、浮点数）实现了 Clone、Display 特征。

## Vec

模仿 Rust 的 Vec（类似 C++ 的 vector），移动必须显式调用 `std::move`，拷贝必须用 clone 方法。

实现了 IterMut 迭代器类，支持 Rust 迭代器的 next 方法。

## Deque

不同于 C++ 的 deque，该 Deque 使用循环队列存储，空间不够时申请两倍空间。
