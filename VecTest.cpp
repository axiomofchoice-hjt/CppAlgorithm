#include <iostream>
#include <assert.h>
#include "Vec.h"
#include "BaseType.h"
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
    // b[0] = 3;
    assert(a[0][0] == 1);
    assert(a[0][1] == 2);
    assert(b.size() == 0);
    cout << "ok" << endl;
}};

int main() {
    for (size_t i = 0; i < sizeof(tests) / sizeof(tests[0]); i++) {
        cout << "test " << i << endl;
        tests[i]();
        cout << "test " << i << " ok" << endl;
    }
    // cout << a[0] << endl;
    // cout << a[1] << endl;
    return 0;
}