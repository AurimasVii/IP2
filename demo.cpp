#include "AVL_TREE.h"
#include <iostream>
#include <stdexcept>

using namespace std;
using namespace AVLProject;

int main() {
    try {
        AVLTree tree1;
        tree1 += 10;
        tree1 += 20;
        tree1 += 30;
        tree1 += 40;
        tree1 += 50;
        tree1 += 25;

        cout << "Tree1 using << operator: " << tree1 << endl;
        cout << "Tree1 as string: " << tree1.toString() << endl;

        cout << "Search for 25 in Tree1: " << (tree1[25] ? "Found" : "Not Found") << endl;
        cout << "Search for 15 in Tree1: " << (tree1[15] ? "Found" : "Not Found") << endl;

        tree1 -= 30;
        cout << "Tree1 after removing 30 using -= operator: " << tree1 << endl;
        --tree1;
        cout << "Tree1 after deleting the root using -- operator: " << tree1 << endl;
        cout << "Tree1 as string after operations: " << tree1.toString() << endl;

        AVLTree tree2 = tree1;
        cout << "Tree1 == Tree2: " << (tree1 == tree2 ? "True" : "False") << endl;
        cout << "Tree1 != Tree2: " << (tree1 != tree2 ? "True" : "False") << endl;

        tree2.remove(40);
        cout << "Tree2 after removing 40: " << tree2 << endl;
        cout << "Search for 50 in Tree2: " << (tree2.search(50) ? "Found" : "Not Found") << endl;
        cout << "Tree2 in-order traversal: ";
        tree2.inOrder();
        cout << endl;

        !tree1;
        cout << "Tree1 after freeing memory using ! operator: " << tree1 << endl;

        cout << "Attempting to insert a duplicate value (10) into Tree1..." << endl;
        try {
            tree1 += 10;
            tree1 += 10; 
        } catch (const logic_error& e) {
            cerr << "Caught exception: " << e.what() << endl;
        }

        // Additional operator tests
        AVLTree tree3;

        // Test > and < operators
        tree1 += 50;
        tree3 += 10;
        tree3 += 30;
        tree3 += 40;
        cout << "Tree1 > Tree3: " << (tree1 > tree3 ? "True" : "False") << endl;
        cout << "Tree3 < Tree1: " << (tree3 < tree1 ? "True" : "False") << endl;

        // Test >= and <= operators
        tree3 += 50;
        cout << "Tree1 >= Tree3: " << (tree1 >= tree3 ? "True" : "False") << endl;
        cout << "Tree3 <= Tree1: " << (tree3 <= tree1 ? "True" : "False") << endl;

        tree3 += 60;
        cout << "Tree3 >= Tree1: " << (tree3 >= tree1 ? "True" : "False") << endl;
        cout << "Tree1 <= Tree3: " << (tree1 <= tree3 ? "True" : "False") << endl;

    } catch (const exception& e) {
        cerr << "Unhandled exception: " << e.what() << endl;
        return 1; 
    }

    cout << "Program completed successfully." << endl;
    return 0; 
}
