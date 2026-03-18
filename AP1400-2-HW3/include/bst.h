#ifndef BST_H
#define BST_H

#include <iostream>
class BST {
  public:
    class Node {
      public:
        int value{0};
        Node *left{nullptr}, *right{nullptr};

        Node() = default;
        Node(const Node &node) = default;
        Node(int value, Node *left, Node *right)
            : value(value), left(left), right(right) {}

        bool operator==(int v) const { return (value == v); }
        std::strong_ordering operator<=>(int v) const { return (value <=> v); }
    };
};

inline std::ostream &operator<<(std::ostream &os, const BST::Node &node) {
    os << node.value << " " << node.left << " " << node.right;
    return os;
}
#endif // BST_H
