#ifndef BST_H
#define BST_H

class BST {
  public:
    class Node {
      public:
        Node();
        Node(int value, Node *left, Node *right);
        Node(const Node &node);

        int value;
        Node *left, *right;
    };
};

#endif // BST_H
