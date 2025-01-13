#include <iostream>
#include <sstream>
#include <stack>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
#include "CTree.h"
#include "CNode.h"
#include "CResult.h"
#include "CError.h"

using namespace std;

// Stałe komunikatów
const string MSG_FORMULA_TOO_LONG = "Formula too long. ";
const string MSG_TOO_LITTLE_VALUES = "Too little values. ";
const string MSG_NO_VARIABLES = "No variables";
const string MSG_VARIABLES = "Variables: ";

// Stałe operatorów
const string OPERATOR_PLUS = "+";
const string OPERATOR_MINUS = "-";
const string OPERATOR_MULTIPLY = "*";
const string OPERATOR_DIVIDE = "/";
const string OPERATOR_SIN = "sin";
const string OPERATOR_COS = "cos";

CTree::CTree() : root(nullptr) {}

CTree::CTree(string formula) : root(nullptr) {
    enter(formula);
}

// Konstruktor kopiujacy
CTree::CTree(const CTree& other) : root(nullptr), variables(other.variables) {
    root = copyTree(other.root);
}

// Konstruktor przenoszacy
CTree::CTree(CTree&& other) : root(other.root), variables(std::move(other.variables)) {
    other.root = nullptr;
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
    return (s == OPERATOR_PLUS || s == OPERATOR_MINUS || s == OPERATOR_MULTIPLY || s == OPERATOR_DIVIDE || s == OPERATOR_SIN || s == OPERATOR_COS);
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

CResult<CTree*, CError> CTree::enter(string formula) {
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
            return CResult<CTree*, CError>().fail(MSG_FORMULA_TOO_LONG);
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
            return CResult<CTree*, CError>().fail(MSG_TOO_LITTLE_VALUES);
        }
        nodeStack.pop();
    }
    return CResult<CTree*, CError>().ok(this);
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

string CTree::getTree() {
    return getPreorder(root);
}

string CTree::getPreorder(CNode* node) {
    if (node) {
        string toReturn = node->getValue() + " ";
        toReturn += getPreorder(node->getLeft());
        toReturn += getPreorder(node->getRight());
        return toReturn;
    }
    return "";
}


double CTree::compute(const vector<double>& values) const {
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

    if (value == OPERATOR_PLUS) return computeHelper(node->getLeft(), values) + computeHelper(node->getRight(), values);
    if (value == OPERATOR_MINUS) return computeHelper(node->getLeft(), values) - computeHelper(node->getRight(), values);
    if (value == OPERATOR_MULTIPLY) return computeHelper(node->getLeft(), values) * computeHelper(node->getRight(), values);
    if (value == OPERATOR_DIVIDE) return computeHelper(node->getLeft(), values) / computeHelper(node->getRight(), values);
    if (value == OPERATOR_SIN) return sin(computeHelper(node->getLeft(), values));
    if (value == OPERATOR_COS) return cos(computeHelper(node->getLeft(), values));

    return 1;
}

void CTree::vars() {
    if (variables.empty()) {
        cout << MSG_NO_VARIABLES << endl;
        return;
    }
    cout << MSG_VARIABLES;
    for (size_t i = 0; i < variables.size(); ++i) {
        cout << variables[i] << " ";
    }
    cout << endl;
}

void CTree::join(string formula) {
    CTree newTree(formula);
    if (!root) {
        return;
    }
    if (!newTree.root) {
        return;
    }

    CTree new_ctree = *this + newTree;

    if (!new_ctree.root) {
        return;
    }

    *this = new_ctree;
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
    }

    result.variables.insert(result.variables.end(), other.variables.begin(), other.variables.end());

    sort(result.variables.begin(), result.variables.end());
    result.variables.erase(unique(result.variables.begin(), result.variables.end()), result.variables.end());

    return result;
}

// operator przypisywania kopiujacy
CTree& CTree::operator=(const CTree& other) {
    if (this != &other) {
        deleteTree(root);
        root = copyTree(other.root);
        variables = other.variables;
    }
    return *this;
}

//operator przypisywania przenoszacy
CTree& CTree::operator=(CTree&& other) {
    if (this != &other) {
        deleteTree(root);
        root = other.root;
        variables = std::move(other.variables);
        other.root = nullptr;
        other.variables.clear();
    }
    return *this;
}

