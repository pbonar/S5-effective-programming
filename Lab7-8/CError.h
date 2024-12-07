#ifndef CERROR_H
#define CERROR_H

#include <string>

class CError {
public:
    CError(const std::string& errorMessage);
    std::string getErrorMessage() const;

private:
    std::string errorMessage;
};

#endif // CERROR_H
