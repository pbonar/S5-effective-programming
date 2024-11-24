#include "CNode.h"
#include <iostream>

CNode::CNode(string value) : value(value), left(nullptr), right(nullptr) {
    bool is_done = false;
    cout << "started creating new node" << endl;
    for (int i = 0; i < VALID_EXPRESSION_ARRAY_LENGTH; i++) {
        if (VALID_EXPRESSION_ARRAY[i] == value) {
            is_number = false;
            is_done = true;
            cout << "new node is an expression" << endl;
            return;
        }
    }
    if (!is_done) {
        for (int i = 0; i < value.length(); i++) {
            cout << value.at(i) << " " << !isdigit(value.at(i)) << " " << value.length() << endl;;
            if (!isdigit(value.at(i))) {
                cout << "repair " << value << " with " << REPAIR_VALUE << endl;
                value = REPAIR_VALUE;
                is_number = true;
                return;
            }
        }
        is_number = true;
        cout << "node with " << value << " has been created" << endl;
    }
}

void CNode::setLeft(CNode* leftNode) {
    if (!is_number)
        left = leftNode;
    else 
        cout << "cant add a child to a number " << value << endl;
}

void CNode::setRight(CNode* rightNode) {
    if (!is_number)
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

bool CNode::getIfNumber() const {
    return is_number;
}

string CNode::toString() {
    string to_return = value;
    if (left != nullptr) to_return += " " + left->toString();
    if (right != nullptr) to_return += " " + right->toString();
    return to_return;
}