#ifndef CPARSER_H
#define CPARSER_H

#include "CTree.h"
#include <string>

using namespace std;

class CParser {
private:
    CTree tree;

public:
    void processCommands();
};

#endif