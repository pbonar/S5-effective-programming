#include <iostream>
#include <fstream>
#include "CResult.h"
#include "CError.h"
#include "CNode.h"
#include "CTree.h"
#include "CResultSaver.h"
#include "CMySmartPointer.h"

using namespace std;

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

    CMySmartPointer<string>* sp3 = new CMySmartPointer<string>(new string("Another String"));
    cout << "Related pointers : " << sp1.printRelatedPointers() << endl;
    cout << "Initial value (sp3): " << **sp3 << endl;

    **sp3 = *sp1;
    cout << "Value after assignment (sp3): " << **sp3 << endl;
    cout << "Related pointers : " << sp1.printRelatedPointers() << endl;

    delete sp3;
    cout << "Related pointers : " << sp2.printRelatedPointers() << endl;

    cout << endl << "Test of 2 and 2" << endl;
    CMySmartPointer<string> sp4(new string("Test String"));
    cout << "Initial value (sp4): " << *sp4 << endl;
    cout << "Related pointers : " << sp4.printRelatedPointers() << endl;

    CMySmartPointer<string> sp5 = sp4;
    cout << "Value after copy (sp5): " << *sp5 << endl;
    cout << "Related pointers : " << sp5.printRelatedPointers() << endl;

    sp1 = sp4;
    cout << "Value after assignment (sp1): " << *sp1 << endl;
    cout << "Related pointers : " << sp1.printRelatedPointers() << endl;

    return 0;
}
