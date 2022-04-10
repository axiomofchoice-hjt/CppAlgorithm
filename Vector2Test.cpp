#include <assert.h>

#include <iostream>

#include "Vector2.h"

using namespace std;

int main() {
    {
        Vector2<double> a(1.0, 1.0);
        a += Vector2(1.0, 2.0);
        assert(a == Vector2(2.0, 3.0));
        a -= Vector2(3.0, 1.0);
        assert(a == Vector2(-1.0, 2.0));
        a *= 2;
        assert(a == Vector2(-2.0, 4.0));
        a /= 4;
        assert(a == Vector2(-0.5, 1.0));
        cout << a << endl;
    }
    {
        assert(Vector2<double>::Dot(Vector2(1.0, 20.0), Vector2(1.5, 30.0)) == 601.5);
        assert(Vector2<double>::Cross(Vector2(1.0, 20.0), Vector2(30.0, 1.5)) == -598.5);
        cout << Vector2(1.5, 2.0).length() << endl;
    }
    cout << "test ok" << endl;
    return 0;
}