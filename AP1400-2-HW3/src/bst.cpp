#include "bst.h"
#include <cstddef>
#include <queue>
#include <vector>

void BST::bfs(std::function<void(BST::Node *&node)> func) {
    std::queue<BST::Node *> que;
    if (root)
        que.push(root);
    while (que.empty() == false) {
        BST::Node *node = que.front();
        que.pop();
        func(node);
        if (node->left)
            que.push(node->left);
        if (node->right)
            que.push(node->right);
    }
}

size_t BST::length() {
    size_t len = 0;
    bfs([&len](BST::Node *&node) { len++; });
    return len;
}

BST::~BST() {
    std::vector<BST::Node *> nodes;
    bfs([&nodes](BST::Node *&node) { nodes.push_back(node); });
    for (auto node : nodes)
        delete node;
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
