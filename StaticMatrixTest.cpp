#include <assert.h>

#include <iostream>

#include "StaticMatrix.h"

using namespace std;

int main() {
    {
        StaticMatrix<int, 2, 2> a{{1, 2}, {3, 4}};
        StaticMatrix<int, 2, 2> b{{1, 2}, {3, 4}};
        cout << a << endl;
        assert(a * b == (StaticMatrix<int, 2, 2>{{7, 10}, {15, 22}}));
        b = StaticMatrix<int, 2, 2>{{2, 10}, {4, 1}};
        assert(a + b == (StaticMatrix<int, 2, 2>{{3, 12}, {7, 5}}));
        assert(a - b == (StaticMatrix<int, 2, 2>{{-1, -8}, {-1, 3}}));
    }
    {
        StaticMatrix<int, 1, 2> a{{1, 2}};
        StaticMatrix<int, 2, 1> b{{3}, {4}};
        assert(a * b == (StaticMatrix<int, 1, 1>{{11}}));
    }
    {
        StaticMatrix<double, 3, 3> a{{1, 2, 9}, {3, 5, 7}, {6, 4, 8}};
        assert(a.det() == -114);
    }
    {
        StaticMatrix<double, 3, 3> a{{1, 2, 9}, {3, 5, 7}, {6, 4, 8}};
        cout << a.inverse().inverse() << endl;
    }
    cout << "test ok" << endl;
    return 0;
}