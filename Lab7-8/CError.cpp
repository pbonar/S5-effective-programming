#include "CError.h"

CError::CError(const std::string& errorMessagee) : errorMessage(errorMessagee) {}

std::string CError::getErrorMessage() const {
    return errorMessage;
}