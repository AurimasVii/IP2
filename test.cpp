#include <cassert>
#include <iostream>
#include <fstream>
#include "AVL_TREE.h"

using namespace std;
using namespace AVLProject;

int main() {
    ofstream logFile("log.txt");
    if (!logFile.is_open()) {
        cerr << "Error: Could not open log.txt for writing." << endl;
        return 1;
    }

    auto log = [&](const string& message) {
        cout << message << endl;
        logFile << message << endl;
    };

    try {
        AVLTree tree;
        assert(tree.toString() == "");
        log("Test Constructor: Passed");

        tree.insert(10);
        tree += 20;
        tree += 30;
        assert(tree.toString() == "10 20 30 ");
        log("Test Insert and += Operator: Passed");

        assert(tree.search(20) == true);
        assert(tree[30] == true);
        assert(tree.search(40) == false);
        assert(tree[50] == false);
        log("Test Search and [] Operator: Passed");

        tree.remove(20);
        assert(tree.toString() == "10 30 ");
        tree -= 10;
        assert(tree.toString() == "30 ");
        log("Test Remove and -= Operator: Passed");

        --tree;
        assert(tree.toString() == "");
        log("Test Singular Delete (-- Operator): Passed");

        tree += 40;
        tree += 50;
        AVLTree treeCopy = tree;
        assert(treeCopy.toString() == "40 50 ");
        log("Test Copy Constructor: Passed");

        AVLTree tree2;
        tree2 += 40;
        tree2 += 50;
        assert(tree == tree2);
        tree2 += 60;
        assert(tree != tree2);
        log("Test Equality and Inequality Operators: Passed");

        !tree;
        assert(tree.toString() == "");
        log("Test Free Memory (! Operator): Passed");

        tree2.inOrder();
        log("Test In-Order Traversal: Passed");

        AVLTree treeMoved = std::move(tree2);
        assert(treeMoved.toString() == "40 50 60 ");
        assert(tree2.toString() == "");
        log("Test Move Constructor: Passed");

        AVLTree treeAssigned;
        treeAssigned = std::move(treeMoved);
        assert(treeAssigned.toString() == "40 50 60 ");
        assert(treeMoved.toString() == "");
        log("Test Move Assignment Operator: Passed");

        // Additional operator tests
        AVLTree tree1, tree3;

        // Test += operator
        tree1 += 10;
        tree1 += 20;
        tree1 += 30;
        assert(tree1.toString() == "10 20 30 ");
        log("Test += Operator: Passed");

        // Test -= operator
        tree1 -= 20;
        assert(tree1.toString() == "10 30 ");
        log("Test -= Operator: Passed");

        // Test == and != operators
        tree3 += 10;
        tree3 += 30;
        assert(tree1 == tree3);
        tree3 += 40;
        assert(tree1 != tree3);
        log("Test == and != Operators: Passed");

        // Test > and < operators
        tree1 += 50;
        assert(tree1 > tree3);  // tree1 has more elements
        assert(tree3 < tree1);  // tree3 has fewer elements
        log("Test > and < Operators: Passed");

        // Test >= and <= operators
        tree3 += 50;
        assert(tree1 >= tree3); // tree1 and tree3 have the same size
        assert(tree3 <= tree1); // tree3 and tree1 have the same size
        tree3 += 60;
        assert(tree3 >= tree1); // tree3 has more elements
        assert(tree1 <= tree3); // tree1 has fewer elements
        log("Test >= and <= Operators: Passed");

        log("All tests passed successfully!");
    } catch (const exception& e) {
        cerr << "Unhandled exception: " << e.what() << endl;
        logFile << "Unhandled exception: " << e.what() << endl;
        return 1;
    } catch (...) {
        cerr << "Unknown error occurred." << endl;
        logFile << "Unknown error occurred." << endl;
        return 1;
    }

    logFile.close();
    return 0;
}