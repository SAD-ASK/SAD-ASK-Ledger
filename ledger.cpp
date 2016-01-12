#include <iostream>
#include <fstream>
#include <iomanip>
#include "ledger.h"

// Never to see the light of day...
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
    this->_balance += amount;
}


void Profile::printTransactionList() {

    const int width1 = 30; // subject to change
    const int width2 = 19;

    // Set decimal settings for output
    std::cout << std::fixed << std::showpoint << std::setprecision(2);


    // Heading
    // First column (first pipe to second pipe) is 30 characters
    // Second column is 19 characters
    std::cout << "| " << std::left  << std::setw(width1 - 2) << "Description"
              << "| " << std::right << std::setw(width2 - 2) << "Amount"      << "|"
              << std::endl;
    std::cout << "|" << std::string(29, '-') << "|" << std::string(18, '-') << "|" << std::endl;

    for (auto &i : this->_transList) {
        std::cout << "| " << std::left     << std::setw(width1 - 2) << i.description
                  << "| " << std::setw(17) << std::right            << i.amount << "|"
                  << std::endl;
    }
}


std::string chooseProfile() {
    while (true) {
        std::string profileName;
        std::cout << "Welcome to " << PROGRAM::NAME    << std::endl
                  << "Version: "   << PROGRAM::VERSION << std::endl;

        std::cout << "Please enter the profile name you wish to use" << std::endl
                  << "(if entered profile name does not exist, you will be prompted to create it)" << std::endl
                  << ": ";
        getline(std::cin, profileName);
        // Error checking

        std::string fileName = "profiles/" + profileName + ".txt";

        // Return if exists already
        if (std::ifstream(fileName)) {
            return profileName;
        }
        else return queryCreateNewProfile(profileName, fileName)

        }
    }
}

bool menuLoop(Profile &currentProfile) {

    char selection;

    std::cout << "Please make a selection" << std::endl
              << "A: Add a transaction" << std::endl
              << "L: View transaction list" << std::endl
              << "Q: Quit the program" << std::endl;
    std::cout << "Selection: ";
    std::cin >> selection;
    std::cin.ignore();

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

    case 'L' :
    case 'l' :
        currentProfile.printTransactionList();
        break;
    case 'Q' :
    case 'q' :
        return false;

    default:
        return true;
    }
    return true;
}


std::string queryCreateNewProfile(std::string profileName, std::string fileName) {
    char selection;
    do {
    std::cout << "Profile " << profileName << " does not exist, create?" << std::endl
              << "(y/n): ";
    std::cin >> selection;
    if ( !( (selection == 'y') | (selection == 'n') ) )
        std::cout << "Incorrect input, please enter y or n to answer" << std::endl;
    } while ( (selection == 'y') | (selection == 'n') );

    if (selection == 'y') {
        std::fstream file;
        file.open(fileName, std::fstream::out);
        file.close();
        return fileName;
    }
    else
        // WHERE I LEFT OFF
}

int main( ) {

    // Choose account
    std::string profileName = chooseProfile();
    Profile currentProfile;
    std::fstream currentFile;
    bool isDone = true;

    do {
        isDone = menuLoop(currentProfile);
    } while (isDone);

    return 0;
}
