#include <assert.h>

#include <iostream>

#include "BaseType.h"
#include "Deque.h"
using std::cout;
using std::endl;

void (*tests[])() = {[] {
    Deque<i32> a;
    a.push_back(1);
    a.push_back(2);
    a.push_front(3);
    a.push_front(4);
    a.push_front(5);
    assert(a[0] == 5);
    assert(a[1] == 4);
    assert(a[2] == 3);
    assert(a[3] == 1);
    assert(a[4] == 2);
    for (auto i :
         Iterable(MapIter(
             a.iter(), std::function([](const i32 *x) { return *x * *x; })))) {
        cout << i << ' ' << endl;
    }
    cout << a << endl;
}};

int main() {
    for (size_t i = 0; i < sizeof(tests) / sizeof(tests[0]); i++) {
        cout << "test " << i << endl;
        tests[i]();
        cout << "test " << i << " ok" << endl;
    }
    return 0;
}
