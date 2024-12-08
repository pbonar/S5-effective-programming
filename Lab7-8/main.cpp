#include <iostream>
#include "CResult.h"
#include "CError.h"
#include "../Lab5-6/CNode.h"
#include "../Lab5-6/CTree.h"

using namespace std;

CResult<double, CError> eDivide(double dDividend, double dDivisor)
{
    if (dDivisor == 0) {
        return CResult<double, CError>::fail(CError("cannot divide by zero"));
    }
    return CResult<double, CError>::ok(dDividend / dDivisor);
}

int main()
{
    CResult<double, CError> result = eDivide(10, 2);
    if (result.isSuccess())
    {
        std::cout << "Result: " << result.getValue() << std::endl;
    }
    else
    {
        size_t numErrors = result.getErrors().size();
        for (size_t i = 0; i < numErrors; ++i)
        {
            std::cout << "Error: " << result.getErrors()[i].getErrorMessage() << std::endl;
        }
    }

    result = eDivide(10, 0);
    if (result.isSuccess())
    {
        std::cout << "Result: " << result.getValue() << std::endl;
    }
    else
    {
        size_t numErrors = result.getErrors().size();
        for (size_t i = 0; i < numErrors; ++i)
        {
            std::cout << "Error: " << result.getErrors()[i].getErrorMessage() << std::endl;
        }
    }

    std::cout << "Welcome to the Expression Tree Builder!\n";

    while (true) {
        std::cout << "\nEnter a mathematical formula (or type 'exit' to quit): ";
        std::string formula;
        std::getline(std::cin, formula);

        if (formula == "exit") {
            break;
        }

        cout << "lollo" << endl;
        CTree* tree = new CTree(formula);
        CResult<CTree, CError> result2 = *tree;
        cout << "lollo" << endl;

        if (result2.isSuccess()) {
            std::cout << "\nTree successfully created! Here's the pre-order traversal:\n";
            result2.getValue().printTree();
        } else {
            std::cout << "\nError: Failed to create the tree. Details:\n";
            const std::vector<CError>& errors = result2.getErrors();
            for (size_t i = 0; i < errors.size(); ++i) {
                std::cout << " - " << errors[i].getErrorMessage() << std::endl;
            }
        }
    }
    return 0;
}
