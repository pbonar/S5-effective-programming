#include <iostream>
#include <sstream>
#include <stack>
#include <vector>
#include <string>
#include <cmath>
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
    for (string::size_type i = 0; i < s.length(); ++i) {
        char c = s[i];
        if (!isdigit(c) && c != '.') {
            return false;
        }
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

    nodeStack.push(root);

    while (ss >> token) {
        CNode* node = new CNode(token);

        while (nodeStack.size() != 0 && !nodeStack.top()->addChild(node)) {
            nodeStack.pop();
        }
        
        if (nodeStack.size() == 0) {
            cout << "We had to end earlier because of the fact that formula was too long. New formula:   ";
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

    while (nodeStack.size() != 0) {
        while (!nodeStack.top()->isFull())
            nodeStack.top()->addChild(new CNode("1"));
        nodeStack.pop();
    }
    cout << "Final equasion: ";
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
    return computeHelper(root, values);
}

double CTree::computeHelper(CNode* node, const vector<double>& values) const {
    if (node == nullptr) {
        return 0;
    }

    string value = node->getValue();

    // Jeśli to liczba
    if (isNumber(value)) {
        return stod(value);
    }

    // Jeśli to zmienna
    if (isVariable(value)) {
        if (value == "x") return values[0];
        if (value == "y") return values[1];
        return 0;
    }

    // Jeśli to operator
    if (value == "+") {
        return computeHelper(node->getLeft(), values) + computeHelper(node->getRight(), values);
    } else if (value == "-") {
        return computeHelper(node->getLeft(), values) - computeHelper(node->getRight(), values);
    } else if (value == "*") {
        return computeHelper(node->getLeft(), values) * computeHelper(node->getRight(), values);
    } else if (value == "/") {
        return computeHelper(node->getLeft(), values) / computeHelper(node->getRight(), values);
    } else if (value == "sin") {
        return sin(computeHelper(node->getLeft(), values));
    } else if (value == "cos") {
        return cos(computeHelper(node->getLeft(), values));
    }
    return 0;
}

void CTree::vars() {
    if (variables.size() == 0) {
        cout << "No variables\n";
        return;
    }
    cout << "Variables: ";
    for (int i = 0; i < variables.size(); i++) {
        cout << variables[i] << " ";
    }
    cout << endl;
}

void CTree::join(string formula) {
    CTree newTree(formula);
    if (root == nullptr) {
        cout << "Tree A is empty, nothing to join with Tree B.\n";
        return;
    }
    if (newTree.root == nullptr) {
        cout << "Tree B is empty, nothing to join.\n";
        return;
    }
    // *this = *this + newTree;
    cout << "Modified tree: ";
    printTree();
}

CNode* CTree::findLeafNodeParent(CNode* node) {
    CNode* current = node;
    while (current->getType() != 1 && current->getLeft()->getLeft() != nullptr) {
        current = current->getLeft();
        if (current == nullptr) {
            return nullptr;
        }
    }
    return current;
}

void CTree::replaceLeafWithRoot(CNode* leaf_node, CNode* new_root) {
    if (new_root != nullptr)
        leaf_node->setLeft(new_root);
    else cout << "Error: unable to join a nullptr"<<endl;
}

CTree CTree::operator+(const CTree& other) {
    CTree result(*this);
    CNode* leafNode = findLeafNodeParent(result.root);
    if (leafNode) {
        CNode* copiedRoot = new CNode(*other.root);
        result.replaceLeafWithRoot(leafNode, copiedRoot);
    } else {
        cout << "Error: No leaf node found in Tree A for substitution.\n";
    }
    return result;
    }
    
CTree* CTree::operator=(const CTree& other) {
    if (this != &other) { 
        delete root;
        if (other.root) {
            root = new CNode(*other.root);
        } 
        else {
            root = NULL;
        }
    }
    return this; 
}