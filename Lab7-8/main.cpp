#include <iostream>
#include <fstream>
#include "CResult.h"
#include "CError.h"
#include "CNode.h"
#include "CTree.h"
#include "CResultSaver.h" // Upewnij się, że masz odpowiednią definicję tej klasy

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
    // Test dzielenia
    CResult<double, CError> result = eDivide(10, 2);
    if (result.isSuccess())
    {
        std::cout << "Result: " << result.getValue() << std::endl;
        // Test zapisu do pliku
        CResult<std::string, CError> saveResult = CResultSaver<double>::saveToFile("divide_result.txt", result);
        if (saveResult.isSuccess()) {
            std::cout << "Result successfully saved to file: " << saveResult.getValue() << std::endl;
        } else {
            std::cout << "Failed to save result: " << saveResult.getErrors()[0].getErrorMessage() << std::endl;
        }
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

        CResult<CTree*, CError>* result2 = new CResult<CTree*, CError>();
        *result2 = CTree().enter(formula);

        if (result2->isSuccess()) {
            std::cout << "\nTree successfully created! Here's the pre-order traversal\n";
            // result2->getValue().printTree();

            // Test zapisu drzewa do pliku
            CResult<std::string, CError> saveTreeResult = CResultSaver<CTree*>::saveToFile("tree_result.txt", *result2);
            if (saveTreeResult.isSuccess()) {
                std::cout << "Tree successfully saved to file: " << saveTreeResult.getValue() << std::endl;
            } else {
                std::cout << "Failed to save tree: " << saveTreeResult.getErrors()[0].getErrorMessage() << std::endl;
            }

        } else {
            std::cout << "\nError: Failed to create the tree. Details:\n";
            const std::vector<CError>& errors = result2->getErrors();
            cout << "Number of fails: " << errors.size() << endl;
            for (size_t i = 0; i < errors.size(); ++i) {
                std::cout << " - " << errors[i].getErrorMessage() << std::endl;
            }
        }

        delete result2;  // Pamiętaj o usunięciu dynamicznie alokowanego obiektu
    }

    return 0;
}
