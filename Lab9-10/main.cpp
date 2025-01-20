#include <iostream>
#include <fstream>
#include "CResult.h"
#include "CError.h"
#include "CNode.h"
#include "CTree.h"
#include "CResultSaver.h"
#include "CMySmartPointer.h"

int main() {
    CTree tree1 = CTree("/ 1 2");

    CTree tree2 = CTree("/ 4 3");

    CTree tree3 = std::move(tree1);

    CTree tree4 = tree2 + tree3;

    cout << "=== TREE TEST ===" << endl;
    cout << "Tree1:   ";
    tree1.printTree();
    cout << "Tree2:   ";
    tree2.printTree();
    cout << "Tree3:   ";
    tree3.printTree();
    cout << "Tree4:   ";
    tree4.printTree();
    cout << endl;
    

    cout << "=== CMySmartPointer TEST ===" << endl;
    CMySmartPointer<string> sp1(new string("Hello, World!"));
    cout << "Initial value (sp1): " << *sp1 << endl;
    cout << "Related pointers : " << sp1.printRelatedPointers() << endl;

    CMySmartPointer<string> sp2 = sp1;
    cout << "Value after copy (sp2): " << *sp2 << endl;
    cout << "Related pointers : " << sp1.printRelatedPointers() << endl;

    *sp2 = "Modified String!";
    cout << "Modified value (sp1): " << *sp1 << endl;
    cout << "Modified value (sp2): " << *sp2 << endl;

    CMySmartPointer<string> sp3(new string("Another String"));
    cout << "Related pointers : " << sp1.printRelatedPointers() << endl;
    cout << "Initial value (sp3): " << *sp3 << endl;
    sp3 = sp1;
    cout << "Value after assignment (sp3): " << *sp3 << endl;
    cout << "Related pointers : " << sp1.printRelatedPointers() << endl;
    return 0;
}
