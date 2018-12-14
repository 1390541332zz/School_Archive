/*
 * Purpose for program: This program provides an API for storing integers in a vector.
 *
 * Programmer: Jacob Abel
 * Date: April 26, 2017
 *
 * Honor Code: I have neither given nor received any unauthorized assistance
 * with this program.
 */

#include "Vector.h"

Vector::Vector() {
    size = ARRSIZE;
    arr = new storageType[ARRSIZE]();
}

Vector::~Vector() {
    delete [] arr;
}

size_t Vector::itemCount() const {
    return qty;
}

storageType Vector::itemAt(int index) const {
    return (index >= 0 && static_cast<size_t>(index) < qty) ? arr[index]: storageType();
}

void Vector::add(storageType data) {
    if (qty >= size) {
        storageType* tmp = arr;
        size *= SCALE;
        arr = new storageType[size]();
        for (size_t i = 0; i < qty; i++) arr[i] = tmp[i];
        delete [] tmp;
    }
    arr[qty++] = data;
}