#include "AVL_TREE.h"
#include <iostream>
#include <algorithm>
#include <memory>
#include <sstream>

namespace AVLProject {

    AVLTree::AVLTree() : pImpl(std::make_unique<AVLTreeImpl>()) {}
    AVLTree::~AVLTree() = default;
    AVLTree::AVLTree(const AVLTree& other) : pImpl(std::make_unique<AVLTreeImpl>()) {
        if (other.pImpl->root) {
            pImpl->root = pImpl->copyTree(other.pImpl->root); // Ensure deep copy
        }
    }
    AVLTree& AVLTree::operator=(const AVLTree& other) {
        if (this != &other) {
            pImpl->freeMemory(pImpl->root);
            if (other.pImpl->root) {
                pImpl->root = pImpl->copyTree(other.pImpl->root); // Ensure deep copy
            } else {
                pImpl->root = nullptr;
            }
        }
        return *this;
    }
    AVLTree::AVLTree(AVLTree&& other) noexcept : pImpl(std::move(other.pImpl)) {}
    AVLTree& AVLTree::operator=(AVLTree&& other) noexcept {
        if (this != &other) {
            pImpl = std::move(other.pImpl);
        }
        return *this;
    }

    bool AVLTree::operator==(const AVLTree& other) const {
        return pImpl->compareTrees(pImpl->root, other.pImpl->root);
    }
    bool AVLTree::operator!=(const AVLTree& other) const {
        return !(*this == other);
    }
    AVLTree& AVLTree::operator+=(const double& val) {
        try {
            pImpl->root = pImpl->insertNode(pImpl->root, val);
        } catch (const std::logic_error& e) {
            throw;
        }
        return *this;
    }
    AVLTree& AVLTree::operator-=(const double& val) {
        pImpl->root = pImpl->deleteNode(pImpl->root, val);
        return *this;
    }
    bool AVLTree::operator[](const double& val) const {
        return pImpl->searchNode(pImpl->root, val);
    }
    AVLTree& AVLTree::operator--() {
        if (pImpl->root) {
            pImpl->root = pImpl->deleteNode(pImpl->root, pImpl->root->value);
        }
        return *this;
    }
    void AVLTree::operator!() {
        pImpl->freeMemory(pImpl->root);
        pImpl->root = nullptr;
    }

    bool AVLTree::operator>(const AVLTree& other) const {
        return this->toString().size() > other.toString().size(); 
    }

    bool AVLTree::operator<(const AVLTree& other) const {
        return this->toString().size() < other.toString().size(); 
    }

    bool AVLTree::operator>=(const AVLTree& other) const {
        return !(*this < other); 
    }

    bool AVLTree::operator<=(const AVLTree& other) const {
        return !(*this > other); 
    }

    void AVLTree::insert(const double& val) {
        pImpl->root = pImpl->insertNode(pImpl->root, val);
    }
    void AVLTree::remove(const double& val) {
        pImpl->root = pImpl->deleteNode(pImpl->root, val);
    }
    bool AVLTree::search(const double& val) const {
        return pImpl->searchNode(pImpl->root, val);
    }
    void AVLTree::inOrder() const {
        pImpl->inOrderTraversal(pImpl->root, std::cout);
    }
    std::string AVLTree::toString() const {
        std::ostringstream os;
        pImpl->inOrderTraversal(pImpl->root, os);
        return os.str();
    }

    std::ostream& operator<<(std::ostream& os, const AVLTree& tree) {
        tree.pImpl->inOrderTraversal(tree.pImpl->root, os);
        return os;
    }

    AVLTreeImpl::~AVLTreeImpl() {
        freeMemory(root);
    }

    void AVLTreeImpl::freeMemory(AVLNode* node) {
        if (node) {
            freeMemory(node->left);
            freeMemory(node->right);
            delete node;
        }
    }

    AVLNode* AVLTreeImpl::insertNode(AVLNode* node, const double& val) {
        if (!node) return new AVLNode(val);

        if (val < node->value)
            node->left = insertNode(node->left, val);
        else if (val > node->value)
            node->right = insertNode(node->right, val);
        else
            throw std::logic_error("Duplicate value detected: " + std::to_string(val));

        node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
        int balance = getBalanceFactor(node);

        if (balance > 1 && val < node->left->value)
            return rotateRight(node);
        if (balance < -1 && val > node->right->value)
            return rotateLeft(node);
        if (balance > 1 && val > node->left->value) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        if (balance < -1 && val < node->right->value) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    AVLNode* AVLTreeImpl::deleteNode(AVLNode* node, const double& val) {
        if (!node) return nullptr;

        if (val < node->value)
            node->left = deleteNode(node->left, val);
        else if (val > node->value)
            node->right = deleteNode(node->right, val);
        else {
            if (!node->left || !node->right) {
                AVLNode* temp = node->left ? node->left : node->right;
                delete node;
                return temp;
            } else {
                AVLNode* temp = minValueNode(node->right);
                node->value = temp->value;
                node->right = deleteNode(node->right, temp->value);
            }
        }

        if (!node) return node;

        node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
        int balance = getBalanceFactor(node);

        if (balance > 1 && getBalanceFactor(node->left) >= 0)
            return rotateRight(node);
        if (balance > 1 && getBalanceFactor(node->left) < 0) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        if (balance < -1 && getBalanceFactor(node->right) <= 0)
            return rotateLeft(node);
        if (balance < -1 && getBalanceFactor(node->right) > 0) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    AVLNode* AVLTreeImpl::minValueNode(AVLNode* node) {
        AVLNode* current = node;
        while (current->left)
            current = current->left;
        return current;
    }

    void AVLTreeImpl::inOrderTraversal(AVLNode* node, std::ostream& os) const {
        if (node) {
            inOrderTraversal(node->left, os);
            os << node->value << " ";
            inOrderTraversal(node->right, os);
        }
    }

    bool AVLTreeImpl::searchNode(AVLNode* node, const double& val) const {
        if (!node) return false;
        if (node->value == val) return true;
        if (val < node->value) return searchNode(node->left, val);
        return searchNode(node->right, val);
    }

    int AVLTreeImpl::getHeight(const AVLNode* node) const {
        return node ? node->height : 0;
    }

    int AVLTreeImpl::getBalanceFactor(const AVLNode* node) const {
        return node ? getHeight(node->left) - getHeight(node->right) : 0;
    }

    AVLNode* AVLTreeImpl::rotateRight(AVLNode* y) {
        AVLNode* x = y->left;
        AVLNode* T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;
        x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;

        return x;
    }

    AVLNode* AVLTreeImpl::rotateLeft(AVLNode* x) {
        AVLNode* y = x->right;
        AVLNode* T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;
        y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;

        return y;
    }

    bool AVLTreeImpl::compareTrees(const AVLNode* a, const AVLNode* b) const {
        if (!a && !b) return true;
        if (!a || !b) return false;

        return (a->value == b->value) &&
               compareTrees(a->left, b->left) &&
               compareTrees(a->right, b->right);
    }

    AVLNode* AVLTreeImpl::copyTree(const AVLNode* node) const {
        if (!node) return nullptr;

        AVLNode* newNode = new AVLNode(node->value);
        newNode->left = copyTree(node->left);
        newNode->right = copyTree(node->right);
        newNode->height = node->height;
        return newNode;
    }

}