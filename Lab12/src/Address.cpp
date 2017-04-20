/*
 * Purpose for program: This program provides an API for storing addresses.
 *
 * Programmer: Jacob Abel
 * Date: April 20, 2017
 *
 * Honor Code: I have neither given nor received any unauthorized assistance
 * with this program.
 */

#include "Address.h"

Address::Address() {
}

Address::Address(std::string first, std::string last, std::string addr) {
    firstName = first;
    lastName  = last;
    address   = addr;
}

void Address::setFirstName(std::string name) {
    firstName = name;
}

void Address::setLastName(std::string name) {
    lastName = name;
}

void Address::setAddress(std::string addr) {
    address = addr;
}

std::string Address::getFirstName() const {
    return firstName;
}

std::string Address::getLastName() const {
    return lastName;
}

std::string Address::getAddress() const {
    return address;
}

bool Address::operator == (const Address& addr) const {
    return (firstName == addr.firstName && lastName == addr.lastName && address == addr.address);
}