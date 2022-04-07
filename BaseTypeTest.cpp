#include <assert.h>

#include <iostream>

#include "BaseType.h"
using std::cout;
using std::endl;

int main() {
    i32 a;
    a = 1;
    a += i32(2);
    assert(a == i32(3));
    assert(a.clone() == i32(3));
    assert(i32(5) + i32(7) == i32(12));
    assert(i32(5) - i32(7) == i32(-2));
    assert(i32(5) * i32(7) == i32(35));
    assert(i32(13) / i32(3) == i32(4));
    assert(i32(13) % i32(3) == i32(1));
    assert((i32(7) & i32(15)) == i32(7));
    assert((i32(7) | i32(15)) == i32(15));
    assert((i32(7) ^ i32(15)) == i32(8));
    assert(-i32(7) == i32(-7));
    assert(~i32(7) == i32(-8));

    f64 b;
    b = 1.0;
    assert(b == f64(1.0));

    return 0;
}