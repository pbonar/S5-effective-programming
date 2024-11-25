#ifndef CNODE_H
#define CNODE_H

#include <string>

using namespace std;

static const string VALID_EXPRESSION_ARRAY[] = {"sin", "cos", "+", "-", "*", "/"};
static const int VALID_EXPRESSION_ARRAY_LENGTH = 6;
static const string REPAIR_VALUE = "1";

class CNode {
private:
    int type;
    // 0 - expression, 1 - number, 2 - variable
    string value;
    CNode* left;
    CNode* right;

public:
    CNode(string value);

    void setLeft(CNode* leftNode);
    void setRight(CNode* rightNode);
    void setValue(string new_value);
    void setType(int new_type); 
    bool addChild(CNode* child);

    string toString();
    bool isFull();
    
    int getType() const;
    string getValue() const;
    CNode* getLeft() const;
    CNode* getRight() const;  
};

#endif
