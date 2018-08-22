/*
 * Purpose for program: This program functions as a basic mailbox.
 *
 * Programmer: Jacob Abel
 * Date: April 10, 2017
 *
 * Honor Code: I have neither given nor received any unauthorized assistance
 * with this program.
 */

#include "mailbox.h"

// Primary Mailbox Function
int mailbox(std::string inputFile, std::string outputFile) {
    std::ifstream is(inputFile);
    std::ofstream os(outputFile);
    std::string line;
    
    mailFolder* head = initHead();
    
    while (std::getline(is, line)) {
        std::istringstream iss(line);
        std::string cmd = "", argA = "", argB = "";
        iss >> cmd;
        if (cmd == "load"   && iss >> argA) {
            os << "Command: " << cmd << ' ' << argA << std::endl;
            importMbox(os, argA, head);
        } else if (cmd == "save"   && iss >> argA >> argB) {
            os << "Command: " << cmd << ' ' << argA << ' ' << argB << std::endl;
            exportMbox(os, argB, findMailFolder(argA, head));
        } else if (cmd == "add") {
            os << "Command: " << cmd << std::endl;
           newMail(is, os, head);
        } else if (cmd == "remove" && iss >> argA >> argB) {
            os << "Command: " << cmd << ' ' << argA << ' ' << argB << std::endl;
            removeMail(os, findMailFolder(argA, head), stoi(argB));
        } else if (cmd == "show"   && iss >> argA) {
            if (iss >> argB) {
                os << "Command: " << cmd << ' ' << argA << ' ' << argB << std::endl;
                dispMail(os, findMailFolder(argA, head), stoi(argB), true);
            } else {
                os << "Command: " << cmd << ' ' << argA << std::endl;
                dispMail(os, findMailFolder(argA, head), 0, false);
            }
        } else if (cmd.front() != '#' && !iss.fail()) {
            std::cerr << "[ERROR] mailbox: Invalid Command" << std::endl;
        } 
    }
    implodeMailbox(head);
    return 0;
}

//Initialises Mailbox Data Structure
mailFolder* initHead() {
    mailFolder* head = new mailFolder;
    head->title = INBOX;
    head->listPtr = new mailFolder;
    head->listPtr->title = HACKED;
    return head;
}

//Reduces all characters in a string to lowercase
std::string lowerCase(std::string str) {
    for (size_t i = 0; i < str.length(); i++) str[i] = std::tolower(str[i]);
    return str;
}

// Returns the mailFolder with the corresponding title
mailFolder* findMailFolder(std::string title, mailFolder* listPtr) {
    while (listPtr != nullptr && lowerCase(title) != lowerCase(listPtr->title)) listPtr = listPtr->listPtr;
    if (listPtr == nullptr) std::cerr << "[ERROR] findMailFolder: Mail Folder not found." << std::endl;
    return listPtr;
}

// Verifies that the mailItem has not been tampered with. Returns true if intact
bool verifyMail(mailItem& mail) {
    std::string hash = sha256(mail.fromAddr + mail.date + mail.toAddr + mail.subject + mail.content);
    return (mail.mailID == sign(hash, mail.fromAddr));
}

// Adds a new mailItem to the mailbox
void addMail(mailItem& mail, mailFolder* folder) {
    if (folder == nullptr) {
        std::cerr << "[ERROR] addMail: Mailbox Pointer is NULL." << std::endl;
    } else {
        if (folder->mailPtr == nullptr) {
            folder->mailPtr = new mailItem[SIZE];
            folder->mailSize = SIZE;
        } else if (folder->mailSize == folder->mailQty) {
            mailItem* tmp = folder->mailPtr;
            folder->mailPtr = new mailItem[folder->mailSize * SCALE];
            for (size_t i = 0; i < folder->mailQty; i++) folder->mailPtr[i] = tmp[i];
            delete[] tmp;
            folder->mailSize *= SCALE;
        }
        folder->mailPtr[folder->mailQty] = mail;
        folder->mailQty++;
    }
}

// Removes a mailItem from a mailfolder and compacts the folder array
void removeMail(std::ofstream& os, mailFolder* folder, int index) {
    if (folder == nullptr) {
        std::cerr << "[ERROR] removeMail: Mailbox Pointer is NULL." << std::endl;
    } else if (index < 0 || static_cast<size_t>(index) >= folder->mailQty) {
        os << "\tMessage not removed" << std::endl;
        os << "\tMessage " << index << " not a valid message number" << std::endl;
    } else {
        for (size_t i = index; i < folder->mailQty; i++) {
                folder->mailPtr[i] = (i != folder->mailSize - 1) ? folder->mailPtr[i + 1] : nullMail;
            }
        folder->mailPtr[folder->mailQty - 1] = nullMail;
        folder->mailQty--;
        os << "\tMessage removed" << std::endl;
        if (folder->mailQty + MARGIN == folder->mailSize / SCALE) {
            mailItem* tmp = folder->mailPtr;
            folder->mailPtr = new mailItem[folder->mailSize / SCALE];
            for (size_t i = 0; i < folder->mailQty; i++) folder->mailPtr[i] = tmp[i];
            delete[] tmp;
            folder->mailSize /= SCALE;
        }
    }
}

// Takes mail data from a command and passes it to addMail
void newMail(std::ifstream& is, std::ofstream& os, mailFolder* head) {
    mailItem mail;
    //std::smatch id;
    std::string tmp;
    if (head == nullptr) {
        std::cerr << "[ERROR] newMail: Mailbox Pointer is NULL." << std::endl;
        return;
    }
    is >> tmp >> std::ws && std::getline(is, mail.fromAddr, '\n');
    is >> tmp >> std::ws && std::getline(is, mail.date, '\n');
    is >> tmp >> std::ws && std::getline(is, mail.toAddr, '\n');
    is >> tmp >> std::ws && std::getline(is, mail.subject, '\n');
    std::getline(is, tmp, '\n');
    
    // What compiler are you using? This code works with the latest version of 
    // g++ but does not work on web-cat.
    // while (std::getline(is, tmp) && !std::regex_search(tmp, id, std::regex("ID\\s(\\d+)"))) mail.content += tmp;
    // mail.mailID = std::stoul(id.str(1));
    std::getline(is, mail.content, '\n');
    is >> tmp >> mail.mailID;
    
    if (is.fail()) {
        std::cerr << "[ERROR] newMail: File Read Error." << std::endl;
        return;
    }
    mailFolder* folder = findMailFolder((verifyMail(mail) ? INBOX : HACKED), head);
    addMail(mail, folder);
    if (folder->title == HACKED) {
        os << "\tMessage was not authentic.  Sent to hacked list." << std::endl;
    } else {
        os << "\tMessage added" << std::endl;
    }
}

// Loads a mbox file into a mailbox data structure in memory
void importMbox(std::ofstream& os, std::string& inputFile, mailFolder* head) {
    std::ifstream is(inputFile);
    std::string tmp;
    //std::smatch id;
    size_t mailCount = 0;
    //while (std::getline(is, tmp)) if (std::regex_match(tmp, std::regex("ID\\s\\d+"))) mailCount++;
    is.clear();
    is.seekg(0, is.beg);
    //for (size_t i = 0; i < mailCount; i++) {
        while(!is.fail()) {
        mailItem mail;
        is >> tmp >> std::ws && std::getline(is, mail.fromAddr, '\n');
        is >> tmp >> std::ws && std::getline(is, mail.date, '\n');
        is >> tmp >> std::ws && std::getline(is, mail.toAddr, '\n');
        is >> tmp >> std::ws && std::getline(is, mail.subject, '\n');
        std::getline(is, tmp);
        
        // What compiler are you using? This code works with the latest version of 
        // g++ but does not work on web-cat.
        //while (std::getline(is, tmp) && !std::regex_search(tmp, id, std::regex("ID\\s(\\d+)"))) mail.content += tmp;
        //mail.mailID = std::stoul(id.str(1));
        
        std::getline(is, mail.content, '\n');
        is >> tmp >> mail.mailID;
        if (is.fail()) break;
        mailFolder* folder = findMailFolder((verifyMail(mail) ? INBOX : HACKED), head);
        addMail(mail, folder);
        mailCount++;
    }
    os << "\tMessages: " << mailCount << std::endl;
    is.close();
}

// Saves the mailbox data structure to an mbox file
void exportMbox(std::ofstream& os, std::string& outputFile, mailFolder* folder) {
    if (folder == nullptr) {
        std::cerr << "[ERROR] exportMbox: Mailbox Pointer is NULL." << std::endl;
    } else {
        std::ofstream mbox(outputFile);
        for (size_t i = 0; i < folder->mailQty; i++) {
            mbox << "From "    << folder->mailPtr[i].fromAddr << std::endl;
            mbox << "Date "    << folder->mailPtr[i].date     << std::endl;
            mbox << "To "      << folder->mailPtr[i].toAddr   << std::endl;
            mbox << "Subject " << folder->mailPtr[i].subject  << std::endl;
            mbox << "Message" << std::endl << folder->mailPtr[i].content  << std::endl;
            mbox << "ID "      << folder->mailPtr[i].mailID   << std::endl << std::endl;
        }
        mbox.close();
        os << '\t' << folder->mailQty << " Messages saved" << std::endl;
    }
}

// Displays either an entire mailbox or a single mailItem if an index is given
void dispMail(std::ofstream& os, mailFolder* folder, int index, bool isSingle) {
    if (folder == nullptr) {
        std::cerr << "[ERROR] dispMail: Mailbox Pointer is NULL." << std::endl;
    } else if (index < 0 || static_cast<size_t>(index) >= folder->mailQty) {
        os << "\tMessage " << index << " not a valid message number" << std::endl;
    } else {
        size_t qty = (isSingle) ? index : folder->mailQty - 1;
        for (size_t i = index; i <= qty; i++) {
            os << "From "    << folder->mailPtr[i].fromAddr << std::endl;
            os << "Date "    << folder->mailPtr[i].date     << std::endl;
            os << "To "      << folder->mailPtr[i].toAddr   << std::endl;
            os << "Subject " << folder->mailPtr[i].subject  << std::endl;
            os << "Message" << std::endl << folder->mailPtr[i].content  << std::endl;
            os << "ID "      << folder->mailPtr[i].mailID   << std::endl << std::endl;
        }
    }
}

// Implodes and frees the mailbox data structure
void implodeMailbox(mailFolder*& listPtr) {
    while (listPtr != nullptr) {
        if (listPtr->mailPtr != nullptr) delete[] listPtr->mailPtr;
        mailFolder* tmpPtr = listPtr->listPtr;
        delete listPtr;
        listPtr = tmpPtr;
    }
}