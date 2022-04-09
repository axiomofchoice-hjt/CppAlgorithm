#include <assert.h>

#include <iostream>
#include <vector>

#include "YetAnotherBigInteger.h"

using namespace std;

int main() {
    {
        YABigInt<YAInt32> a(YAInt32(0), YAInt32(UINT_MAX));
        YABigInt<YAInt32> b(YAInt32(2));
        cout << a << endl;
        cout << b << endl;
        tie(a, b) = a * b;
        cout << a << endl;
        cout << b << endl;
        // assert(b == YAInt32(1));
    }
    cout << "test ok" << endl;
    return 0;
}