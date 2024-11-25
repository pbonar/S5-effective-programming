#include <iostream>
#include <sstream>
#include <stack>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
#include "CTree.h"
#include "CNode.h"

using namespace std;

CTree::CTree() : root(nullptr) {}

CTree::CTree(string formula) : root(nullptr) {
    enter(formula);
}

CTree::~CTree() {
    deleteTree(root);
}

void CTree::deleteTree(CNode* node) {
    if (node) {
        deleteTree(node->getLeft());
        deleteTree(node->getRight());
        delete node;
    }
}

bool CTree::isOperator(const string& s) const {
    return (s == "+" || s == "-" || s == "*" || s == "/" || s == "sin" || s == "cos");
}

bool CTree::isNumber(const string& s) const {
    for (size_t i = 0; i < s.size(); ++i) {
        if (!isdigit(s[i]) && s[i] != '.') return false;
    }
    return true;
}

bool CTree::isVariable(const string& s) const {
    return !s.empty() && isalpha(s[0]);
}

void CTree::enter(string formula) {
    stringstream ss(formula);
    stack<CNode*> nodeStack;
    string token;

    ss >> token;
    root = new CNode(token);
    variables.clear();
    nodeStack.push(root);

    while (ss >> token) {
        CNode* node = new CNode(token);

        while (!nodeStack.empty() && !nodeStack.top()->addChild(node)) {
            nodeStack.pop();
        }

        if (nodeStack.empty()) {
            cout << "Formula too long. Resulting tree: ";
            printPreorder(root);
            cout << endl;
            return;
        }

        if (isVariable(token)) {
            if (find(variables.begin(), variables.end(), token) == variables.end()) {
                variables.push_back(token);
            }
        }

        nodeStack.push(node);
    }

    while (!nodeStack.empty()) {
        while (!nodeStack.top()->isFull()) {
            nodeStack.top()->addChild(new CNode("1"));
        }
        nodeStack.pop();
    }

    cout << "Final equation: ";
    printPreorder(root);
    cout << endl;
}

void CTree::printTree() const {
    printPreorder(root);
    cout << endl;
}

void CTree::printPreorder(CNode* node) const {
    if (node) {
        cout << node->getValue() << " ";
        printPreorder(node->getLeft());
        printPreorder(node->getRight());
    }
}

double CTree::compute(const vector<double>& values) const {
    if (values.size() > variables.size()) cout << "Too many values. Few arent going to be used."<< endl;
    else if (values.size() < variables.size()) cout << "To little values. The missing ones will be replaced by 1." << endl;
    return computeHelper(root, values);
}

double CTree::computeHelper(CNode* node, const vector<double>& values) const {
    if (!node) return 0;

    string value = node->getValue();

    if (isNumber(value)) return stod(value);

    if (isVariable(value)) {
        vector<string>::const_iterator it = find(variables.begin(), variables.end(), value);
        if (it != variables.end()) {
            size_t index = distance(variables.begin(), it);
            return values[index];
        }
        return 1;
    }

    if (value == "+") return computeHelper(node->getLeft(), values) + computeHelper(node->getRight(), values);
    if (value == "-") return computeHelper(node->getLeft(), values) - computeHelper(node->getRight(), values);
    if (value == "*") return computeHelper(node->getLeft(), values) * computeHelper(node->getRight(), values);
    if (value == "/") return computeHelper(node->getLeft(), values) / computeHelper(node->getRight(), values);
    if (value == "sin") return sin(computeHelper(node->getLeft(), values));
    if (value == "cos") return cos(computeHelper(node->getLeft(), values));

    return 1;
}

void CTree::vars() {
    if (variables.empty()) {
        cout << "No variables\n";
        return;
    }
    cout << "Variables: ";
    for (size_t i = 0; i < variables.size(); ++i) {
        cout << variables[i] << " ";
    }
    cout << endl;
}

void CTree::join(string formula) {
    CTree newTree(formula);
    if (!root) {
        cout << "First tree is empty, no leafes to connect.\n";
        return;
    }
    if (!newTree.root) {
        cout << "Second tree is empty, no leafes to join.\n";
        return;
    }

    CTree new_ctree = *this + newTree;

    if (!new_ctree.root) {
        cout << "Failed to join trees.\n";
        return;
    }

    *this = new_ctree;
    cout << "Modified equasion: ";
    printTree();
}

CNode* CTree::copyTree(CNode* node) const {
    if (!node) return nullptr;

    CNode* newNode = new CNode(node->getValue());
    newNode->setType(node->getType());
    newNode->setLeft(copyTree(node->getLeft()));
    newNode->setRight(copyTree(node->getRight()));

    return newNode;
}

CNode* CTree::findLeaf(CNode* node) const {
    if (!node) return nullptr;

    if (!node->getLeft() && !node->getRight()) {
        return node;
    }

    CNode* leaf1 = findLeaf(node->getRight());
    if (leaf1) return leaf1;
    return findLeaf(node->getLeft());
}

void CTree::replaceLeafWithRoot(CNode* leafNode, CNode* newRoot) {
    if (leafNode == root) {
        deleteTree(root);
        root = newRoot;
        return;
    }

    CNode* parent = findParent(root, leafNode);
    if (!parent) {
        cout << "Cant find the leafs parrent\n";
        return;
    }

    if (parent->getLeft() == leafNode) {
        parent->setLeft(newRoot);
    } else {
        parent->setRight(newRoot);
    }
}

CNode* CTree::findParent(CNode* parent, CNode* childNode) const {
    if (!parent) return nullptr;

    if (parent->getLeft() == childNode || parent->getRight() == childNode) {
        return parent;
    }

    CNode* left_parent = findParent(parent->getLeft(), childNode);
    if (left_parent) return left_parent;

    return findParent(parent->getRight(), childNode);
}

CTree CTree::operator+(const CTree& other) const {
    CTree result;
    result.root = copyTree(root);

    result.variables.insert(result.variables.end(), variables.begin(), variables.end());

    CNode* leafNode = result.findLeaf(result.root);
    if (leafNode) {
        CNode* copiedRoot = copyTree(other.root);
        result.replaceLeafWithRoot(leafNode, copiedRoot);
        if (leafNode->getType() == 2) {
            result.variables.erase(remove(result.variables.begin(), result.variables.end(), leafNode->getValue()), result.variables.end());
        }
    } else {
        cout << "No leaf node found" << endl;
    }

    result.variables.insert(result.variables.end(), other.variables.begin(), other.variables.end());

    sort(result.variables.begin(), result.variables.end());
    result.variables.erase(unique(result.variables.begin(), result.variables.end()), result.variables.end());

    return result;
}

CTree& CTree::operator=(const CTree& other) {
    if (this != &other) {
        deleteTree(root);
        root = copyTree(other.root);
        variables = other.variables;
    }
    return *this;
}
