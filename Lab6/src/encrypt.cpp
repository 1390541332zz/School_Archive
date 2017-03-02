/*
 * Purpose for program: Encryption and Decryption through an Atbash Cipher.
 *
 * Programmer: Jacob Abel
 * Date: March 1, 2017
 *
 * Honor Code: I have neither given nor received any unauthorized assistance
 * with this program.
 */

#include "encrypt.h"

int encryptDecrypt(std::string iFile, std::string oFile) {
    std::ifstream is(iFile);
    std::ofstream os(oFile);
    std::string cmd;
    std::string payload;
    
    while (is >> cmd && std::getline(is, payload, '\n') && !is.fail()) {
        if (cmd == "encrypt") {
            os << "encrypted:" << encrypt(payload) << std::endl;
        } else if ( cmd == "decrypt") {
            os << "decrypted:" << decrypt(payload) << std::endl;
        } else {
            std::cerr << "ERROR: Invalid Command!" << std::endl;
        }
    }
    
    is.close();
    os.close();
    return 0;
}

std::string encrypt(std::string input){    
    for (size_t i = 0; i < input.length(); i++){
        char c = input[i];
        if (std::isupper(c)) {
            input[i] = 2 * 'A' + 25 - c;
        } else if (std::islower(c)) {
            input[i] = 2 * 'a' + 25 - c;
        }
    }
    return input;
}

std::string decrypt(std::string input){
    return encrypt(input);
}