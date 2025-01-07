#include <iostream>
#include <fstream>
#include "CResult.h"
#include "CError.h"
#include "CNode.h"
#include "CTree.h"
#include "CResultSaver.h"

int main() {
    CTree tree1 = CTree("/ 1 2");

    CTree tree2 = CTree("/ 4 3");

    CTree tree3 = std::move(tree1);

    CTree tree4 = tree2 + tree3;

    cout << "Tree1:   ";
    tree1.printTree();
    cout << "Tree2:   ";
    tree2.printTree();
    cout << "Tree3:   ";
    tree3.printTree();
    cout << "Tree4:   ";
    tree4.printTree();

    return 0;
}
