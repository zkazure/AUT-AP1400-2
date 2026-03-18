#include "bst.h"

void BST::destroy_subtree(Node *node) {
    if (!node)
        return;

    destroy_subtree(node->left);
    destroy_subtree(node->right);
    delete (node);
}

BST::~BST() {
    destroy_subtree(root);
    root = nullptr;
}

bool BST::add_node(int value) {
    if (!root) {
        root = new BST::Node(value, nullptr, nullptr);
        return true;
    }

    BST::Node *curr = root;
    BST::Node *prev = nullptr;
    while (curr) {
        if (value == *curr)
            return false;
        prev = curr;
        curr = (value < *curr) ? curr->left : curr->right;
    }
    BST::Node *node = new BST::Node(value, nullptr, nullptr);
    if (value < *prev)
        prev->left = node;
    else
        prev->right = node;

    return true;
}
