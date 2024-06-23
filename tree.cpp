#pragma once

#include <iostream>
#include <vector>
#include <stack>

/*
Reference:
https://zhuanlan.zhihu.com/p/56895993
*/

namespace tree {

template <class T>
class BinaryNode {
  public:
    T value;
    BinaryNode* left;
    BinaryNode* right;

    BinaryNode() : value(-1), left(nullptr), right(nullptr) {}
    explicit BinaryNode(T val) : value(val), left(nullptr), right(nullptr) {}
};

template <class T>
class Node {
public:
    T value;
    std::vector<Node*> children;

    explicit Node(T val) : value(val) {}
    Node(T val, const std::vector<Node*>& ns) : value(val), children(ns) {}
};

namespace recursion {
template <class T>
void Preorder(const BinaryNode<T>* root, std::vector<T>* res) {
    if (!root) return;

    res->push_back(root->value);
    Preorder(root->left, res);
    Preorder(root->right, res);
}

template <class T>
void Inorder(const BinaryNode<T>* root, std::vector<T>* res) {
    if (!root) return;

    Inorder(root->left, res);
    res->push_back(root->value);
    Inorder(root->right, res);
}

template <class T>
void Postorder(const BinaryNode<T>* root, std::vector<T>* res) {
    if (!root) return;

    Postorder(root->left, res);
    Postorder(root->right, res);
    res->push_back(root->value);
}
}  // namespace recursion


template <class T>
void Preorder(const BinaryNode<T>* root, std::vector<T>* res) {
    std::stack<BinaryNode<T>*> stk;
    BinaryNode<T>* node = root;

    while (node || !stk.empty()) {
        if (node) {
            res->push_back(node->value);
            // stk.push(node);
            if (node->right) stk.push(node->right);
            if (node->left) stk.push(node->left);
            node = node->left;
            continue;
        }
        node = stk.top();
        stk.pop();
    }
}

template <class T>
void Inorder(const BinaryNode<T>* root, std::vector<T>* res) {
    BinaryNode<T>* node = root;
    std::stack<BinaryNode<T>*> stk;

    while (node || !stk.empty()) {
        if (node) {
            stk.push(node);
            node = node->left;
            continue;
        }

        node = stk.top();
        stk.pop();
        res->push_back(node->value);
        node = node->right;
    }
}

}  // namespace tree
