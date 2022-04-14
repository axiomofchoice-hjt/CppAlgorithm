#ifndef TREE_H
#define TREE_H

#include <algorithm>
#include <forward_list>
#include <iostream>
#include <memory>
#include <utility>
#include <vector>

using std::cout;
using std::endl;

class EmptyStruct {
   public:
    friend std::ostream &operator<<(std::ostream &cout,
                                    const EmptyStruct &self) {
        return cout;
    }
};

template <class NodeInfo = EmptyStruct, class EdgeInfo = EmptyStruct>
class TreeNode {
   private:
    NodeInfo info;
    std::forward_list<std::pair<const TreeNode<NodeInfo, EdgeInfo> *, EdgeInfo>>
        edges;

   public:
    TreeNode() : info(), edges() {}
    TreeNode(NodeInfo info) : info(info), edges() {}
    void setInfo(NodeInfo info) { this->info = info; }
    void addEdge(const TreeNode<NodeInfo, EdgeInfo> &to,
                 const EdgeInfo &edgeInfo = EdgeInfo()) {
        edges.push_front(std::make_pair(&to, edgeInfo));
    }

    void print(size_t depth) const {
        cout << "[" << info << "]" << endl;
        for (const auto &edge : edges) {
            for (size_t i = 0; i < depth + 1; i++) {
                cout << "  ";
            }
            cout << edge.second << "->";
            edge.first->print(depth + 1);
        }
    }
};

template <class NodeInfo = EmptyStruct, class EdgeInfo = EmptyStruct>
class TreeGenerator {
   private:
    std::vector<TreeNode<NodeInfo, EdgeInfo>> _map;
    size_t root;

   public:
    TreeGenerator(size_t nodeNum) : _map(nodeNum, NodeInfo()), root() {}
    TreeNode<NodeInfo, EdgeInfo> &operator[](size_t n) { return _map[n]; }
    void setRoot(size_t root) { this->root = root; }
    void print() const { _map[root].print(0); }
};

#endif