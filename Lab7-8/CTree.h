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

    bool isOperator(const string& s) const;
    bool isNumber(const string& s) const;
    bool isVariable(const string& s) const;

    void printPreorder(CNode* node) const;
    double computeHelper(CNode* node, const vector<double>& values) const;
    CNode* copyTree(CNode* node) const;
    CNode* findLeaf(CNode* node) const;
    void replaceLeafWithRoot(CNode* leafNode, CNode* newRoot);
    CNode* findParent(CNode* parent, CNode* childNode) const;

    void deleteTree(CNode* node);

public:
    CTree();
    CTree(string formula);
    ~CTree();

    void printTree() const;

    void enter(string formula);
    double compute(const vector<double>& values) const;
    void vars();
    void join(string formula);

    CTree operator+(const CTree& other) const;
    CTree& operator=(const CTree& other);
};

#endif