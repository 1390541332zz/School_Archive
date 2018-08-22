#ifndef LAB13_VECTOR_H
#define LAB13_VECTOR_H

#include <cstddef>

#define ARRSIZE 10
#define SCALE 2

typedef int storageType;

class Vector {
    private:
        size_t size = 0;
        size_t qty = 0;
        storageType* arr = nullptr;
    public:
        Vector();
        ~Vector();
        size_t itemCount() const;
        storageType itemAt(int index) const;
        void add(storageType data);
};

#endif /* LAB13_VECTOR_H */