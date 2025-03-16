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

        cout << "Tree1: " << tree1 << endl;

        cout << "Search for 25: " << (tree1[25] ? "Found" : "Not Found") << endl;
        cout << "Search for 15: " << (tree1[15] ? "Found" : "Not Found") << endl;

        tree1 -= 30;
        cout << "Tree1 after removing 30: " << tree1 << endl;

        --tree1;
        cout << "Tree1 after deleting the root: " << tree1 << endl;

        AVLTree tree2 = tree1;
        cout << "Tree1 == Tree2: " << (tree1 == tree2 ? "True" : "False") << endl;

        tree2.remove(40);
        cout << "Tree2 after removing 40: " << tree2 << endl;

        !tree1;
        cout << "Tree1 after freeing memory: " << tree1 << endl;

        try {
            tree1 += 10;
            tree1 += 10;
        } catch (const logic_error& e) {
            cerr << "Caught exception: " << e.what() << endl;
        }

        AVLTree tree3;
        tree3 += 10;
        tree3 += 30;
        tree3 += 40;

        cout << "Tree1 > Tree3: " << (tree1 > tree3 ? "True" : "False") << endl;
        cout << "Tree3 < Tree1: " << (tree3 < tree1 ? "True" : "False") << endl;

    } catch (const exception& e) {
        cerr << "Unhandled exception: " << e.what() << endl;
        return 1;
    } catch (...) {
        cerr << "Unhandled unknown exception occurred." << endl;
        return 1;
    }
    cout << "Program completed successfully." << endl;

    return 0;
}
