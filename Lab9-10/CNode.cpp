#include "CNode.h"
#include <iostream>

const string REPAIR_VALUE = "1";  
const string ADD_OP = "+";  
const string SUB_OP = "-";  
const string MUL_OP = "*";  
const string DIV_OP = "/";  
const string SIN_FUNC = "sin";  
const string COS_FUNC = "cos";  
const int VALID_EXPRESSION_ARRAY_LENGTH = 6;  
const string MSG_REPAIR_VALUE = "Value had to be repaired because of disallowed string";

const string VALID_EXPRESSION_ARRAY[] = {ADD_OP, SUB_OP, MUL_OP, DIV_OP, SIN_FUNC, COS_FUNC};

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
            if (!isdigit(value.at(i))) {
                type = 2;
                if (!value.empty() && isalpha(value[0])) {
                } else {
                    // cout << MSG_REPAIR_VALUE << endl;
                    value = REPAIR_VALUE;
                }
                return;
            }
        }
        type = 1;
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
        else if (right == nullptr && value != SIN_FUNC && value != COS_FUNC) {
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
