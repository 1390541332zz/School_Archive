/*
 * Purpose for program: Google Unit Tests for mailbox.cpp
 *
 * Programmer: Jacob Abel
 * Date: April 10, 2017
 *
 * Honor Code: I have neither given nor received any unauthorized assistance
 * with this program.
 */

#include "mailbox.h"
#include <gtest/gtest.h>
#include <sstream>

const std::string NULLSTREAM     = "/dev/null";
const std::string TEST_DIR      = "./test/";
const std::string GENERATED_DIR = "generated/";
const std::string MBOXES_DIR    = "mboxes/";
const std::string SAMPLES_DIR   = "samples/";

const mailItem mailValid1 = {
    4135, 
    "Let's do lunch", 
    "2014/4/11", 
    "HIWTDIPPG@vt.edu", 
    "RLCVAZDSA@vt.edu", 
    "At first she would call to him as she did so with words that she probably considered friendly, such as \"come on then, you old dung-beetle!\", or \"look at the old dung-beetle there!\" Gregor never responded to being spoken to in that way, but just remained where he was forced to impose on them. \"Anna! Anna!\" his father called into the kitchen through the entrance hall, clapping his hands, \"get a locksmith here, now!\" And the two girls, their skirts swishing, immediately ran out through the hall, wrenching open the front door of the bedroom opened and Mr. \"Grete, come with us in here for a little while then as well, and Gregor's sister would leave her work to help her mother, but nothing would have any effect on him. Now Gregor's sister also had to help his mother with the music stand, his mother with the music stand, his mother with the music stand, his mother with the cooking; although that was not about him in some other food that was more suitable? If she didn't do it herself he would rather go hungry than draw her attention to it, although he did not want to think about too much, so he started to move toward her, he was slow and infirm, but it was only now out of politeness that they allowed their peace to be disturbed. Smears of dirt were left on the walls, here and there were now many such things as one of the worst of these places when his sister no longer had any particular reason to be upset, and if he finally managed to do what he wanted with that leg, all the others seemed to be set free and would move about painfully. Please don't make things any harder for me than they are already, and don't take sides against me at the office. And the injury in Gregor's back began to hurt as much as he would."
};
const mailItem mailInvalid1 = {
    4136, 
    "Let's do lunch", 
    "2014/4/11", 
    "HIWTDIPPG@vt.edu", 
    "RLCVAZDSA@vt.edu", 
    "At first she would call to him as she did so with words that she probably considered friendly, such as \"come on then, you old dung-beetle!\", or \"look at the old dung-beetle there!\" Gregor never responded to being spoken to in that way, but just remained where he was forced to impose on them. \"Anna! Anna!\" his father called into the kitchen through the entrance hall, clapping his hands, \"get a locksmith here, now!\" And the two girls, their skirts swishing, immediately ran out through the hall, wrenching open the front door of the bedroom opened and Mr. \"Grete, come with us in here for a little while then as well, and Gregor's sister would leave her work to help her mother, but nothing would have any effect on him. Now Gregor's sister also had to help his mother with the music stand, his mother with the music stand, his mother with the music stand, his mother with the cooking; although that was not about him in some other food that was more suitable? If she didn't do it herself he would rather go hungry than draw her attention to it, although he did not want to think about too much, so he started to move toward her, he was slow and infirm, but it was only now out of politeness that they allowed their peace to be disturbed. Smears of dirt were left on the walls, here and there were now many such things as one of the worst of these places when his sister no longer had any particular reason to be upset, and if he finally managed to do what he wanted with that leg, all the others seemed to be set free and would move about painfully. Please don't make things any harder for me than they are already, and don't take sides against me at the office. And the injury in Gregor's back began to hurt as much as he would."
};
const mailItem mailValid2 = {
    3630, 
    "Get Started on P4", 
    "2017/03/21", 
    "dmcphers@vt.edu", 
    "dmcphers@vt.edu", 
    "Hey don't put off project 4 any more.  You'll thank me when you are done."
};
const mailItem mailInvalid2 = {
    3631, 
    "Get Started on P4", 
    "2017/03/21", 
    "dmcphers@vt.edu", 
    "dmcphers@vt.edu", 
    "Hey don't put off project 4 any more.  You'll thank me when you are done."
};

std::string extractFile(std::string file) {
    std::ifstream is(file);
    std::stringstream buf;
    buf << is.rdbuf();
    is.close();
    return buf.str();
}

TEST(ImplodeMailbox, Cleanup) {
    mailFolder* head = initHead();
    implodeMailbox(head);
    ASSERT_EQ(head, nullptr);
}

TEST(lowerCase, Verify) {
    ASSERT_EQ("inbox",  lowerCase("inbox"));
    ASSERT_EQ("inbox",  lowerCase("INBOX"));
    ASSERT_EQ("inbox",  lowerCase("Inbox"));
    ASSERT_EQ("hacked", lowerCase("hacked"));
    ASSERT_EQ("hacked", lowerCase("HACKED"));
    ASSERT_EQ("hacked", lowerCase("Hacked"));
}

TEST(FindMailFolder, Search) {
    mailFolder* head = initHead();
    ASSERT_EQ(findMailFolder(INBOX, head), head);
    ASSERT_EQ(findMailFolder(HACKED, head), head->listPtr);
}

TEST(FindMailFolder, Case) {
    mailFolder* head = initHead();
    ASSERT_EQ(findMailFolder("INBOX", head), head);
    ASSERT_EQ(findMailFolder("HACKED", head), head->listPtr);
    ASSERT_EQ(findMailFolder("inbox", head), head);
    ASSERT_EQ(findMailFolder("hacked", head), head->listPtr);
}

TEST(VerifyMail, Verify) {
    mailItem mailValid   = mailValid2;
    mailItem mailInvalid = mailInvalid2;
    ASSERT_TRUE(verifyMail(mailValid));
    ASSERT_FALSE(verifyMail(mailInvalid));
}

TEST(AddMail, Add) {
    mailFolder* head = initHead();
    mailFolder* fakeHead = initHead();
    mailItem mail1 = mailValid1;
    mailItem mail2 = mailInvalid1;
    mailItem mail3 = mailValid2;
    mailItem mail4 = mailInvalid2;
    
    fakeHead->mailPtr = new mailItem[20];
    fakeHead->mailSize = 20;
    fakeHead->listPtr->mailPtr = new mailItem[SIZE];
    fakeHead->listPtr->mailSize = SIZE;
    fakeHead->mailPtr[0] = mail1;
    fakeHead->mailPtr[1] = mail1;
    fakeHead->mailPtr[2] = mail1;
    fakeHead->mailPtr[3] = mail1;
    fakeHead->mailPtr[4] = mail1;
    fakeHead->mailPtr[5] = mail3;
    fakeHead->mailPtr[6] = mail1;
    fakeHead->mailPtr[7] = mail1;
    fakeHead->mailPtr[8] = mail1;
    fakeHead->mailPtr[9] = mail1;
    fakeHead->mailPtr[10] = mail1;
    fakeHead->listPtr->mailPtr[0] = mail2;
    fakeHead->listPtr->mailPtr[0] = mail2;
    fakeHead->listPtr->mailPtr[1] = mail4;
    fakeHead->mailQty = 11;
    fakeHead->listPtr->mailQty = 3;

    addMail(mail1, head);
    addMail(mail1, head);
    addMail(mail1, head);
    addMail(mail1, head);
    addMail(mail1, head);
    addMail(mail2, head->listPtr);
    addMail(mail3, head);
    addMail(mail4, head->listPtr);
    addMail(mail1, head);
    addMail(mail1, head);
    addMail(mail1, head);
    addMail(mail1, head);
    addMail(mail1, head);

    for (size_t i = 0; i < fakeHead->mailQty; i++) {
        ASSERT_EQ(head->mailPtr[i].mailID,   fakeHead->mailPtr[i].mailID)<<i<< ' '<<head->mailQty<< ' '<<head->mailSize;
        ASSERT_EQ(head->mailPtr[i].subject,  fakeHead->mailPtr[i].subject);
        ASSERT_EQ(head->mailPtr[i].date,     fakeHead->mailPtr[i].date);
        ASSERT_EQ(head->mailPtr[i].fromAddr, fakeHead->mailPtr[i].fromAddr);
        ASSERT_EQ(head->mailPtr[i].toAddr,   fakeHead->mailPtr[i].toAddr);
        ASSERT_EQ(head->mailPtr[i].content,  fakeHead->mailPtr[i].content);
    }
    for (size_t i = 0; i < fakeHead->listPtr->mailQty; i++) {
        ASSERT_EQ(head->listPtr->mailPtr[i].mailID,   fakeHead->listPtr->mailPtr[i].mailID);
        ASSERT_EQ(head->listPtr->mailPtr[i].subject,  fakeHead->listPtr->mailPtr[i].subject);
        ASSERT_EQ(head->listPtr->mailPtr[i].date,     fakeHead->listPtr->mailPtr[i].date);
        ASSERT_EQ(head->listPtr->mailPtr[i].fromAddr, fakeHead->listPtr->mailPtr[i].fromAddr);
        ASSERT_EQ(head->listPtr->mailPtr[i].toAddr,   fakeHead->listPtr->mailPtr[i].toAddr);
        ASSERT_EQ(head->listPtr->mailPtr[i].content,  fakeHead->listPtr->mailPtr[i].content);
    }
}

TEST(RemoveMail, Remove) {
    std::string logAddr = "verifyRemove.out";
    std::ofstream os(TEST_DIR + GENERATED_DIR + logAddr);
    mailFolder* head = initHead();
    mailFolder* fakeHead = initHead();
    
    mailItem mail1 = mailValid1;
    mailItem mail2 = mailInvalid1;
    mailItem mail3 = mailValid2;
    mailItem mail4 = mailInvalid2;
    
    addMail(mail4, fakeHead->listPtr);
    addMail(mail2, fakeHead->listPtr);
    addMail(mail3, fakeHead);
    addMail(mail1, fakeHead);

    addMail(mail1, head);
    addMail(mail2, head->listPtr);
    addMail(mail4, head->listPtr);
    addMail(mail2, head->listPtr);
    addMail(mail3, head);
    addMail(mail1, head);

    ASSERT_NE(fakeHead->mailPtr,          nullptr);
    ASSERT_NE(fakeHead->listPtr->mailPtr, nullptr);
    ASSERT_NE(head->listPtr->mailPtr,     nullptr);
    ASSERT_NE(head->mailPtr,              nullptr);
    
    removeMail(os, head, 300);
    removeMail(os, head, 5);
    removeMail(os, head, -1);
    removeMail(os, head, 0);
    removeMail(os, head->listPtr, 0);
    
    for (size_t i = 0; i < fakeHead->mailQty; i++) {
        ASSERT_EQ(head->mailPtr[i].mailID,   fakeHead->mailPtr[i].mailID);
        ASSERT_EQ(head->mailPtr[i].subject,  fakeHead->mailPtr[i].subject);
        ASSERT_EQ(head->mailPtr[i].date,     fakeHead->mailPtr[i].date);
        ASSERT_EQ(head->mailPtr[i].fromAddr, fakeHead->mailPtr[i].fromAddr);
        ASSERT_EQ(head->mailPtr[i].toAddr,   fakeHead->mailPtr[i].toAddr);
        ASSERT_EQ(head->mailPtr[i].content,  fakeHead->mailPtr[i].content);
    }
    for (size_t i = 0; i < fakeHead->listPtr->mailQty; i++) {
        ASSERT_EQ(head->listPtr->mailPtr[i].mailID,   fakeHead->listPtr->mailPtr[i].mailID);
        ASSERT_EQ(head->listPtr->mailPtr[i].subject,  fakeHead->listPtr->mailPtr[i].subject);
        ASSERT_EQ(head->listPtr->mailPtr[i].date,     fakeHead->listPtr->mailPtr[i].date);
        ASSERT_EQ(head->listPtr->mailPtr[i].fromAddr, fakeHead->listPtr->mailPtr[i].fromAddr);
        ASSERT_EQ(head->listPtr->mailPtr[i].toAddr,   fakeHead->listPtr->mailPtr[i].toAddr);
        ASSERT_EQ(head->listPtr->mailPtr[i].content,  fakeHead->listPtr->mailPtr[i].content);
    }
    removeMail(os, head->listPtr, 0);
    removeMail(os, head->listPtr, 0);
    removeMail(os, head->listPtr, 0);
    removeMail(os, head->listPtr, 0);
    removeMail(os, head->listPtr, 0);
    removeMail(os, head->listPtr, 0);
    removeMail(os, head->listPtr, 0);

    os.close();
    
    std::string genStr  = extractFile(TEST_DIR + GENERATED_DIR + logAddr);
    std::string sampStr = extractFile(TEST_DIR + SAMPLES_DIR   + logAddr);
    ASSERT_EQ(genStr, sampStr);

}

TEST(NewMail, Add) {
    std::string logAddr  = "verifyNew.out";
    std::string fileAddr = "verifyNew.in";
    std::ifstream is(TEST_DIR + SAMPLES_DIR   + fileAddr);
    std::ofstream os(TEST_DIR + GENERATED_DIR + logAddr);
    mailFolder* head = initHead();
    mailFolder* fakeHead = initHead();
    mailItem mail1 = mailValid2;
    mailItem mail2 = mailInvalid2;
    std::string tmp;

    addMail(mail1, fakeHead);
    addMail(mail2, fakeHead->listPtr);
    is >> tmp;
    newMail(is, os, head);
    is >> tmp;
    newMail(is, os, head);
    
    ASSERT_NE(head->mailPtr,              nullptr);
    ASSERT_NE(head->listPtr->mailPtr,     nullptr);
    ASSERT_NE(fakeHead->mailPtr,          nullptr);
    ASSERT_NE(fakeHead->listPtr->mailPtr, nullptr);
        
    for (size_t i = 0; i < fakeHead->mailQty; i++) {
        ASSERT_EQ(head->mailPtr[i].mailID,   fakeHead->mailPtr[i].mailID);
        ASSERT_EQ(head->mailPtr[i].subject,  fakeHead->mailPtr[i].subject);
        ASSERT_EQ(head->mailPtr[i].date,     fakeHead->mailPtr[i].date);
        ASSERT_EQ(head->mailPtr[i].fromAddr, fakeHead->mailPtr[i].fromAddr);
        ASSERT_EQ(head->mailPtr[i].toAddr,   fakeHead->mailPtr[i].toAddr);
        ASSERT_EQ(head->mailPtr[i].content,  fakeHead->mailPtr[i].content);
    }
    for (size_t i = 0; i < fakeHead->listPtr->mailQty; i++) {
        ASSERT_EQ(head->listPtr->mailPtr[i].mailID,   fakeHead->listPtr->mailPtr[i].mailID);
        ASSERT_EQ(head->listPtr->mailPtr[i].subject,  fakeHead->listPtr->mailPtr[i].subject);
        ASSERT_EQ(head->listPtr->mailPtr[i].date,     fakeHead->listPtr->mailPtr[i].date);
        ASSERT_EQ(head->listPtr->mailPtr[i].fromAddr, fakeHead->listPtr->mailPtr[i].fromAddr);
        ASSERT_EQ(head->listPtr->mailPtr[i].toAddr,   fakeHead->listPtr->mailPtr[i].toAddr);
        ASSERT_EQ(head->listPtr->mailPtr[i].content,  fakeHead->listPtr->mailPtr[i].content);
    }
    
    is.close();
    os.close();
    
    std::string genStr  = extractFile(TEST_DIR + GENERATED_DIR + logAddr);
    std::string sampStr = extractFile(TEST_DIR + SAMPLES_DIR   + logAddr);
    ASSERT_EQ(genStr, sampStr);
}

TEST(ImportMbox, Import) {
    std::string logAddr = "verifyImport.out";
    std::string mboxAddr = "verifyImport.mbox";
    std::ofstream os(TEST_DIR + GENERATED_DIR + logAddr);
    std::string fileAddr = TEST_DIR + MBOXES_DIR + mboxAddr;
    mailFolder* head = initHead();
    mailFolder* fakeHead = initHead();
    
    mailItem mail1 = mailValid1;
    mailItem mail2 = mailInvalid1;
    
    addMail(mail1, fakeHead);
    addMail(mail2, fakeHead->listPtr);
    addMail(mail1, fakeHead);
    addMail(mail1, fakeHead);
    importMbox(os, fileAddr, head);

    ASSERT_NE(fakeHead->mailPtr,          nullptr);
    ASSERT_NE(fakeHead->listPtr->mailPtr, nullptr);
    ASSERT_NE(head->listPtr->mailPtr,     nullptr);
    ASSERT_NE(head->mailPtr,              nullptr);
    
    for (size_t i = 0; i < fakeHead->mailQty; i++) {
        ASSERT_EQ(head->mailPtr[i].mailID,   fakeHead->mailPtr[i].mailID);
        ASSERT_EQ(head->mailPtr[i].subject,  fakeHead->mailPtr[i].subject);
        ASSERT_EQ(head->mailPtr[i].date,     fakeHead->mailPtr[i].date);
        ASSERT_EQ(head->mailPtr[i].fromAddr, fakeHead->mailPtr[i].fromAddr);
        ASSERT_EQ(head->mailPtr[i].toAddr,   fakeHead->mailPtr[i].toAddr);
        ASSERT_EQ(head->mailPtr[i].content,  fakeHead->mailPtr[i].content);
    }
    for (size_t i = 0; i < fakeHead->listPtr->mailQty; i++) {
        ASSERT_EQ(head->listPtr->mailPtr[i].mailID,   fakeHead->listPtr->mailPtr[i].mailID);
        ASSERT_EQ(head->listPtr->mailPtr[i].subject,  fakeHead->listPtr->mailPtr[i].subject);
        ASSERT_EQ(head->listPtr->mailPtr[i].date,     fakeHead->listPtr->mailPtr[i].date);
        ASSERT_EQ(head->listPtr->mailPtr[i].fromAddr, fakeHead->listPtr->mailPtr[i].fromAddr);
        ASSERT_EQ(head->listPtr->mailPtr[i].toAddr,   fakeHead->listPtr->mailPtr[i].toAddr);
        ASSERT_EQ(head->listPtr->mailPtr[i].content,  fakeHead->listPtr->mailPtr[i].content);
    }
    
    os.close();
    
    std::string genStr  = extractFile(TEST_DIR + GENERATED_DIR + logAddr);
    std::string sampStr = extractFile(TEST_DIR + SAMPLES_DIR   + logAddr);
    ASSERT_EQ(genStr, sampStr);
}

TEST(ExportMbox, Export) {
    std::string logAddr    = "verifyExport.out";
    std::string inboxAddr  = "verifyExport-Inbox.mbox";
    std::string hackedAddr = "verifyExport-Hacked.mbox";
    std::string inAddr     = TEST_DIR + MBOXES_DIR    + "verifyImport.mbox";
    std::string outInbox   = TEST_DIR + GENERATED_DIR + inboxAddr;
    std::string outHacked  = TEST_DIR + GENERATED_DIR + hackedAddr;
    std::ofstream os(TEST_DIR + GENERATED_DIR + logAddr);
    std::ofstream nullOS(NULLSTREAM);
    mailFolder* head = initHead();
    
    importMbox(nullOS, inAddr, head);
    exportMbox(os, outInbox, findMailFolder(INBOX, head));
    exportMbox(os, outHacked, findMailFolder(HACKED, head));
    
    os.close();
    
    std::string genInboxStr   = extractFile(outInbox);
    std::string genHackedStr  = extractFile(outHacked);
    std::string genLogStr     = extractFile(TEST_DIR + GENERATED_DIR + logAddr);
    std::string sampInboxStr  = extractFile(TEST_DIR + MBOXES_DIR    + inboxAddr);
    std::string sampHackedStr = extractFile(TEST_DIR + MBOXES_DIR    + hackedAddr);
    std::string sampLogStr    = extractFile(TEST_DIR + SAMPLES_DIR   + logAddr);
    ASSERT_EQ(genInboxStr,  sampInboxStr);
    ASSERT_EQ(genHackedStr, sampHackedStr);
    ASSERT_EQ(genLogStr,    sampLogStr);
}

TEST(DispMail, Display) {
    std::string logAddr  = "verifyDisplay.out";
    std::string fileAddr = "verifyImport.mbox";
    std::string inFile   = TEST_DIR + MBOXES_DIR    + fileAddr;
    std::string outFile  = TEST_DIR + GENERATED_DIR + logAddr;
    std::ofstream os(outFile);
    mailFolder* head = initHead();
    
    importMbox(os, inFile, head);
    dispMail(os, findMailFolder(INBOX, head), -1, true);
    dispMail(os, findMailFolder(INBOX, head), 5, true);
    dispMail(os, findMailFolder(INBOX, head), 300, true);
    dispMail(os, findMailFolder(INBOX, head), 0, true);
    dispMail(os, findMailFolder(INBOX, head), 2, true);
    dispMail(os, findMailFolder(INBOX, head), 0, false);
    dispMail(os, findMailFolder(HACKED, head), -1, true);
    dispMail(os, findMailFolder(HACKED, head), 5, true);
    dispMail(os, findMailFolder(HACKED, head), 300, true);
    dispMail(os, findMailFolder(HACKED, head), 0, true);
    dispMail(os, findMailFolder(HACKED, head), 0, false);
    
    std::string genLogStr  = extractFile(outFile);
    std::string sampLogStr = extractFile(TEST_DIR + SAMPLES_DIR   + logAddr);
    
    ASSERT_EQ(genLogStr, sampLogStr);
}

TEST(Mailbox, VerifyCommandParsing) {
    std::string logAddr  = "verifyCommandParsing.out";
    std::string fileAddr = "verifyCommandParsing.in";
    std::string inFile   = TEST_DIR + SAMPLES_DIR   + fileAddr;
    std::string outFile  = TEST_DIR + GENERATED_DIR + logAddr;
    mailbox(inFile, outFile);
    
    std::string genLogStr  = extractFile(outFile);
    std::string sampLogStr = extractFile(TEST_DIR + SAMPLES_DIR + logAddr);
    
    ASSERT_EQ(genLogStr, sampLogStr);
}