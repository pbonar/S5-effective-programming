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
        // Szukamy zmiennej w wektorze 'variables'
        vector<string>::const_iterator it = find(variables.begin(), variables.end(), value);
        if (it != variables.end()) {
            // Jeśli zmienna została znaleziona, pobieramy jej wartość z 'values'
            size_t index = distance(variables.begin(), it);
            return values[index];
        }
        // Jeśli zmienna nie została znaleziona, zwracamy 0 (lub można rzucić wyjątek)
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
    *this = *this + newTree;
    cout << "Modified tree: ";
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

    CNode* CTree::findLeafNode(CNode* node) const {
        if (!node) return nullptr;

        if (!node->getLeft() && !node->getRight()) {
            return node;
        }

        CNode* leaf1 = findLeafNode(node->getRight());
        if (leaf1) return leaf1;
        CNode* leaf2 = findLeafNode(node->getLeft());
        if (leaf2) return leaf2;

        return nullptr;
    }

    void CTree::replaceLeafNodeWithRoot(CNode* leafNode, CNode* newRoot) {

        if(leafNode == root)
        {
            delete root;
            root = newRoot;
            return;
        }

        CNode* parent = findParent(root, leafNode);
        if (!parent) {
            return;
        }

        if (parent->getLeft() == leafNode) {
            parent->setLeft(newRoot);
        } else {
            parent->setRight(newRoot);
        }
        return;
    }

    CNode* CTree::findParent(CNode* parent, CNode* childNode) const {
        if (!parent) return nullptr;

        if (parent->getLeft() == childNode || parent->getRight()) {
            return parent;
        } else {
            CNode* left_parent = findParent(parent->getLeft(), childNode);
            CNode* right_parent = findParent(parent->getRight(), childNode);
            if (left_parent) return left_parent;
            else if (right_parent) return right_parent;
            else return nullptr;
        }
    }

CTree CTree::operator+(const CTree& other) const {
    CTree result;
    result.root = copyTree(root);

    CNode* leafNode = result.findLeafNode(result.root);
    if (leafNode) {
        CNode* copiedRoot = copyTree(other.root);
        result.replaceLeafNodeWithRoot(leafNode, copiedRoot);
    } else {
        cout << "Error: No leaf node found in Tree A for substitution.\n";
    }

    return result;
}

CTree& CTree::operator=(const CTree& other) {
    if (this != &other) { 
        delete root;
        if (other.root) {
            root = new CNode(*other.root);
        } 
        else {
            root = NULL;
        }
    }
    return *this; 
}
