#include <fstream>
#include <string>
#include <sstream>
#include "CTree.h"
#include "CResult.h"
#include "CError.h"

template <typename T>
class CResultSaver {
public:
    static CResult<std::string, CError> saveToFile(const std::string& filePath, const CResult<T, CError> result) {
        std::ofstream outFile(filePath);

        if (!outFile.is_open()) {
            return CResult<std::string, CError>::fail(CError("Failed to open file: " + filePath));
        }

        if (!result.isSuccess()) {
            const std::vector<CError>& errors = result.getErrors();
            for (size_t i = 0; i < errors.size(); ++i) {
                outFile << "Error: " << errors[i].getErrorMessage() << std::endl;
            }
        } else {
            outFile << "No errors." << std::endl;
        }

        outFile.close();
        return CResult<std::string, CError>::ok(filePath);
    }
};

template <>
class CResultSaver<CTree*> {
public:
    static CResult<std::string, CError> saveToFile(const std::string& filePath, const CResult<CTree*, CError>& result) {
        std::ofstream outFile(filePath);

        if (!outFile.is_open()) {
            return CResult<std::string, CError>::fail(CError("Failed to open file: " + filePath));
        }

        if (!result.isSuccess()) {
            const std::vector<CError>& errors = result.getErrors();
            for (size_t i = 0; i < errors.size(); ++i) {
                outFile << "Error: " << errors[i].getErrorMessage() << std::endl;
            }
        } else {
            CTree* tree = result.getValue();
            if (tree != nullptr) {
                std::ostringstream treeOutput;
                outFile << "Tree in prefix notation: " << tree->getTree() << std::endl;
            }
        }

        outFile.close();
        return CResult<std::string, CError>::ok(filePath);
    }

};
