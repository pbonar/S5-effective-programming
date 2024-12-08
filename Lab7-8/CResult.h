#ifndef CRESULT_H
#define CRESULT_H

#include <vector>
#include "CError.h"

template <typename T, typename E>
class CResult {
public:
    CResult(const T& cValue);
    CResult(E* pcError);
    CResult(std::vector<E*>& vErrors);
    CResult(const CResult<T, E>& cOther);
    ~CResult();
    static CResult<T, E> cOk(const T& cValue);
    static CResult<T, E> cFail(E* pcError);
    static CResult<T, E> cFail(std::vector<E*>& vErrors);
    CResult<T, E>& operator=(const CResult<T, E>& cOther);
    bool bIsSuccess();
    T cGetValue();
    std::vector<E*>& vGetErrors();

private:
    T* pc_value;
    std::vector<E*> v_errors;
};

template <typename T, typename E>
CResult<T, E>::CResult(const T& cValue) : pc_value(new T(cValue)) {}

template <typename T, typename E>
CResult<T, E>::CResult(E* pcError) : pc_value(nullptr), v_errors(1, pcError) {}

template <typename T, typename E>
CResult<T, E>::CResult(std::vector<E*>& vErrors) : pc_value(nullptr), v_errors(vErrors) {}

template <typename T, typename E>
CResult<T, E>::CResult(const CResult<T, E>& cOther) {
    if (cOther.pc_value) {
        pc_value = new T(*(cOther.pc_value));
    } else {
        pc_value = nullptr;
    }
    v_errors = cOther.v_errors;
}

template <typename T, typename E>
CResult<T, E>::~CResult() {
    if (pc_value) {
        delete pc_value;
    }
    for (typename std::vector<E*>::iterator it = v_errors.begin(); it != v_errors.end(); ++it) {
        delete *it;
    }
}

template <typename T, typename E>
CResult<T, E> CResult<T, E>::cOk(const T& cValue) {
    return CResult<T, E>(cValue);
}

template <typename T, typename E>
CResult<T, E> CResult<T, E>::cFail(E* pcError) {
    return CResult<T, E>(pcError);
}

template <typename T, typename E>
CResult<T, E> CResult<T, E>::cFail(std::vector<E*>& vErrors) {
    return CResult<T, E>(vErrors);
}

template <typename T, typename E>
CResult<T, E>& CResult<T, E>::operator=(const CResult<T, E>& cOther) {
    if (this != &cOther) {
        if (pc_value) {
            delete pc_value;
        }
        for (typename std::vector<E*>::iterator it = v_errors.begin(); it != v_errors.end(); ++it) {
            delete *it;
        }
        if (cOther.pc_value) {
            pc_value = new T(*(cOther.pc_value));
        } else {
            pc_value = nullptr;
        }
        v_errors = cOther.v_errors;
    }
    return *this;
}

template <typename T, typename E>
bool CResult<T, E>::bIsSuccess() {
    return pc_value != nullptr;
}

template <typename T, typename E>
T CResult<T, E>::cGetValue() {
    return *pc_value;
}

template <typename T, typename E>
std::vector<E*>& CResult<T, E>::vGetErrors() {
    return v_errors;
}

#endif
