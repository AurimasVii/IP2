#include "AVL_TREE.h"
#include <iostream>
#include <algorithm>
#include <sstream>

namespace AVLProject {

    /**
     * @brief Represents a single node in the AVL tree.
     */
    struct AVLNode {
        double value;         ///< The value stored in the node.
        AVLNode* left;        ///< Pointer to the left child.
        AVLNode* right;       ///< Pointer to the right child.
        AVLNode* parent;      ///< Pointer to the parent node.
        int height;           ///< Height of the node in the tree.

        /**
         * @brief Constructs an AVLNode with a given value and optional parent.
         * @param val The value to store in the node.
         * @param parent Pointer to the parent node (default is nullptr).
         */
        AVLNode(double val, AVLNode* parent = nullptr)
            : value(val), left(nullptr), right(nullptr), parent(parent), height(1) {}
    };

    class AVLTreeImpl {
    public:
        AVLNode* root;

        AVLTreeImpl() : root(nullptr) {}
        ~AVLTreeImpl() { freeMemory(root); }

        AVLNode* insertNode(AVLNode* node, const double& val, AVLNode* parent);
        AVLNode* deleteNode(AVLNode* node, const double& val);
        AVLNode* minValueNode(AVLNode* node);
        void freeMemory(AVLNode* node);
        void inOrderTraversal(AVLNode* node, std::ostream& os) const;
        bool searchNode(AVLNode* node, const double& val) const;
        int getHeight(const AVLNode* node) const;
        int getBalanceFactor(const AVLNode* node) const;
        AVLNode* rotateRight(AVLNode* y);
        AVLNode* rotateLeft(AVLNode* x);
        AVLNode* copyTree(const AVLNode* node) const;
        int countNodes(AVLNode* node) const;
        double sumValues(AVLNode* node) const;
        bool compareTrees(const AVLNode* a, const AVLNode* b) const;
    };

    AVLTree::AVLTree() : pImpl(std::make_unique<AVLTreeImpl>()) {}
    AVLTree::~AVLTree() {
        // No need to manually free memory; unique_ptr handles it
    }
    AVLTree::AVLTree(const AVLTree& other) : pImpl(std::make_unique<AVLTreeImpl>()) {
        if (other.pImpl && other.pImpl->root) {
            pImpl->root = pImpl->copyTree(other.pImpl->root);  // Deep copy of the tree
        } else {
            pImpl->root = nullptr;
        }
    }

    AVLTree::AVLTree(AVLTree&& other) noexcept {
        pImpl = std::move(other.pImpl); // Transfer ownership
        other.pImpl = std::make_unique<AVLTreeImpl>(); // Reset the moved-from object to a new, empty state
    }

    AVLTree& AVLTree::operator=(const AVLTree& other) {
        if (this != &other) {
            // Free existing resources
            pImpl->freeMemory(pImpl->root);
            pImpl->root = nullptr;

            // Deep copy the other tree
            if (other.pImpl && other.pImpl->root) {
                pImpl->root = pImpl->copyTree(other.pImpl->root);
            }
        }
        return *this;
    }

    AVLTree& AVLTree::operator=(AVLTree&& other) noexcept {
        if (this != &other) {
            // Release any existing resources
            pImpl.reset();

            // Transfer ownership of pImpl
            pImpl = std::move(other.pImpl);

            // Reset the moved-from object to a new, empty state
            other.pImpl = std::make_unique<AVLTreeImpl>();
        }
        return *this;
    }

    void AVLTree::insert(const double& val) {
        pImpl->root = pImpl->insertNode(pImpl->root, val, nullptr);
    }

    void AVLTree::remove(double val) {
        pImpl->root = pImpl->deleteNode(pImpl->root, val);
    }

    bool AVLTree::search(double val) const {
        return pImpl->searchNode(pImpl->root, val);
    }

    void AVLTree::getInOrderTraversal() const {
        pImpl->inOrderTraversal(pImpl->root, std::cout);
    }

    std::string AVLTree::toString() const {
        if (!pImpl || !pImpl->root) {
            return ""; // Return an empty string if the tree is empty or pImpl is null
        }
        std::ostringstream os;
        pImpl->inOrderTraversal(pImpl->root, os);
        return os.str();
    }

    AVLTree& AVLTree::operator+=(const double& val) {
        insert(val);
        return *this;
    }

    AVLTree& AVLTree::operator-=(const double& val) {
        remove(val);
        return *this;
    }

    bool AVLTree::operator[](const double& val) const {
        return search(val);
    }

    AVLTree& AVLTree::operator--() {
        if (pImpl->root) {
            pImpl->root = pImpl->deleteNode(pImpl->root, pImpl->root->value);
        }
        return *this;
    }

    void AVLTree::operator!() {
        if (pImpl) {
            pImpl->freeMemory(pImpl->root);
            pImpl->root = nullptr; // Ensure the tree is properly reset
        }
    }

    bool AVLTree::operator==(const AVLTree& other) const {
        return pImpl->compareTrees(pImpl->root, other.pImpl->root); //viskas apie sumas turetu but
    }

    bool AVLTree::operator!=(const AVLTree& other) const {
        return !(*this == other);
    }

    bool AVLTree::operator>(const AVLTree& other) const {
        return pImpl->sumValues(pImpl->root) > other.pImpl->sumValues(other.pImpl->root);
    }

    bool AVLTree::operator<(const AVLTree& other) const {
        return pImpl->sumValues(pImpl->root) < other.pImpl->sumValues(other.pImpl->root);
    }

    bool AVLTree::operator>=(const AVLTree& other) const {
        return !(*this < other);
    }

    bool AVLTree::operator<=(const AVLTree& other) const {
        return !(*this > other);
    }

    std::ostream& operator<<(std::ostream& os, const AVLTree& tree) {
        tree.pImpl->inOrderTraversal(tree.pImpl->root, os);
        return os;
    }

    // AVLTreeImpl Private Methods
    AVLNode* AVLTreeImpl::insertNode(AVLNode* node, const double& val, AVLNode* parent) {
        if (!node) return new AVLNode(val, parent);

        if (val < node->value)
            node->left = insertNode(node->left, val, node);
        else if (val > node->value)
            node->right = insertNode(node->right, val, node);
        else if(val == 2*val)
            throw DuplicateValueException(val);  // Pass the duplicate value to the exception

        node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
        int balance = getBalanceFactor(node);

        if (balance > 1 && val < node->left->value) return rotateRight(node);
        if (balance < -1 && val > node->right->value) return rotateLeft(node);
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
                if (temp) temp->parent = node->parent;
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

        if (balance > 1 && getBalanceFactor(node->left) >= 0) return rotateRight(node);
        if (balance > 1 && getBalanceFactor(node->left) < 0) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        if (balance < -1 && getBalanceFactor(node->right) <= 0) return rotateLeft(node);
        if (balance < -1 && getBalanceFactor(node->right) > 0) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    void AVLTreeImpl::freeMemory(AVLNode* node) {
        if (node) {
            freeMemory(node->left);
            freeMemory(node->right);
            delete node;
        }
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

        if (T2) T2->parent = y;
        x->parent = y->parent;
        y->parent = x;

        y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;
        x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;

        return x;
    }

    AVLNode* AVLTreeImpl::rotateLeft(AVLNode* x) {
        AVLNode* y = x->right;
        AVLNode* T2 = y->left;

        y->left = x;
        x->right = T2;

        if (T2) T2->parent = x;
        y->parent = x->parent;
        x->parent = y;

        x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;
        y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;

        return y;
    }

    AVLNode* AVLTreeImpl::minValueNode(AVLNode* node) {
        AVLNode* current = node;
        while (current->left)
            current = current->left;
        return current;
    }

    AVLNode* AVLTreeImpl::copyTree(const AVLNode* node) const {
        if (!node) return nullptr;
        AVLNode* newNode = new AVLNode(node->value);
        newNode->left = copyTree(node->left);
        newNode->right = copyTree(node->right);
        newNode->height = node->height;
        return newNode;
    }

    bool AVLTreeImpl::compareTrees(const AVLNode* a, const AVLNode* b) const {
        if (!a && !b) return true;
        if (!a || !b) return false;
        return (a->value == b->value) &&
               compareTrees(a->left, b->left) &&
               compareTrees(a->right, b->right);
    }

    int AVLTreeImpl::countNodes(AVLNode* node) const {
        if (!node) return 0;
        return 1 + countNodes(node->left) + countNodes(node->right);
    }

    double AVLTreeImpl::sumValues(AVLNode* node) const {
        if (!node) return 0;
        return node->value + sumValues(node->left) + sumValues(node->right);
    }

}  // namespace AVLProject
