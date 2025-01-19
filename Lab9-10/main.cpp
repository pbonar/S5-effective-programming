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
    CMySmartPointer<std::string> sp1(new std::string("Hello, World!"));
    std::cout << "Initial value (sp1): " << *sp1 << std::endl;

    CMySmartPointer<std::string> sp2 = sp1;
    std::cout << "Value after copy (sp2): " << *sp2 << std::endl;

    *sp2 = "Modified String!";
    std::cout << "Modified value (sp1): " << *sp1 << std::endl;
    std::cout << "Modified value (sp2): " << *sp2 << std::endl;

    CMySmartPointer<std::string> sp3(new std::string("Another String"));
    std::cout << "Initial value (sp3): " << *sp3 << std::endl;
    sp3 = sp1;
    std::cout << "Value after assignment (sp3): " << *sp3 << std::endl;
    return 0;
}
