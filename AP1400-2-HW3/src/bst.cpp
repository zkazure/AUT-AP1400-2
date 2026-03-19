#include "bst.h"
#include <cstddef>
#include <iomanip>
#include <queue>
#include <stack>
#include <string>
#include <vector>

void BST::bfs(std::function<void(Node *&node)> func) const {
    std::queue<Node *> que;
    if (root)
        que.push(root);
    while (que.empty() == false) {
        Node *node = que.front();
        que.pop();
        func(node);
        if (node->left)
            que.push(node->left);
        if (node->right)
            que.push(node->right);
    }
}

BST::Node *BST::clone(const Node *other) const {
    if (other == nullptr)
        return nullptr;

    Node *node = new Node(other->value, nullptr, nullptr);
    node->left = clone(other->left);
    node->right = clone(other->right);
    return node;
}

BST::BST(const BST &other) { root = clone(other.root); }

BST::~BST() {
    std::vector<Node *> nodes;
    bfs([&nodes](Node *&node) { nodes.push_back(node); });
    for (auto node : nodes)
        delete node;
}

size_t BST::length() const {
    size_t len = 0;
    bfs([&len](Node *&node) { len++; });
    return len;
}

bool BST::add_node(int value) {
    if (!root) {
        root = new Node(value, nullptr, nullptr);
        return true;
    }

    Node *curr = root;
    Node *prev = nullptr;
    while (curr) {
        if (value == *curr)
            return false;
        prev = curr;
        curr = (value < *curr) ? curr->left : curr->right;
    }
    Node *node = new BST::Node(value, nullptr, nullptr);
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

    Node *curr = root;
    Node *prev = nullptr;
    while (curr) {
        prev = curr;
        curr = (value < *curr) ? curr->left : curr->right;
        if (curr && value == *curr) {
            return (prev->left == curr) ? &(prev->left) : &(prev->right);
        }
    }

    return nullptr;
}

BST::Node **BST::find_parrent(int value) {
    if (root == nullptr || value == *root)
        return nullptr;

    Node **curr = &root;
    Node **prev = nullptr;
    while (curr) {
        if (value == **curr)
            return prev;

        prev = curr;
        curr = (value < **curr) ? &(*curr)->left : &(*curr)->right;
    }

    return nullptr;
}

BST::Node **BST::find_successor(int value) {
    // 中序遍历的前驱节点
    if (root == nullptr)
        return nullptr;

    std::stack<Node **> st;
    Node **curr = &root;
    Node **prev = nullptr;
    while (*curr || st.empty() == false) {
        if (*curr) {
            st.push(curr);
            curr = &(*curr)->left;
        } else {
            curr = st.top();
            st.pop();
            if (value == **curr)
                return prev;
            prev = curr;
            curr = &(*curr)->right;
        }
    }
    return nullptr;
}

bool BST::delete_node(int value) {
    if (root == nullptr)
        return false;

    Node **node = find_node(value);
    if (node == nullptr)
        return false;
    Node *to_delete = *node;

    Node **parr = find_parrent(value), **succ = find_successor(value);
    if ((*node)->left == nullptr) {
        if ((*node)->right) {
            // only right side exist
            if (parr) {
                if ((*parr)->left == *node)
                    (*parr)->left = (*node)->right;
                else
                    (*parr)->right = (*node)->right;
            } else {
                root = (*node)->right;
            }
        } else {
            // leaf node
            if (parr) {
                if ((*parr)->left == *node)
                    (*parr)->left = nullptr;
                else
                    (*parr)->right = nullptr;
            } else {
                root = nullptr;
            }
        }
    } else {
        if ((*node)->right) {
            // both side exist
            Node **succ_parr = find_parrent((*succ)->value);
            (*succ)->left = (*node)->left;
            (*succ)->right = (*node)->right;

            if (parr) {
                if ((*parr)->left == *node)
                    (*parr)->left = *succ;
                else
                    (*parr)->right = *succ;
            } else {
                root = *succ;
            }
            (*succ_parr)->right = nullptr;
        } else {
            // only left side exist
            if (parr) {
                if ((*parr)->left == *node)
                    (*parr)->left = (*node)->left;
                else
                    (*parr)->right = (*node)->left;
            } else {
                root = (*node)->left;
            }
        }
    }
    delete to_delete;
    return true;
}

BST &BST::operator++() {
    bfs([](Node *&node) { node->value += 1; });
    return *this;
}

BST BST::operator++(int) {
    BST tmp = *this;
    bfs([](Node *&node) { node->value += 1; });
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
