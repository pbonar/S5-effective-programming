#ifndef C_MY_SMART_POINTER_H
#define C_MY_SMART_POINTER_H

#include <iostream>

class CRefCounter {
public:
    CRefCounter() : i_count(0) {}
    int iAdd() { return (++i_count); }
    int iDec() { return (--i_count); }
    int iGet() const { return i_count; }

private:
    int i_count;
};

template <typename T>
class CMySmartPointer {
public:
    explicit CMySmartPointer(T *pcPointer)
        : pc_pointer(pcPointer), pc_counter(new CRefCounter()) {
        pc_counter->iAdd();
    }

    CMySmartPointer(const CMySmartPointer &pcOther)
        : pc_pointer(pcOther.pc_pointer), pc_counter(pcOther.pc_counter) {
        pc_counter->iAdd();
    }

    CMySmartPointer& operator=(const CMySmartPointer &pcOther) {
        if (this != &pcOther) {
            if (pc_counter->iDec() == 0) {
                delete pc_pointer;
                delete pc_counter;
            }

            pc_pointer = pcOther.pc_pointer;
            pc_counter = pcOther.pc_counter;
            pc_counter->iAdd();
        }
        return *this;
    }

    ~CMySmartPointer() {
        if (pc_counter->iDec() == 0) {
            delete pc_pointer;
            delete pc_counter;
        }
    }

    T& operator*() { return *pc_pointer; }
    T* operator->() { return pc_pointer; }

private:
    CRefCounter *pc_counter;
    T *pc_pointer;
};

#endif // C_MY_SMART_POINTER_H
