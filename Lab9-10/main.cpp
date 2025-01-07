#include <iostream>
#include <fstream>
#include "CResult.h"
#include "CError.h"
#include "CNode.h"
#include "CTree.h"
#include "CResultSaver.h"

using namespace std;

const string DIVIDE_RESULT_FILE = "divide_result.txt";
const string TREE_RESULT_FILE = "tree_result.txt";
const string CANNOT_DIVIDE_ERROR = "cannot divide by zero";
const string EXIT_COMMAND = "exit";
const string WELCOME_MESSAGE = "Welcome to the Expression Tree Builder!";
const string INPUT_PROMPT = "\nEnter a mathematical formula (or type 'exit' to quit): ";
const string TREE_CREATED_MESSAGE = "\nTree successfully created! Here's the pre-order traversal\n";
const string TREE_SAVE_SUCCESS_MESSAGE = "Tree successfully saved to file: ";
const string TREE_SAVE_FAILURE_MESSAGE = "Failed to save tree: ";
const string TREE_CREATION_ERROR = "\nError: Failed to create the tree. Details:\n";
const string NUMBER_OF_FAILURES_MESSAGE = "Number of fails: ";
const string RESULT_SAVE_SUCCESS_MESSAGE = "Result successfully saved to file: ";
const string RESULT_SAVE_FAILURE_MESSAGE = "Failed to save result: ";
const string ERROR_PREFIX = "Error: ";
const string RESULT_PREFIX = "Result: ";

CResult<double, CError> eDivide(double dDividend, double dDivisor)
{
    if (dDivisor == 0) {
        return CResult<double, CError>::fail(CError(CANNOT_DIVIDE_ERROR));
    }
    return CResult<double, CError>::ok(dDividend / dDivisor);
}

int main()
{
    CResult<double, CError> result = eDivide(10, 2);
    if (result.isSuccess())
    {
        cout << RESULT_PREFIX << result.getValue() << endl;
        CResult<string, CError> saveResult = CResultSaver<double>::saveToFile(DIVIDE_RESULT_FILE, result);
        if (saveResult.isSuccess()) {
            cout << RESULT_SAVE_SUCCESS_MESSAGE << saveResult.getValue() << endl;
        } else {
            cout << RESULT_SAVE_FAILURE_MESSAGE << saveResult.getErrors()[0].getErrorMessage() << endl;
        }
    }
    else
    {
        size_t numErrors = result.getErrors().size();
        for (size_t i = 0; i < numErrors; ++i)
        {
            cout << ERROR_PREFIX << result.getErrors()[i].getErrorMessage() << endl;
        }
    }

    result = eDivide(10, 0);
    if (result.isSuccess())
    {
        cout << RESULT_PREFIX << result.getValue() << endl;
    }
    else
    {
        size_t numErrors = result.getErrors().size();
        for (size_t i = 0; i < numErrors; ++i)
        {
            cout << ERROR_PREFIX << result.getErrors()[i].getErrorMessage() << endl;
        }
    }

    cout << WELCOME_MESSAGE << "\n";

    while (true) {
        cout << INPUT_PROMPT;
        string formula;
        getline(cin, formula);

        if (formula == EXIT_COMMAND) {
            break;
        }

        CResult<CTree*, CError>* result2 = new CResult<CTree*, CError>();
        *result2 = CTree().enter(formula);

        if (result2->isSuccess()) {
            cout << TREE_CREATED_MESSAGE;
            result2->getValue()->printTree();

            CResult<string, CError> saveTreeResult = CResultSaver<CTree*>::saveToFile(TREE_RESULT_FILE, *result2);
            if (saveTreeResult.isSuccess()) {
                cout << TREE_SAVE_SUCCESS_MESSAGE << saveTreeResult.getValue() << endl;
            } else {
                cout << TREE_SAVE_FAILURE_MESSAGE << saveTreeResult.getErrors()[0].getErrorMessage() << endl;
            }

        } else {
            cout << TREE_CREATION_ERROR;
            const vector<CError>& errors = result2->getErrors();
            cout << NUMBER_OF_FAILURES_MESSAGE << errors.size() << endl;
            for (size_t i = 0; i < errors.size(); ++i) {
                cout << " - " << errors[i].getErrorMessage() << endl;
            }
            CResult<string, CError> saveTreeResult = CResultSaver<CTree*>::saveToFile(TREE_RESULT_FILE, *result2);
            if (saveTreeResult.isSuccess()) {
                cout << TREE_SAVE_SUCCESS_MESSAGE << saveTreeResult.getValue() << endl;
            } else {
                cout << TREE_SAVE_FAILURE_MESSAGE << saveTreeResult.getErrors()[0].getErrorMessage() << endl;
            }
        }

        delete result2;
    }

    return 0;
}
