#include <iostream>
#include <fstream>
#include <iomanip>
#include "ledger.h"

//void addTransaction(std::string description, float amount) {
//    Transaction t;
//    t.description = description;
//    t.amount = amount;
//    transList.push_back(t);
//}


Profile::Profile() :
    _profileName("Default"),
    _transList(),
    _balance(0)
{}

void Profile::addTransaction(std::string description, float amount) {
    Transaction t;
    t.description = description;
    t.amount = amount;
    this->_transList.push_back(t);
}


void Profile::printTransactionList() {
    for (auto i = this->_transList.begin(); i != this->_transList.end(); ++i) {
        std::cout << (*i).description << (*i).amount << std::endl;
    }
}

//void printTransactionList() {
//// Formatting work in progress
////    std::cout << "------------------------------------------------" << endl;
////    std::cout << "|     Desc     |                      | Amount |" << endl;
////    std::cout << "|-----------------------------------------------" << endl;

//    // Classic for loop, possibly replace with range for or something better?
//    for (auto i = transList.begin(); i != transList.end(); ++i) {
//        std::cout << (*i).description << (*i).amount << std::endl;
//    }
//}

std::string chooseProfile() {
    std::string profileName;
    std::cout << "Welcome to " << PROGRAM::NAME << std::endl
              << "Version: " << PROGRAM::VERSION << std::endl;

    std::cout << "Please enter the profile name you wish to use" << std::endl
              << "(if entered profile name does not exist, you will be prompted to create it)" << std::endl
              << ": ";
    getline(std::cin, profileName);
    if (profileName == "\n")
        return "Default";
    // Error checking

    return profileName;
}

bool menuLoop(Profile &currentProfile) {

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
        std::string description;
        float amount;

        std::cout << "What do you want to call the transaction?" << std::endl << ": ";
        getline(std::cin, description);

        std::cout << "How much was this transaction for? (+ for gaining $, - for spending)" << std::endl << ": ";
        std::cin >> amount;

        currentProfile.addTransaction(description, amount);
        break;
    }

    case 'B' :
    case 'b' :
        currentProfile.printTransactionList();
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

    // Choose account
    std::string profileName = chooseProfile();
    Profile currentProfile;
    bool isDone = true;

    do {
        isDone = menuLoop(currentProfile);
    } while (isDone);

    return 0;
}
