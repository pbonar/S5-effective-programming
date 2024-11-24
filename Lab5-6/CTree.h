#ifndef CTREE_H
#define CTREE_H

#include <string>
#include <vector>
#include "CNode.h"

using namespace std;

class CTree {
private:
    CNode* root;
    vector<string> variables;

    // Pomocnicze funkcje
    bool isOperator(const string& s) const;
    bool isNumber(const string& s) const;
    bool isVariable(const string& s) const;

    void enter(string formula);
    void printPreorder(CNode* node) const;
    double computeHelper(CNode* node, const vector<double>& values) const;

    void deleteTree(CNode* node);

public:
    CTree();
    CTree(string formula);
    ~CTree();

    void printTree() const;
    double compute(const vector<double>& values) const;
    void vars();
    void join(string formula);
    CTree operator+(const CTree& other);
    CTree* operator=(const CTree& other);
    CNode* findLeafNodeParent(CNode* node);
    void replaceLeafWithRoot(CNode* leafNode, CNode* newRoot);
};

#endif