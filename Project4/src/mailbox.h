#ifndef PROJECT4_MAILBOX_H
#define PROJECT4_MAILBOX_H

#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <string>
//#include <regex>
#include <cstddef>
#include <cctype>
#include "sha256.h"

typedef struct mailFolder mailFolder;
typedef struct mailItem mailItem;

struct mailFolder {
    mailFolder* listPtr = nullptr;
    size_t mailSize = 0;
    size_t mailQty = 0;
    std::string title = "";
    mailItem* mailPtr = nullptr;
};

struct mailItem {
    size_t mailID = 0;
    std::string subject = "";
    std::string date = "";
    std::string fromAddr = "";
    std::string toAddr = "";
    std::string content = "";
};

const mailItem nullMail;

#define SIZE 10
#define MARGIN 5
#define SCALE 2

#define INBOX "Inbox"
#define HACKED "Hacked"

int mailbox(std::string inputFile, std::string outputFile);
mailFolder* initHead();
std::string lowerCase(std::string str);
mailFolder* findMailFolder(std::string title, mailFolder* listPtr);
bool verifyMail(mailItem& mail);
void importMbox(std::ofstream& os, std::string& inputFile, mailFolder* head);
void exportMbox(std::ofstream& os, std::string& outputFile, mailFolder* folder);
void dispMail(std::ofstream& os, mailFolder* folder, int index, bool isSingle);
void removeMail(std::ofstream& os, mailFolder* folder, int index);
void newMail(std::ifstream& is, std::ofstream& os, mailFolder* head);
void addMail(mailItem& mail, mailFolder* folder);
void implodeMailbox(mailFolder*& listPtr);

#endif /* PROJECT4_MAILBOX_H */