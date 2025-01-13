#ifndef CRESULT_H
#define CRESULT_H

#include <vector>
#include <iostream>

using namespace std;

template <typename T, typename E>
class CResult {
private:
    T* result_value;
    std::vector<E> error_list;

public:
    CResult() : result_value(NULL), error_list() {}

    CResult(const T& value) : result_value(new T(value)), error_list() {}

    CResult(const E& error) : result_value(NULL), error_list(1, error) {} 

    CResult(const std::vector<E>& errors) : result_value(NULL), error_list(errors) {}

    CResult(const CResult<T, E>& other) : result_value(other.result_value ? new T(*other.result_value) : NULL), 
        error_list(other.error_list) {}

    ~CResult() {
        delete result_value;
    }

    static CResult<T, E> ok(const T& value) {
        CResult<T, E> result;
        result.result_value = new T(value);
        return result;
    }

    static CResult<T, E> fail(E error) {
        CResult<T, E> result;
        result.error_list.push_back(error);
        // cout << "ERROR" << result.error_list.size() <<endl;
        return result;
    }

    static CResult<T, E> fail(const std::vector<E>& errors) {
        return CResult<T, E>(errors);
    }

    CResult<T, E>& operator=(const CResult<T, E>& other) {
        if (this != &other) {
            delete result_value;
            result_value = other.result_value ? new T(*other.result_value) : NULL;
            error_list = other.error_list;
        }
        return *this;
    }
    
    CResult<T, E>& operator=(T* other) {
        result_value = other;
        return *this;
    }

    bool isSuccess() const {
        return result_value != NULL;
    }

    T getValue() const {
        if (result_value) {
            return *result_value;
        }
        return T();
    }


    const std::vector<E>& getErrors() const {
        return error_list;
    }

};

template <typename E>
class CResult<void, E> {
private:
    std::vector<E> error_list;

public:
    CResult() : error_list() {}

    CResult(const E& error) : error_list(1, error) {} 

    CResult(const std::vector<E>& errors) : error_list(errors) {}

    CResult(const CResult<void, E>& other) : error_list(other.error_list) {}

    ~CResult() {}

    CResult<void, E>& operator=(const CResult<void, E>& other) {
        if (this != &other) {
            error_list = other.error_list;
        }
        return *this;
    }

    bool isSuccess() const {
        return error_list.empty();
    }

    const std::vector<E>& getErrors() const {
        return error_list;
    }

};

#endif
