#include <iostream>
#include <vector>
#include "CTree.h"
#include "CNode.h"

using namespace std;

int main() {
    // Przykład formuły: "* + x y x"
    // Ta formuła oznacza (x + y) * x

    cout << "Testy przykladowe:" << endl;
    string formula = "+ / x y 3";
    CNode n("a");
    // Tworzymy drzewo z formuły
    CTree tree(formula);

    // Wyświetlamy drzewo (w formie preorder)
    vector<double> values;
    values.push_back(6);  // x = 5
    values.push_back(3);  // y = 3
    tree.vars();
    double result = tree.compute(values);
    CTree tree2(formula);
    CTree tree4 = tree + tree2;
    tree4.printTree();
    cout << "Wynik obliczenia: " << result << endl;

    return 0;
}
