#include "AVL_TREE.h"
#include <cassert>
#include <iostream>
#include <fstream>

using namespace std;
using namespace AVLProject;

ofstream logFile("log.txt");

void log(const string& message) {
    cout << message << endl;
    logFile << message << endl;
}

void testConstructor() {
    AVLTree tree;
    assert(tree.toString() == "");
    log("Test 1: Constructor - PASSED");
}

void testInsertAndPlusEquals() {
    AVLTree tree;
    tree.insert(10);
    tree += 20;
    tree += 30;
    assert(tree.toString() == "10 20 30 ");
    log("Test 2: Insert and += Operator - PASSED");
}

void testSearchAndSubscriptOperator() {
    AVLTree tree;
    tree += 10;
    tree += 20;
    tree += 30;
    assert(tree.search(20) == true);
    assert(tree[30] == true);
    assert(tree.search(40) == false);
    assert(tree[50] == false);
    log("Test 3: Search and [] Operator - PASSED");
}

void testRemoveAndMinusEquals() {
    AVLTree tree;
    tree += 10;
    tree += 20;
    tree += 30;
    tree.remove(20);
    assert(tree.toString() == "10 30 ");
    tree -= 10;
    assert(tree.toString() == "30 ");
    log("Test 4: Remove and -= Operator - PASSED");
}

void testSingularDelete() {
    AVLTree tree;
    tree += 10;
    tree += 20;
    --tree;
    assert(tree.toString() == "20 ");
    --tree;
    assert(tree.toString() == "");
    log("Test 5: Singular Delete (-- Operator) - PASSED");
}

void testMoveConstructor() {
    AVLTree tree;
    tree += 10;
    tree += 20;

    AVLTree movedTree = std::move(tree);
    assert(movedTree.toString() == "10 20 ");
    assert(tree.toString() == "");
    log("Test 6: Move Constructor - PASSED");
}

void testEqualityAndInequalityOperators() {
    AVLTree tree1, tree2;
    tree1 += 10;
    tree1 += 20;
    tree2 += 10;
    tree2 += 20;
    assert(tree1 == tree2);
    tree2 += 30;
    assert(tree1 != tree2);
    log("Test 7: Equality and Inequality Operators - PASSED");
}

void testFreeMemory() {
    AVLTree tree;
    tree += 10;
    tree += 20;
    !tree;
    assert(tree.toString() == "");
    log("Test 8: Free Memory (! Operator) - PASSED");
}

void testComparisonOperators() {
    AVLTree tree1, tree2;
    tree1 += 10;
    tree1 += 20;
    tree2 += 10;
    tree2 += 20;
    tree2 += 30;
    assert(tree1 < tree2);
    assert(tree2 > tree1);
    assert(tree1 <= tree2);
    assert(tree2 >= tree1);
    log("Test 9: Comparison Operators - PASSED");
}

void testMoveConstructorAndAssignment() {
    AVLTree tree1;
    tree1 += 10;
    tree1 += 20;

    AVLTree tree2 = std::move(tree1);
    assert(tree2.toString() == "10 20 ");
    assert(tree1.toString() == "");

    AVLTree tree3;
    tree3 += 30;
    tree3 = std::move(tree2);
    assert(tree3.toString() == "10 20 ");
    assert(tree2.toString() == "");
    log("Test 10: Move Constructor and Assignment - PASSED");
}

void testDuplicateValue() {
    AVLTree tree;
    tree.insert(10);
    tree.insert(20);
    try {
        tree.insert(10);
        assert(false);
    } catch (const std::logic_error& e) {
        assert(std::string(e.what()) == "Duplicate value detected: 10.000000");
    }
    log("Test 11: Duplicate Value - PASSED");
}

void runTests() {
    testConstructor();
    testInsertAndPlusEquals();
    testSearchAndSubscriptOperator();
    testRemoveAndMinusEquals();
    testSingularDelete();
    testMoveConstructor();
    testEqualityAndInequalityOperators();
    testFreeMemory();
    testComparisonOperators();
    testMoveConstructorAndAssignment();
    testDuplicateValue();
    log("All tests completed successfully.");
}

int main() {
    if (!logFile.is_open()) {
        cerr << "Error: Could not open log.txt for writing." << endl;
        return 1;
    }

    try {
        runTests();
    } catch (const exception& e) {
        cerr << "Test failed: " << e.what() << endl;
        logFile << "Test failed: " << e.what() << endl;
        return 1;
    } catch (...) {
        cerr << "Test failed: Unknown exception." << endl;
        logFile << "Test failed: Unknown exception." << endl;
        return 1;
    }

    logFile.close();
    return 0;
}