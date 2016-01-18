#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <algorithm>
#include "ledger.h"


void initialize() {
    // mkdir seems to be standard for windows AND *nixes...so...
    int fSuccess = system("mkdir profiles");
}

// Never to see the light of day...
Profile::Profile() :
    _profileName("Default"),
    _transList(),
    _balance(0)
{}


Profile::Profile(std::string profileName) :
    _profileName(profileName),
    _transList(),
    _balance(0),
    _fileName("profiles/" + profileName + ".txt")
{
    // Loads profile file
    loadFile();
}


void Profile::addTransaction() {
    std::string description;
    float amount;

    std::cout << "What do you want to call the transaction?" << std::endl << ": ";
    getline(std::cin, description);

    std::cout << "How much was this transaction for? (+ for gaining $, - for spending)" << std::endl << ": ";
    std::cin >> amount;


    Transaction t;
    t.description = description;
    t.amount = amount;
    t.id = this->_transList.back().id + 1;
    this->_transList.push_back(t);
    this->_balance += amount;
    saveToFile(t);
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



void Profile::deleteTransaction() {
    int selection;

    std::cout << "What is the id number of the transaction you wish to remove?" << std::endl
              << ": ";
    do {
        std::cin >> selection;
        if ((selection < 1) || (selection > this->_transList.back().id)) {
            std::cout << "Incorrect input, correct range of Ids is: ";
            std::cout << "1 - " << this->_transList.back().id << std::endl;
        }
    } while ((selection < 1) || (selection > this->_transList.back().id));

    for (auto i = this->_transList.begin(); i != this->_transList.end(); ++i) {
        if ( (*i).id == selection ) {
            (*i).id = 0;
        }
    }
    // my first lambda
    this->_transList.erase(std::remove_if(this->_transList.begin(), this->_transList.end(),
                                       [](Transaction const& t) { return t.id == 0; }), this->_transList.end());
}


void Profile::saveToFile(struct Transaction transaction) {
    std::ofstream file;
    file.open(this->_fileName,std::ios::app);
    if (file.is_open()) {
        file << transaction.description << "|"
             << transaction.amount      << "\n";
        file.close();
    }
    else std::cout << "Unable to open file, exiting" << std::endl;
}


void Profile::loadFile() {
    std::ifstream file;
    std::string entry;
    int idNumberCounter = 0;

    file.open(this->_fileName);
    if (file.is_open()) {
        while (getline(file,entry)) {
            idNumberCounter++;
            this->_transList.push_back(convertEntryToTransaction(entry));
            this->_transList.back().id = idNumberCounter;
        }
    }
}


struct Transaction Profile::convertEntryToTransaction(std::string entry) {
    Transaction t;

    std::size_t startPos = 0;
    std::size_t nextTokenPos;
    std::string subString;

    // Gets description
    t.description = entry.substr(0, nextTokenPos = entry.find("|"));
    startPos = nextTokenPos + 1;

    // Gets amount
    subString = entry.substr(startPos, nextTokenPos = entry.find("\n"));
    t.amount = std::stof(subString);

    return t;
}


std::string chooseProfile() {
    bool querySuccess = false;
    do  {
        std::string profileName;
        std::cout << "Welcome to " << PROGRAM::NAME    << std::endl
                  << "Version: "   << PROGRAM::VERSION << std::endl;

        std::cout << "Please enter the profile name you wish to use" << std::endl
                  << "(if entered profile name does not exist, you will be prompted to create it)" << std::endl
                  << ": ";
        getline(std::cin, profileName);

        // Error checking

        // default if it were working...
        std::string fileName = "profiles/" + profileName + ".txt";

        // Return if exists already
        if (std::ifstream(fileName))
            return profileName;

        else {
            querySuccess = queryCreateNewProfile(profileName, fileName);
            if (querySuccess)
                return profileName;
        }

    } while (!querySuccess);

    std::cout << "Something went wrong, Default profile loaded" << std::endl;
    return "Default";
}

bool menuLoop(Profile &currentProfile) {

    char selection;

    std::cout << "Please make a selection"  << std::endl
              << "A: Add a transaction"     << std::endl
              << "D: Delete a transaction"  << std::endl
              << "L: View transaction list" << std::endl
              << "Q: Quit the program"      << std::endl;
    std::cout << "Selection: ";
    std::cin >> selection;
    std::cin.ignore();

    switch (selection) {
    case 'A' :
    case 'a' :
        currentProfile.addTransaction();
        break;

    case 'D' :
    case 'd' :
        currentProfile.deleteTransaction();
        break;

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


bool queryCreateNewProfile(std::string profileName, std::string fileName) {
    char selection;
    bool profileCreated = false;

    do {

        std::cout << "Profile " << profileName << " does not exist, create?" << std::endl
                  << "(y/n): ";
        std::cin >> selection;
        if ( !( (selection == 'y') | (selection == 'n') ) )
            std::cout << "Incorrect input, please enter y or n to answer" << std::endl;
    } while ( !((selection == 'y') | (selection == 'n')) );

    if (selection == 'y') {
        std::fstream file;
        file.open(fileName, std::ios::out);
        file << std::flush;
        file.close();
        profileCreated = true;
        std::cout << "File should be created..." << std::endl;
    }

    return profileCreated;
}


int main( ) {

    // Initialize settings and stuff
    initialize();

    // Choose account
    std::string profileName = chooseProfile();
    Profile currentProfile(profileName);

    // Read profile file
    std::fstream currentFile;
    bool isDone = true;

    do {
        isDone = menuLoop(currentProfile);
    } while (isDone);

    return 0;
}
