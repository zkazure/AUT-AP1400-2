#ifndef BST_H
#define BST_H

#include <compare>
#include <functional>
#include <initializer_list>
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

    Node *clone(const Node *other) const;

  public:
    BST() = default;
    BST(const BST &other);
    BST(BST &&other) noexcept;
    BST(std::initializer_list<int> init);
    ~BST();

    Node *&get_root() { return root; }
    void bfs(std::function<void(Node *&node)> func) const;
    size_t length() const;
    bool add_node(int value);
    Node **find_node(int value);
    Node **find_parrent(int value);
    Node **find_successor(int value);
    bool delete_node(int value);

    BST &operator++();
    BST operator++(int);
    BST &operator=(BST &other);
    BST &operator=(BST &&other) noexcept;
};

std::ostream &operator<<(std::ostream &os, const BST::Node &node);

std::ostream &operator<<(std::ostream &os, BST &bst);
#endif // BST_H
