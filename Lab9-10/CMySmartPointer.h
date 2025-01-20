#ifndef C_MY_SMART_POINTER_H
#define C_MY_SMART_POINTER_H

#include <iostream>
#include <list>
#include <sstream> // Dla std::ostringstream

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
        : pc_pointer(pcPointer), pc_counter(new CRefCounter()), related_pointers(new std::list<CMySmartPointer*>()) {
        pc_counter->iAdd();
        related_pointers->push_back(this);
    }

    CMySmartPointer(const CMySmartPointer &pcOther)
        : pc_pointer(pcOther.pc_pointer), pc_counter(pcOther.pc_counter), related_pointers(pcOther.related_pointers) {
        pc_counter->iAdd();
        related_pointers->push_back(this);
    }

    CMySmartPointer& operator=(const CMySmartPointer &pcOther) {
        if (this != &pcOther) {
            if (pc_counter->iDec() == 0) {
                delete pc_pointer;
                delete pc_counter;
                delete related_pointers;
            }

            pc_pointer = pcOther.pc_pointer;
            pc_counter = pcOther.pc_counter;
            related_pointers = pcOther.related_pointers;
            pc_counter->iAdd();
            related_pointers->push_back(this);
        }
        return *this;
    }

    ~CMySmartPointer() {
        related_pointers->remove(this);
        if (pc_counter->iDec() == 0) {
            delete pc_pointer;
            delete pc_counter;
            delete related_pointers;
        }
    }

    T& operator*() { return *pc_pointer; }
    T* operator->() { return pc_pointer; }

    std::string printRelatedPointers() const {
        std::ostringstream oss;
        oss << "Related pointers count: " << related_pointers->size() << "\n";
        for (typename std::list<CMySmartPointer*>::const_iterator it = related_pointers->begin();
             it != related_pointers->end(); ++it) {
            oss << *it << " ";
        }
        return oss.str();
    }

private:
    CRefCounter *pc_counter;
    T *pc_pointer;
    std::list<CMySmartPointer*> *related_pointers;
};

#endif // C_MY_SMART_POINTER_H
