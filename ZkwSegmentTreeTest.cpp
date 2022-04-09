#include <assert.h>

#include <iostream>
#include <vector>

#include "ZkwSegmentTree.h"

using namespace std;

int main() {
    {
        int in[] = {0, 1, 2, 3, 4, 5, 8};
        ZkwSum<int> tree(7, in);

        assert(tree.query(2, 3) == 5);
        assert(tree.query(3, 5) == 12);
        cout << tree << endl;
    }
    {
        ZkwMin<int> tree(8);

        for (int i = 0; i < 8; i++) tree[i] = i;
        assert(tree.query(2, 3) == 2);
        assert(tree.query(3, 5) == 3);
    }
    {
        ZkwMax<int> tree(8);

        for (int i = 0; i < 8; i++) tree[i] = i;
        assert(tree.query(2, 3) == 3);
        assert(tree.query(3, 5) == 5);
    }
    cout << "test ok" << endl;
    return 0;
}