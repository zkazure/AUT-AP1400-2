#include "bst.h"
#include <cstddef>
#include <iomanip>
#include <queue>
#include <string>
#include <vector>

void BST::bfs(std::function<void(BST::Node *&node)> func) const {
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

size_t BST::length() const {
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

BST::Node **BST::find_node(int value) {
    if (root == nullptr)
        return nullptr;

    if (value == *root)
        return &root;

    BST::Node *curr = root;
    BST::Node *prev = nullptr;
    while (curr) {
        prev = curr;
        curr = (value < *curr) ? curr->left : curr->right;
        if (curr && value == *curr) {
            return (prev->left == curr) ? &(prev->left) : &(prev->right);
        }
    }

    return nullptr;
}

BST &BST::operator++() {
    bfs([](BST::Node *&node) { node->value += 1; });
    return *this;
}

BST BST::operator++(int) {
    BST tmp = *this;
    bfs([](BST::Node *&node) { node->value += 1; });
    return tmp;
}

std::ostream &operator<<(std::ostream &os, const BST::Node &node) {
    os << std::left;
    os << std::setw(17) << &node;
    os << "=> value:" << std::setw(10) << node.value;
    os << "left:" << std::setw(16) << node.left;
    os << "right:" << std::setw(16) << node.right;
    return os;
}

std::ostream &operator<<(std::ostream &os, BST &bst) {
    std::string boundary = "***************************************************"
                           "*****************************";

    os << boundary << "\n";
    bst.bfs([&os](BST::Node *&node) { os << *node << "\n"; });
    os << "binary search tree size: " << bst.length() << "\n";
    os << boundary << "\n";
    return os;
}
