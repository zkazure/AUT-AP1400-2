#ifndef BST_H
#define BST_H

#include <compare>
#include <ostream>
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

static std::ostream &operator<<(std::ostream &os, const BST::Node &node) {
    os << std::ios::hex << &node << "   =>";
    os << node.value << "      ";
    os << "left: " << std::ios::hex << node.left << std::ios::right << "     ";
    os << "right: " << std::ios::hex << node.right << std::endl;
    return os;
}
#endif // BST_H
