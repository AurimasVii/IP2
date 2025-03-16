#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <memory>
#include <iostream>
#include <string>
#include <stdexcept>

namespace AVLProject {

    struct AVLNode {
        double value;
        AVLNode* left;
        AVLNode* right;
        int height;

        AVLNode(double val) : value(val), left(nullptr), right(nullptr), height(1) {}
    };

    class AVLTreeImpl {
    public:
        AVLNode* root;

        AVLTreeImpl() : root(nullptr) {}
        ~AVLTreeImpl();
        AVLNode* insertNode(AVLNode* node, const double& val);
        AVLNode* deleteNode(AVLNode* node, const double& val);
        AVLNode* minValueNode(AVLNode* node);
        void freeMemory(AVLNode* node);
        void inOrderTraversal(AVLNode* node, std::ostream& os) const;
        bool searchNode(AVLNode* node, const double& val) const;
        int getHeight(const AVLNode* node) const;
        int getBalanceFactor(const AVLNode* node) const;
        AVLNode* rotateRight(AVLNode* y);
        AVLNode* rotateLeft(AVLNode* x);
        bool compareTrees(const AVLNode* a, const AVLNode* b) const;
        AVLNode* copyTree(const AVLNode* node) const; 
    };

    class AVLTree {
    private:
        std::unique_ptr<AVLTreeImpl> pImpl;

    public:
        AVLTree();
        AVLTree(const AVLTree& other);
        AVLTree(AVLTree&& other) noexcept;
        ~AVLTree();

        AVLTree& operator=(const AVLTree& other);
        AVLTree& operator=(AVLTree&& other) noexcept;

        AVLTree& operator+=(const double& val);
        AVLTree& operator-=(const double& val);
        bool operator[](const double& val) const;
        AVLTree& operator--();
        void operator!();

        bool operator==(const AVLTree& other) const;
        bool operator!=(const AVLTree& other) const;
        bool operator>(const AVLTree& other) const;  
        bool operator<(const AVLTree& other) const;  
        bool operator>=(const AVLTree& other) const; 
        bool operator<=(const AVLTree& other) const; 

        void insert(const double& val);
        void remove(const double& val);
        bool search(const double& val) const;
        void inOrder() const;
        std::string toString() const;

        friend std::ostream& operator<<(std::ostream& os, const AVLTree& tree);
    };

}

#endif
