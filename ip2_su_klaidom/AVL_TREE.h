// ------------------------------------------------------
// Author: Aurimas Vižinis
// ------------------------------------------------------


#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <iostream>
#include <string>
#include <memory>  // For std::unique_ptr

namespace AVLProject {

    class AVLTreeImpl;  // Forward declaration of the implementation class

    /**
     * @brief Represents an AVL tree, a self-balancing binary search tree.
     * 
     * This class provides a public interface for interacting with the AVL tree,
     * while hiding implementation details using the PImpl idiom.
     */
    class AVLTree {
    private:
        std::unique_ptr<AVLTreeImpl> pImpl;  ///< Pointer to the implementation class.

    public:
        /**
         * @brief Constructs an empty AVL tree.
         */
        AVLTree();

        /**
         * @brief Destroys the AVL tree and frees all associated memory.
         */
        ~AVLTree();

        /**
         * @brief Constructs a deep copy of another AVL tree.
         * @param other The AVL tree to copy.
         */
        AVLTree(const AVLTree& other);

        /**
         * @brief Copy assignment operator to copy another AVL tree.
         * @param other The AVL tree to copy.
         * @return Reference to the current AVL tree.
         */
        AVLTree& operator=(const AVLTree& other);

        /**
         * @brief Move constructor to transfer ownership of resources.
         * @param other The AVL tree to move from.
         */
        AVLTree(AVLTree&& other) noexcept;

        /**
         * @brief Move assignment operator to transfer ownership of resources.
         * @param other The AVL tree to move from.
         * @return Reference to the current AVL tree.
         */
        AVLTree& operator=(AVLTree&& other) noexcept;

        /**
         * @brief Inserts a value into the AVL tree.
         * @param val The value to insert.
         */
        void insert(const double& val);

        /**
         * @brief Removes a value from the AVL tree.
         * @param val The value to remove.
         */
        void remove(double val);

        /**
         * @brief Searches for a value in the AVL tree.
         * @param val The value to search for.
         * @return True if the value is found, false otherwise.
         */
        bool search(double val) const;

        /**
         * @brief Prints the in-order traversal of the AVL tree to the console.
         */
        void getInOrderTraversal() const;

        /**
         * @brief Returns a string representation of the in-order traversal of the AVL tree.
         * @return A string containing the in-order traversal.
         */
        std::string toString() const;

        // Arithmetic operators

        /**
         * @brief Inserts a value into the AVL tree using the += operator.
         * @param val The value to insert.
         * @return Reference to the current AVL tree.
         */
        AVLTree& operator+=(const double& val);

        /**
         * @brief Removes a value from the AVL tree using the -= operator.
         * @param val The value to remove.
         * @return Reference to the current AVL tree.
         */
        AVLTree& operator-=(const double& val);

        // Unary operators

        /**
         * @brief Deletes the root node of the AVL tree using the -- operator.
         * @return Reference to the current AVL tree.
         */
        AVLTree& operator--();

        /**
         * @brief Frees all memory associated with the AVL tree using the ! operator.
         */
        void operator!();

        // Comparison operators

        /**
         * @brief Compares two AVL trees for equality.
         * @param other The AVL tree to compare with.
         * @return True if the trees are equal, false otherwise.
         */
        bool operator==(const AVLTree& other) const;

        /**
         * @brief Compares two AVL trees for inequality.
         * @param other The AVL tree to compare with.
         * @return True if the trees are not equal, false otherwise.
         */
        bool operator!=(const AVLTree& other) const;

        /**
         * @brief Checks if the current AVL tree is greater than another AVL tree.
         * @param other The AVL tree to compare with.
         * @return True if the current tree is greater, false otherwise.
         */
        bool operator>(const AVLTree& other) const;

        /**
         * @brief Checks if the current AVL tree is less than another AVL tree.
         * @param other The AVL tree to compare with.
         * @return True if the current tree is less, false otherwise.
         */
        bool operator<(const AVLTree& other) const;

        /**
         * @brief Checks if the current AVL tree is greater than or equal to another AVL tree.
         * @param other The AVL tree to compare with.
         * @return True if the current tree is greater than or equal, false otherwise.
         */
        bool operator>=(const AVLTree& other) const;

        /**
         * @brief Checks if the current AVL tree is less than or equal to another AVL tree.
         * @param other The AVL tree to compare with.
         * @return True if the current tree is less than or equal, false otherwise.
         */
        bool operator<=(const AVLTree& other) const;

        // Subscript operator

        /**
         * @brief Searches for a value in the AVL tree using the [] operator.
         * @param val The value to search for.
         * @return True if the value is found, false otherwise.
         */
        bool operator[](const double& val) const;

        // Stream insertion operator

        /**
         * @brief Outputs the in-order traversal of the AVL tree to a stream.
         * @param os The output stream.
         * @param tree The AVL tree to output.
         * @return The output stream.
         */
        friend std::ostream& operator<<(std::ostream& os, const AVLTree& tree);
    };

    /**
     * @brief Exception class for handling duplicate values in the AVL tree.
     */
    class DuplicateValueException : public std::logic_error {
    public:
        /**
         * @brief Constructs a DuplicateValueException with the duplicate value.
         * @param value The duplicate value that caused the exception.
         */
        explicit DuplicateValueException(double value)
            : std::logic_error("Duplicate value detected: " + std::to_string(value)) {}
    };

}
#endif // AVL_TREE_H
