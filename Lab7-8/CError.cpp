#include "CError.h"

CError::CError(const std::string& errorMessage) : errorMessage(errorMessage) {}

std::string CError::getErrorMessage() const {
    return errorMessage;
}