#include <iostream>

#include "Tree.h"

using namespace std;

int main() {
    {
        TreeGenerator<> tree(5);
        tree[0].addEdge(tree[1]);
        tree[0].addEdge(tree[2]);
        tree[1].addEdge(tree[3]);
        tree[1].addEdge(tree[4]);
        tree.print();
    }
    cout << "test ok" << endl;
    return 0;
}