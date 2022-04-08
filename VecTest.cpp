#include <assert.h>

#include <functional>
#include <iostream>

#include "BaseType.h"
#include "Vec.h"
using std::cout;
using std::endl;

void (*tests[])() = {[] {
    Vec<Vec<i32>> a;
    Vec<i32> b;
    cout << a << endl;
    cout << b << endl;
    b.push_back(1);
    cout << b << endl;
    b.push_back(2);
    cout << b << endl;
    a.push_back(b);
    cout << a << endl;
    assert(a[0][0] == 1);
    assert(a[0][1] == 2);
    assert(b.size() == 0);
    b.resize(3, 7);
    cout << b << endl;
    assert(b[0] == 7);
    assert(b[1] == 7);
    assert(b[2] == 7);
    b.resize(5, 8);
    cout << b << endl;
    assert(b[0] == 7);
    assert(b[1] == 7);
    assert(b[2] == 7);
    assert(b[3] == 8);
    assert(b[4] == 8);
    for (auto i : Iterable(b.iter_mut())) {
        cout << *i << endl;
    }
    a.clear();
    cout << a.size() << endl;
    auto it = MapIter(b.iter(), std::function([](const i32 *x) { return *x * 2; }));
    for (auto i = it.next(); i.has_value(); i = it.next()) {
        cout << i.value() << endl;
    }
}};

int main() {
    for (size_t i = 0; i < sizeof(tests) / sizeof(tests[0]); i++) {
        cout << "test " << i << endl;
        tests[i]();
        cout << "test " << i << " ok" << endl;
    }
    return 0;
}
