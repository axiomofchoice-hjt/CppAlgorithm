#include <assert.h>

#include <iostream>
#include <list>

#include "Iter.h"

using namespace std;

int main() {
    list<int> a{1, 2, 3};
    auto b = IterFromSTLIterator(a.begin(), a.end());
    auto c = ConcatIter(b, b);
    for (auto i : Iterable(c)) {
        cout << *i << ' ';
    }
    cout << endl;
    {
        int cnt = 0;
        for (auto i : Iterable(RangeIter(0, 10))) {
            assert(cnt == i);
            cnt++;
        }
    }
    {
        int cnt = 0;
        for (auto i : Iterable(ZipIter(RangeIter(0, 8), RangeIter(0, 9)))) {
            cout << i.first << ' ' << i.second << endl;
            cnt++;
        }
    }
    {
        int cnt = 0;
        for (auto i : Iterable(MapIter(
                 RangeIter(0, 10), function([](int x) { return x * x; })))) {
            assert(cnt * cnt == i);
            cnt++;
        }
    }
    {
        int cnt = 0;
        for (auto i : Iterable(FilterIter(RangeIter(0, 10), function([](int x) {
                                              return x % 2 == 1;
                                          })))) {
            cout << i << ' ';
            cnt++;
        }
        cout << endl;
    }
    {
        int cnt = 0;
        for (auto [index, item] : Iterable(EnumerateIter(RangeIter(1, 10)))) {
            cout << index << item << ' ';
            cnt++;
        }
        cout << endl;
    }
    {
        int cnt = 0;
        for (auto i : Iterable(StepByIter(RangeIter(1, 12), 3))) {
            cout << i << ' ';
            cnt++;
        }
        cout << endl;
    }
    {
        int cnt = 0;
        for (auto i : Iterable(TakeIter(RangeIter(1, 12), 3))) {
            cout << i << ' ';
            cnt++;
        }
        cout << endl;
    }
    {
        int cnt = 0;
        for (auto i : collect<vector<int>>(TakeIter(RangeIter(1, 12), 3))) {
            cout << i << ' ';
            cnt++;
        }
        cout << endl;
    }
    // cout << *c.next().value() << endl;
    // cout << *c.next().value() << endl;
    // cout << *c.next().value() << endl;
    // cout << *c.next().value() << endl;
    // cout << *c.next().value() << endl;
    // cout << *c.next().value() << endl;
    // cout << *c.next().value() << endl;
    return 0;
}