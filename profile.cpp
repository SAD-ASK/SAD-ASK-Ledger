#include <iostream>
#include <algorithm>
#include <iomanip>
#include <fstream>
#include <sstream>
#include "profile.h"
#include "main.h"
#include "times.h"


Profile::Profile() :
    _profileName(this->chooseProfile()),
    _fileName("profiles/" + _profileName + ".txt"),
    _unsavedEdits(false)
{ loadFile(); }


Profile::~Profile() {
    if (this->_unsavedEdits) {
        this->saveToFile();
    }
}


std::string Profile::chooseProfile() {

    bool querySuccess = false;
    std::string profileName;
    std::cout << "Welcome to " << Globals::NAME    << std::endl
              << "Version: "   << Globals::VERSION << std::endl;

    while (true) {
        do {
            std::cout << "Please enter the profile name you wish to use" << std::endl
                      << "(if entered profile name does not exist, you will be prompted to create it)." << std::endl
                      << "For simplicity's sake, the profile name must be only alphabetic characters, no spaces!" << std::endl;
            printPrompt();

            if (getline(std::cin, profileName)) {
                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cout << "Incorrect input, try again" << std::endl;
                    continue;
                }
                if (std::any_of( profileName.begin(), profileName.end(), ::isspace) ) {
                    std::cout << "Profile name must not contain spaces" << std::endl;
                    continue;
                }
                if ( !(std::all_of( profileName.begin(), profileName.end(), ::isalpha))) {
                    std::cout << "Profile name can only contain alphabet characters!" << std::endl;
                    continue;
                }
                else querySuccess = true;
            }
        } while (!querySuccess);


        std::string fileName = "profiles/" + profileName + ".txt";

        // Return if exists already
        if (std::ifstream(fileName))
            return profileName;
        //loadedProfile = std::unique_ptr<Profile>(new Profile(profileName));

        else {
            querySuccess = this->queryCreateNewProfile(profileName, fileName);
            if (querySuccess)
                return profileName;
            //loadedProfile = std::unique_ptr<Profile>(new Profile(profileName));
        }
    }

    std::cout << "Something went wrong, Default profile loaded, please exit the program normally." << std::endl;
    return "Default";
}

bool Profile::queryCreateNewProfile(std::string profileName, std::string fileName) {
    char selection;
    bool profileCreated = false;

    do {

        std::cout << "Profile " << profileName << " does not exist, create?" << std::endl
                  << "(y/n)"    << std::endl;
        printPrompt();
        std::cin >> selection;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

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

void Profile::addTransaction() {

    // Calling all required functions for transaction info
    std::string stringDescription = chooseDescription();
    float floatAmount = chooseAmount();
    int enumAttribute = chooseAttribute();
    int enumTender = chooseWallet();


    // Transaction to append to vector of transactions
    // improve?
    Globals::Transaction t;
    t.description = stringDescription;
    t.amount = floatAmount;
    t.attribute = enumAttribute;
    t.tenderType = enumTender;
    t.transactionTimestamp = createTimestamp();

    if (this->_transList.empty()) {
        t.id = 0;
    } else t.id = this->_transList.back().id + 1;

    this->_transList.push_back(t);
    _balance[enumTender] += floatAmount;

    this->_unsavedEdits = true;
}


void Profile::printTransactionList() {

    // Column width's listed by print order (subject to change)
    const int idColumn = 4;
    const int descriptionColumn = 20;
    const int attributeColumn = 16;
    const int walletColumn = 10;
    const int amountColumn = 10;
    const int timestampColumn = 16;

    // Set decimal settings for output
    std::cout << std::fixed << std::showpoint << std::setprecision(2);

    // Heading, the -2 accounts for the "| " dividing each section of the table
    std::cout << "| " << std::setw(idColumn - 2) << "ID"
              << "| " << std::setw(descriptionColumn - 2) << "Description"
              << "| " << std::setw(attributeColumn - 2)   << "Attribute"
              << "| " << std::setw(walletColumn - 2)        << "Wallet"
              << "| " << std::setw(timestampColumn -2) << "Date created"
              << "| " << std::right << std::setw(amountColumn - 2) << "Amount"
              << "|" << std::endl;

    std::cout << "|" << std::string((idColumn - 1), '-')
              << "|" << std::string((descriptionColumn - 1), '-')
              << "|" << std::string((attributeColumn - 1), '-')
              << "|" << std::string((walletColumn - 1), '-')
              << "|" << std::string((timestampColumn - 1), '-')
              << "|" << std::string((amountColumn - 1), '-')
              << "|" << std::endl;

    for (auto &i : this->_transList) {
        std::cout << "| " << std::left << std::setw(idColumn - 2) << i.id
                  << "| " << std::left  << std::setw(descriptionColumn - 2) << i.description
                  << "| " << std::right << std::setw(attributeColumn - 2) << convertEnumToString(i.attribute, 2)
                  << "| " << std::right << std::setw(walletColumn - 2) << convertEnumToString(i.tenderType, 1)
                  << "| " << std::right << std::setw(timestampColumn - 2) << getLocaltime(i.transactionTimestamp)
                  << "| " << std::setw(amountColumn - 2) << std::right << i.amount << "|"
                  << std::endl;
    }
}



void Profile::deleteTransaction() {
    int selection;
    bool isFound = false;

    while (!(isFound)) {
        selection = chooseID();
        for (auto &i : this->_transList) {
            if (i.id == selection) {
                isFound = true;
                break;
            }

            if ((selection < 1) || (selection > this->_transList.back().id)) {
                std::cout << "Incorrect input, correct range of Ids is: ";
                std::cout << "1 - " << this->_transList.back().id << std::endl;
                continue;
            }
        }
    }

    // my first lambda
    this->_transList.erase(std::remove_if(this->_transList.begin(), this->_transList.end(),
                                          [this, selection](Globals::Transaction const& t)->bool {
        return t.id == selection; }), this->_transList.end());
    this->_unsavedEdits = true;
}



void Profile::saveToFile() {
    std::ofstream file;

    file.open(this->_fileName.c_str(),std::ios::trunc);
    if (file.is_open()) {
        for (auto i = this->_transList.begin(); i != this->_transList.end(); i++) {
            file << (*i).description << "|"
                 << (*i).attribute << "|"
                 << (*i).tenderType << "|"
                 << (*i).transactionTimestamp << "|"
                 << (*i).amount  << "\n";
        }
    }
    file.close();
}


void Profile::reindexID() {
    int idCounter = 0;
    for (auto i = this->_transList.begin(); i != this->_transList.end(); ++i) {
        idCounter++;
        (*i).id = idCounter;
    }
}

void Profile::loadFile() {
    std::ifstream file;
    std::string entry;
    int idNumberCounter = 0;

    file.open(this->_fileName);
    if (file.is_open()) {
        while (getline(file,entry)) {
            idNumberCounter++;
            this->_transList.push_back(this->convertEntryToTransaction(entry));
            this->_transList.back().id = idNumberCounter;
        }
        for (auto i = this->_transList.begin(); i != this->_transList.end(); i++) {
            this->_balance[(*i).tenderType] += (*i).amount;
        }
    }
}


struct Globals::Transaction Profile::convertEntryToTransaction(std::string entry) {

    Globals::Transaction t;
    std::vector<std::string> vectorOfSubstrings;
    std::string tempString;
    std::istringstream ss(entry);

    while (getline(ss, tempString, '|')) {
        vectorOfSubstrings.push_back(tempString);
    }

    t.description = vectorOfSubstrings[0];
    t.attribute = std::stoi(vectorOfSubstrings[1]);
    t.tenderType = std::stoi(vectorOfSubstrings[2]);
    t.transactionTimestamp = std::stoi(vectorOfSubstrings[3]);
    t.amount = std::stof(vectorOfSubstrings[4]);
    return t;
}
