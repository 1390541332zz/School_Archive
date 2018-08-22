/*
 * Purpose for program: This program provides an interactive command line
 * variant of Blackjack / Natural 21.
 *
 * Programmer: Jacob Abel
 * Date: Febuary 4, 2017
 *
 * Honor Code: I have neither given nor received any unauthorized assistance
 * with this program.
 */

#include "project1.h"

int main() {
    return blackjack("input.txt", "output.txt");
}

int blackjack(string fileIn, string fileOut) {

    unsigned int score1 = 0;
    unsigned int score2 = 0;

    string cardList;
    string cardList1;
    string cardList2;
    string card;
    ifstream in(fileIn);
    ofstream out(fileOut);

    in >> card;
    while (!in.fail()) {
        unsigned int count = 0;
        while (count < 17 && !in.fail()) {
            if (card.compare("A") == 0) {
                count < 11 ? count += 11 : count += 1;
            } else if (card.compare("J") == 0 || card.compare("Q") == 0 \
            || card.compare("K") == 0) {
                count += 10;
            } else {
                count += stoi(card);
            }

            cardList.push_back(' ');
            cardList.append(card);
            in >> card;
        }
        score1 == 0 ? score1 = count : score2 = count;
        cardList1.empty() ? cardList1.append(cardList) \
                          : cardList2.append(cardList);

        cardList.clear();
    }

    out << "Player one's cards:" << cardList1 << endl;
    out << "Player two's cards:" << cardList2 << endl;

    out << "Game Over" << endl;

    if (score1 > 21 && score2 > 21) {
        out << "Everyone busted" << endl;
    } else if (score1 == score2) {
        out << "Push" << endl;
    } else if (score1 <= 21 && (score1 > score2 || score2 > 21)) {
        out << "Player one won" << endl;
    } else {
        out << "Player two won" << endl;
    }

    out << "Player one sum: " << score1 << endl;
    out << "Player two sum: "  << score2 << endl;

    in.close();
    out.close();
    return 0;
}
