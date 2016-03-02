#include <iostream>
#include <algorithm>
#include <iomanip>
#include <fstream>
#include <sstream>
#include "ledger.h"
#include "times.h"


Profile::Profile() :
    _profileName("Default"),
    _unsavedEdits(false)
{}



Profile::Profile(std::string profileName) :
    _profileName(profileName),
    _fileName("profiles/" + profileName + ".txt"),
    _unsavedEdits(false)
{ loadFile(); }


Profile::~Profile() {
    if (this->_unsavedEdits) {
        this->saveToFile();
    }
}


void Profile::addTransaction() {

    // Calling all required functions for transaction info
    std::string stringDescription = chooseDescription();
    float floatAmount = chooseAmount();
    int enumAttribute = chooseAttribute();
    int enumTender = chooseWallet();


    // Transaction to append to vector of transactions
    // improve?
    Transaction t;
    t.description = stringDescription;
    t.amount = floatAmount;
    t.attribute = enumAttribute;
    t.tenderType = enumTender;
    t.creationTimestamp = createTimestamp();

    if (this->_transList.empty()) {
        t.id = 0;
    } else t.id = this->_transList.back().id + 1;

    this->_transList.push_back(t);
    _balance[enumTender] += floatAmount;

    this->_unsavedEdits = true;
}


void Profile::withdrawl() {


}

void Profile::printTransactionList() {

    // Column width's listed by print order (subject to change)
    const int descriptionColumn = 20;
    const int attributeColumn = 16;
    const int walletColumn = 10;
    const int amountColumn = 10;
    const int timestampColumn = 16;

    // Set decimal settings for output
    std::cout << std::fixed << std::showpoint << std::setprecision(2);

    // Heading, the -2 accounts for the "| " dividing each section of the table
    std::cout << "| " << std::setw(descriptionColumn - 2) << "Description"
              << "| " << std::setw(attributeColumn - 2)   << "Attribute"
              << "| " << std::setw(walletColumn - 2)        << "Wallet"
              << "| " << std::setw(timestampColumn -2) << "Date created"
              << "| " << std::right << std::setw(amountColumn - 2) << "Amount"
              << "|" << std::endl;

    std::cout << "|" << std::string((descriptionColumn - 1), '-')
              << "|" << std::string((attributeColumn - 1), '-')
              << "|" << std::string((walletColumn - 1), '-')
              << "|" << std::string((timestampColumn - 1), '-')
              << "|" << std::string((amountColumn - 1), '-')
              << "|" << std::endl;

    for (auto &i : this->_transList) {
        std::cout << "| " << std::left  << std::setw(descriptionColumn - 2) << i.description
                  << "| " << std::right << std::setw(attributeColumn - 2) << convertEnumToString(i.attribute, 2)
                  << "| " << std::right << std::setw(walletColumn - 2) << convertEnumToString(i.tenderType, 1)
                  << "| " << std::right << std::setw(timestampColumn - 2) << getLocaltime(i.creationTimestamp)
                  << "| " << std::setw(amountColumn - 2) << std::right << i.amount << "|"
                  << std::endl;
    }
}



void Profile::deleteTransaction() {
    int selection;

    std::cout << "What is the id number of the transaction you wish to remove?" << std::endl;
    printPrompt();
    do {
        std::cin >> selection;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
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

    this->_unsavedEdits = true;
}



void Profile::saveToFile() {
    std::ofstream file;

    file.open(this->_fileName,std::ios::trunc);
    if (file.is_open()) {
        for (auto i = this->_transList.begin(); i != this->_transList.end(); i++) {
            file << (*i).description << "|"
                 << (*i).attribute << "|"
                 << (*i).tenderType << "|"
                 << (*i).creationTimestamp << "|"
                 << (*i).amount  << "\n";
        }
    }
    file.close();
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
        for (auto i = this->_transList.begin(); i != this->_transList.end(); i++) {
            this->_balance[(*i).tenderType] += (*i).amount;
        }
    }
}


struct Transaction Profile::convertEntryToTransaction(std::string entry) {

    Transaction t;
    std::vector<std::string> vectorOfSubstrings;
    std::string tempString;
    std::istringstream ss(entry);

    while (getline(ss, tempString, '|')) {
        vectorOfSubstrings.push_back(tempString);
    }

    t.description = vectorOfSubstrings[0];
    t.attribute = std::stoi(vectorOfSubstrings[1]);
    t.tenderType = std::stoi(vectorOfSubstrings[2]);
    t.creationTimestamp = std::stoi(vectorOfSubstrings[3]);
    t.amount = std::stof(vectorOfSubstrings[4]);
    return t;

}
