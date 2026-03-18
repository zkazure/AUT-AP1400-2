#ifndef BST_H
#define BST_H

#include <compare>
#include <functional>
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

  private:
    Node *root{nullptr};

  public:
    BST() = default;
    ~BST();

    Node *&get_root() { return root; }
    void bfs(std::function<void(Node *&node)> func);
    size_t length();
    bool add_node(int value);
    Node **find_node(int value);
    Node **find_parrent(int value);
    Node **find_successor(int value);
    bool delete_node(int value);
};

inline std::ostream &operator<<(std::ostream &os, const BST::Node &node) {
    os << &node << " => " << node.value << "  ";
    os << "left: " << node.left << " ";
    os << "right: " << node.right;
    return os;
}
#endif // BST_H
