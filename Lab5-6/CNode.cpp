#include "CNode.h"
#include <iostream>

CNode::CNode(string value) : value(value), left(nullptr), right(nullptr) {
    bool is_done = false;
    for (int i = 0; i < VALID_EXPRESSION_ARRAY_LENGTH; i++) {
        if (VALID_EXPRESSION_ARRAY[i] == value) {
            type = 0;
            is_done = true;
            return;
        }
    }
    if (!is_done) {
        for (int i = 0; i < value.length(); i++) {
            // cout << value.at(i) << " " << !isdigit(value.at(i)) << " " << value.length() << endl;;
            if (!isdigit(value.at(i))) {
                type = 2;
                if (!value.empty() && isalpha(value[0])) {
                } else {
                    cout << "Value had to be repaired because of disallowed string" << endl;
                    value = REPAIR_VALUE;
                }
                return;
            }
        }
        type = 1;;
    }
}

void CNode::setLeft(CNode* leftNode) {
    if (type == 0)
        left = leftNode;
}

void CNode::setRight(CNode* rightNode) {
    if (type == 0)
        right = rightNode;
}

void CNode::setValue(string new_value) {
    value = new_value;   
}

void CNode::setType(int new_type) {
    type = new_type;   
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

int CNode::getType() const {
    return type;
}

string CNode::toString() {
    string to_return = value;
    if (left != nullptr) to_return += " " + left->toString();
    if (right != nullptr) to_return += " " + right->toString();
    return to_return;
}

bool CNode::addChild(CNode* child) {
    if (type == 0) {
        if (left == nullptr) {
            left = child;
            return true;
        }
        else if (right == nullptr && value != "sin" && value != "cos") {
            right = child;
            return true;
        } else {
            return false;
        }
    }
    else {
        return false;
    }
}

bool CNode::isFull() {
    if (type == 0) {
        return right != nullptr && left != nullptr;
    }
    else {
        return true;
    }
}