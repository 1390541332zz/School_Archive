/*
 * Purpose for program: Testing the Atbash Cipher
 *
 * Programmer: Jacob Abel
 * Date: March 1, 2017
 *
 * Honor Code: I have neither given nor received any unauthorized assistance
 * with this program.
 */
 
 #include "lab6.h"
 
 int main(int argc, char const *argv[]) {
     if (argc < 3) {
         std::cerr << "ERROR: Missing Arguments!" << std::endl;
     } else if (argc > 3) {
         std::cerr << "ERROR: Unexpected Arguments!" << argc << std::endl;
     } else {
         return encryptDecrypt(argv[1], argv[2]);
     }
     return 0;
 }