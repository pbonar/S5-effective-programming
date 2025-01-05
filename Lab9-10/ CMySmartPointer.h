template<typename T>
class CMySmartPointer {
public:
    CMySmartPointer(T* ptr = nullptr) : pc_pointer(ptr), pc_counter(new CRefCounter()) {
        pc_counter->iAdd();
    }
    CMySmartPointer(const CMySmartPointer& other) {
        pc_pointer = other.pc_pointer;
        pc_counter = other.pc_counter;
        pc_counter->iAdd();
    }
    ~CMySmartPointer() {
        if (pc_counter->iDec() == 0) {
            delete pc_pointer;
            delete pc_counter;
        }
    }
    CMySmartPointer& operator=(const CMySmartPointer& other) {
        if (this != &other) {
            if (pc_counter->iDec() == 0) {
                delete pc_pointer;
                delete pc_counter;
            }
            pc_pointer = other.pc_pointer;
            pc_counter = other.pc_counter;
            pc_counter->iAdd();
        }
        return *this;
    }
    T& operator*() { return *pc_pointer; }
    T* operator->() { return pc_pointer; }

private:
    T* pc_pointer;
    CRefCounter* pc_counter;
};
