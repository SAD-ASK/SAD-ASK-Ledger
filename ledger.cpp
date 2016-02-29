#include <iostream>
#include <algorithm>
#include <iomanip>
#include <fstream>
#include <sstream>
#include "ledger.h"


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
    std::string description;
    float amount;
    std::string transAttribute;
    int intAttribute;
    std::string transTender;
    int intTender;

    std::cout << "What do you want to call the transaction?" << std::endl;
    printPrompt(this);
    getline(std::cin, description);

    std::cout << "How much was this transaction for? (+ for gaining $, - for spending)" << std::endl;
    printPrompt(this);
    std::cin >> amount;

    std::cout << "What type of transaction is this?" << std::endl
              << "(Novelty,Food,Restaurant,Clothing,Gas,Bill,Vice,Home)" << std::endl;
    printPrompt(this);
    std::cin.ignore();
    getline(std::cin, transAttribute);

    intAttribute = convertStringToEnum(transAttribute, 2);

    std::cout << "What did you pay with?" << std::endl
              << "(Cash, Credit, Debit)"  << std::endl;
    printPrompt(this);
    getline(std::cin, transTender);

    std::cout << transTender << std::endl; // TEST TEST TEST TEST TEST!
    intTender = convertStringToEnum(transTender, 1);




    Transaction t;
    t.description = description;
    t.amount = amount;
    t.attribute = intAttribute;
    t.tenderType = intTender;
    if (this->_transList.empty()) {
        t.id = 0;
    } else t.id = this->_transList.back().id + 1;

    this->_transList.push_back(t);
    _balance[intTender] += amount;

    this->_unsavedEdits = true;
    //saveToFile(t);
}


int Profile::convertStringToEnum(std::string attribute, int conversionType) {
    std::transform( attribute.begin(), attribute.end(), std::back_inserter(attribute), ::tolower);
    if (conversionType == 1) {
        if ( attribute == "cash" )
            return 0;
        if ( attribute == "credit" )
            return 1;
        if ( attribute == "debit" )
            return 2;
        else return 0;
    }
    if (conversionType == 2) {

        if ( attribute == "novelty" )
            return 0;
        if ( attribute == "food" )
            return 1;
        if ( attribute == "restaurant" )
            return 2;
        if ( attribute == "clothing" )
            return 3;
        if ( attribute == "gas" )
            return 4;
        if ( attribute == "bill" )
            return 5;
        if ( attribute == "vice" )
            return 6;
        if ( attribute == "home" )
            return 7;
        else return 0;
    }
    return 0;
}


std::string Profile::convertEnumToString(int enumToConvert, int conversionType) {

    if (conversionType == 1) {
        switch (enumToConvert) {
        case 0 :
            return "Cash";
        case 1 :
            return "Credit";
        case 2 :
            return "Debit";
        default:
            return "null";
        }
    }

    if (conversionType == 2) {
        switch (enumToConvert) {
        case 0 :
            return "Novelty";
        case 1 :
            return "Food";
        case 2 :
            return "Restaurant";
        case 3 :
            return "Clothing";
        case 4 :
            return "Gas";
        case 5 :
            return "Bill";
        case 6 :
            return "Vice";
        case 7 :
            return "Home";
        default :
            return "null";
        }
    }
    else return "null";
}

void Profile::printTransactionList() {

    // Column width's listed by print order (subject to change)
    const int descriptionColumn = 20;
    const int attributeColumn = 16;
    const int walletColumn = 10;
    const int amountColumn = 10;

    // Set decimal settings for output
    std::cout << std::fixed << std::showpoint << std::setprecision(2);

    // Heading
    std::cout << "| " << std::setw(descriptionColumn - 2) << "Description"
              << "| " << std::setw(attributeColumn - 2)   << "Attribute"
              << "| " << std::setw(walletColumn - 2)        << "Wallet"
              << "| " << std::right << std::setw(amountColumn - 2) << "Amount"
              << "|" << std::endl;

    std::cout << "|" << std::string((descriptionColumn - 1), '-')
              << "|" << std::string((attributeColumn - 1), '-')
              << "|" << std::string((walletColumn - 1), '-')
              << "|" << std::string((amountColumn - 1), '-')
              << "|" << std::endl;

    for (auto &i : this->_transList) {
        std::cout << "| " << std::left  << std::setw(descriptionColumn - 2) << i.description
                  << "| " << std::right << std::setw(attributeColumn - 2) << this->convertEnumToString(i.attribute, 2)
                  << "| " << std::right << std::setw(walletColumn - 2) << this->convertEnumToString(i.tenderType, 1)
                  << "| " << std::setw(amountColumn - 2) << std::right << i.amount << "|"
                  << std::endl;
    }
}



void Profile::deleteTransaction() {
    int selection;

    std::cout << "What is the id number of the transaction you wish to remove?" << std::endl;
    printPrompt(this);
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

    this->_unsavedEdits = true;
}



// ADD ATTRIBUTE TO SAVEFILE
void Profile::saveToFile() {
    std::ofstream file;

    file.open(this->_fileName,std::ios::trunc);
    if (file.is_open()) {
        for (auto i = this->_transList.begin(); i != this->_transList.end(); i++) {
            file << (*i).description << "|"
                 << (*i).amount      << "|"
                 << (*i).tenderType  << "\n";
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
    t.amount = std::stof(vectorOfSubstrings[1]);
    t.tenderType = std::stoi(vectorOfSubstrings[2]);
    return t;

}
