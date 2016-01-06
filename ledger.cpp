#include <iostream>
#include <fstream>
#include <iomanip>
#include "ledger.h"

void addTransaction(std::string description, float amount) {
    Transaction t;
    t.description = description;
    t.amount = amount;
    transList.push_back(t);
}

void printTransactionList() {
// Formatting work in progress
//    std::cout << "------------------------------------------------" << endl;
//    std::cout << "|     Desc     |                      | Amount |" << endl;
//    std::cout << "|-----------------------------------------------" << endl;

    // Classic for loop, possibly replace with range for or something better?
    for (auto i = transList.begin(); i != transList.end(); ++i) {
        std::cout << (*i).description << (*i).amount << std::endl;
    }
}

bool menuLoop(int loopCounter) {

    if (loopCounter == 1) {
        std::cout << "Welcome to my Ledger!" << std::endl
                  << "(super alpha)" << std::endl;
    }

    char selection;
    std::cout << "Please make a selection" << std::endl
              << "A: Add a transaction" << std::endl
              << "B: View transaction list" << std::endl
              << "C: Quit the program" << std::endl;
    std::cout << "Selection: ";
    std::cin >> selection;

    switch (selection) {
    case 'A' :
    case 'a' : {
        float amount;
        std::string description;

        std::cout << "What do you want to call the transaction?" << std::endl << ": ";
        std::cin >> description;

        std::cout << "How much was this transaction for? (+ for gaining $, - for spending)" << std::endl << ": ";
        std::cin >> amount;

        addTransaction(description, amount);
        break;
    }

    case 'B' :
    case 'b' :
        printTransactionList();
        break;
    case 'C' :
    case 'c' :
        return false;

    default:
        return true;
    }
    return true;
}

int main( ) {

    static int loopCounter = 0;
    bool isDone = true;
    do {
        loopCounter++;
        isDone = menuLoop(loopCounter);
    } while (isDone);

    return 0;
}
