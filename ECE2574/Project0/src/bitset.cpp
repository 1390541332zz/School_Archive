/*
 * bitset.cpp - Implementation of the bitset class.
 *
 * Author: Jacob Abel
 *
 * This file is part of Project 0.
 */

#include "bitset.hpp"

Bitset::Bitset() {
    arr = new uint8_t[1];
    *arr = 0;
    sz = 8;
}

Bitset::Bitset(intmax_t size) {
    if (size <= 0) {
        arr = nullptr;
        sz = 0;
        return;
    }

    size_t arr_size = std::ceil(static_cast<double>(size)/8);
    arr = new uint8_t[arr_size];
    sz = size;
    std::fill_n(arr, arr_size, 0);
}

Bitset::Bitset(const std::string & value) {
    if (   (value.find_first_not_of("01", 0) != std::string::npos)
        || (value.length() == 0)) {
        invalidate();
        return;
    }
    std::string str(value);
    std::reverse(str.begin(), str.end());
    sz = str.length();
    size_t arr_size = std::ceil(static_cast<double>(sz)/8);
    arr = new uint8_t[arr_size];
    std::fill_n(arr, arr_size, 0);
    for (size_t i = 0; i < sz; i++) {
        arr[i/8] |= (str[i] == '1' ? 0x01 : 0x00) << (i % 8);
    }
}

Bitset::~Bitset() {
    delete [] arr;
    sz = 0;
}

intmax_t Bitset::size() const {
    if (arr == nullptr) return 0;
    return sz;
}

bool Bitset::good() const {
    return (arr != nullptr || sz != 0);
}

void Bitset::set(intmax_t index) {
    if (!good()) return;
    if (index < 0 || index >= static_cast<intmax_t>(sz)) {
        invalidate();
        return;
    }
    arr[index/8] |= (0x01 << index % 8);
}

void Bitset::reset(intmax_t index) {
    if (!good()) return;
    if (index < 0 || index >= static_cast<intmax_t>(sz)) {
        invalidate();
        return;
    }
    arr[index/8] &= ~(0x01 << index % 8);
}

void Bitset::toggle(intmax_t index) {
    if (!good()) return;
    if (index < 0 || index >= static_cast<intmax_t>(sz)) {
        invalidate();
        return;
    }
    arr[index/8] ^= (0x01 << index % 8);
}

bool Bitset::test(intmax_t index) {
    if (!good()) return false;
    if (index < 0 || index >= static_cast<intmax_t>(sz)) {
        invalidate();
        return false;
    }
    return (arr[index/8] & (0x01 << (index % 8))) != 0x00;
}

std::string Bitset::asString() const {
    if (!good()) return "";
    std::ostringstream os;
    for (size_t i = 0; i < sz; i++) {
        uint8_t mask = (0x01 << (i%8));
        os << ((arr[i/8] & mask) >> (i%8));
    }
    std::string str = os.str();
    std::reverse(str.begin(), str.end());
    return str;
}

void Bitset::invalidate() {
    delete [] arr;
    arr = nullptr;
    sz = 0;
}
