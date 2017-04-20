#ifndef LAB12_ADDRESS_H
#define LAB12_ADDRESS_H

#include <string>

class Address {
        std::string firstName;
        std::string lastName;
        std::string address;
    public:
        Address();
        Address(std::string first, std::string last, std::string addr);
        
        void setFirstName(std::string name);
        void setLastName(std::string name);
        void setAddress(std::string addr);
        
        std::string getFirstName() const;
        std::string getLastName() const;
        std::string getAddress() const;
        
        bool operator == (const Address& addr) const;
};

#endif /* LAB12_ADDRESS_H */