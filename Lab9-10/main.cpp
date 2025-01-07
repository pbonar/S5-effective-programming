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
    // Dodawanie przykładowych wartości do drzewa 1 i 2
    // (implementacja metod dodających węzły zależy od szczegółów klasy)

    // Test operatora przypisania przenoszącego
    CTree tree3 = std::move(tree1);

    // Test operatora +
    CTree tree4 = tree2 + tree3;

    // Wyświetlenie zmiennych drzewa wynikowego
    tree1.printTree();
    tree2.printTree();
    tree3.printTree();
    tree4.printTree();

    return 0;
}
