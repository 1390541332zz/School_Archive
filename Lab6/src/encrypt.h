#ifndef LAB6_ENCRYPT_H
#define LAB6_ENCRYPT_H

#include <iostream>
#include <fstream>
#include <string>
#include <cctype>

int encryptDecrypt(std::string iFile, std::string oFile);
std::string encrypt(std::string input);
std::string decrypt(std::string input);

#endif /* LAB6_ENCRYPT_H */