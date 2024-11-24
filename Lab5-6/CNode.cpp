#include "CNode.h"
#include <iostream>

CNode::CNode(string value) : value(value), left(nullptr), right(nullptr) {
    bool is_done = false;
    cout << "Started creating new node" << endl;
    for (int i = 0; i < VALID_EXPRESSION_ARRAY_LENGTH; i++) {
        if (VALID_EXPRESSION_ARRAY[i] == value) {
            type = 0;
            is_done = true;
            cout << "Its a expression: " << value << endl;
            return;
        }
    }
    if (!is_done) {
        for (int i = 0; i < value.length(); i++) {
            cout << value.at(i) << " " << !isdigit(value.at(i)) << " " << value.length() << endl;;
            if (!isdigit(value.at(i))) {
                cout << "Its a variable: " << value << endl;
                type = 2;
                return;
            }
        }
        type = 1;;
        cout << "Its a value: " << value << endl;
    }
}

void CNode::setLeft(CNode* leftNode) {
    if (type == 0)
        left = leftNode;
    else 
        cout << "cant add a child to a number " << value << endl;
}

void CNode::setRight(CNode* rightNode) {
    if (type == 0)
        right = rightNode;
    else 
        cout << "cant add a child to a number " << value << endl;
}

string CNode::getValue() const {
    return value;
}

CNode* CNode::getLeft() const {
    return left;
}

CNode* CNode::getRight() const {
    return right;
}

bool CNode::getType() const {
    return type;
}

string CNode::toString() {
    string to_return = value;
    if (left != nullptr) to_return += " " + left->toString();
    if (right != nullptr) to_return += " " + right->toString();
    return to_return;
}