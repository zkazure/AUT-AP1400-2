#ifndef BST_H
#define BST_H

class BST {
  public:
    class Node {
      public:
        Node() = default;
        Node(const Node &node) = default;
        Node(int value, Node *left, Node *right)
            : value(0), left(left), right(right) {}

        int value;
        Node *left, *right;
    };
};

#endif // BST_H
