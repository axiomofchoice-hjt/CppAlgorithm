#ifndef ZKWSEGMENTTREE_H
#define ZKWSEGMENTTREE_H

#include <functional>
#include <iostream>
#include <vector>

using std::cout;
using std::endl;

template <class Type, class Opt = std::plus<Type>>
class ZkwSegmentTree {
   private:
    size_t prefix_size;
    std::vector<Type> a;

    void up(size_t x) { a[x] = Opt()(a[x * 2], a[x * 2 + 1]); }

    class Modifier {
       private:
        ZkwSegmentTree<Type, Opt> *tree;
        size_t pos;

       public:
        Modifier(ZkwSegmentTree<Type, Opt> *tree, size_t pos)
            : tree(tree), pos(pos) {}

        Type get() const { return tree->a[pos]; }

        const Modifier &set(Type k) const {
            size_t temp = pos;
            tree->a[temp] = k;
            while ((temp >>= 1) != 0) {
                tree->up(temp);
            }
            return *this;
        }

        const Modifier &operator=(Type k) const { return set(k); }
        const Modifier &operator+=(Type k) const {
            return set(tree->a[pos] + k);
        }
        const Modifier &to_min(Type k) const {
            return set(std::min(tree->a[pos], k));
        }
        const Modifier &to_max(Type k) const {
            return set(std::max(tree->a[pos], k));
        }

        operator Type() const { return get(); }
    };

   public:
    ZkwSegmentTree(size_t n)
        : prefix_size(1 << (32 - __builtin_clzll(n - 1))),
          a(prefix_size + n, Type()) {
        for (size_t i = prefix_size - 1; i != 0; i--) {
            up(i);
        }
    }

    template <class T>
    ZkwSegmentTree(size_t n, T *initializer)
        : prefix_size(1 << (32 - __builtin_clzll(n - 1))),
          a(prefix_size + n, Type()) {
        T *it = initializer;
        for (size_t i = 0; i < n; i++, it++) {
            a[i + prefix_size] = *it;
        }
        for (size_t i = prefix_size - 1; i != 0; i--) {
            up(i);
        }
    }

    Modifier operator[](size_t pos) {
        return Modifier(this, pos + prefix_size);
    }

    Type query(size_t l, size_t r) const {
        if (l > r) {
            throw "Empty interval";
        }
        Type ans = a[l + prefix_size];
        l++;
        l += prefix_size - 1;
        r += prefix_size + 1;
        while (l + 1 < r) {
            if (l % 2 == 0) {
                ans = Opt()(ans, a[l + 1]);
            }
            if (r % 2 == 1) {
                ans = Opt()(ans, a[r - 1]);
            }
            l >>= 1;
            r >>= 1;
        }
        return ans;
    }

    friend std::ostream &operator<<(std::ostream &cout,
                                    const ZkwSegmentTree<Type, Opt> &self) {
        cout << "[";
        for (size_t i = 0; i < self.a.size() - self.prefix_size; i++) {
            cout << self.a[i + self.prefix_size];
            if (i != self.a.size() - self.prefix_size - 1) {
                cout << ", ";
            }
        }
        cout << "]";
        return cout;
    }
};

template <class Type>
class Min {
   public:
    Type operator()(const Type &a, const Type &b) const {
        return std::min(a, b);
    }
};

template <class Type>
class Max {
   public:
    Type operator()(const Type &a, const Type &b) const {
        return std::max(a, b);
    }
};

template <class Type>
using ZkwSum = ZkwSegmentTree<Type>;
template <class Type>
using ZkwMin = ZkwSegmentTree<Type, Min<Type>>;
template <class Type>
using ZkwMax = ZkwSegmentTree<Type, Max<Type>>;

#endif
