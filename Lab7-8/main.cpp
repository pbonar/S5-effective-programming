#include <iostream>
#include "CResult.h"
#include "CError.h"

CResult<double, CError> eDivide(double dDividend, double dDivisor)
{
    if (dDivisor == 0)
    {
        // Zwracamy stan błędu z odpowiednim komunikatem
        return CResult<double, CError>::cFail(new CError("cannot divide by zero"));
    }
    // Zwracamy stan sukcesu z wynikiem dzielenia
    return CResult<double, CError>::cOk(dDividend / dDivisor);
}

int main()
{
    CResult<double, CError> result = eDivide(10, 2); // Test z poprawnym dzieleniem
    if (result.bIsSuccess())
    {
        std::cout << "Result: " << result.cGetValue() << std::endl;
    }
    else
    {
        // Użycie tradycyjnej pętli for (C++98)
        size_t numErrors = result.vGetErrors().size();
        for (size_t i = 0; i < numErrors; ++i)
        {
            std::cout << "Error: " << result.vGetErrors()[i]->getErrorMessage() << std::endl;
        }
    }

    result = eDivide(10, 0); // Test z dzieleniem przez 0
    if (result.bIsSuccess())
    {
        std::cout << "Result: " << result.cGetValue() << std::endl;
    }
    else
    {
        // Użycie tradycyjnej pętli for (C++98)
        size_t numErrors = result.vGetErrors().size();
        for (size_t i = 0; i < numErrors; ++i)
        {
            std::cout << "Error: " << result.vGetErrors()[i]->getErrorMessage() << std::endl;
        }
    }

    return 0;
}
