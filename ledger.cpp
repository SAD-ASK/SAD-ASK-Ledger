#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <sstream>
#include "ledger.h"


void initialize() {
    // mkdir seems to be standard for windows AND *nixes...so...
    int fSuccess = system("mkdir profiles");
}

// Never to see the light of day...
//Profile::Profile() {
//    this->_profileName = "Default";
//    this->_unsavedEdits = false;
//}

Profile::Profile() :
    _profileName("Default"),
    _unsavedEdits(false)
{}


//Profile::Profile(std::string profileName) {
//    this->_profileName = profileName;
//    this->_fileName = ("profiles/" + profileName + ".txt");
//    this->_unsavedEdits = false;
//    // Loads profile file
//    loadFile();
//}

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


//void Profile::saveToFile(struct Transaction transaction) {
//    std::ofstream file;
//    file.open(this->_fileName,std::ios::app);
//    if (file.is_open()) {
//        file << transaction.description << "|"
//             << transaction.amount      << "\n";
//        file.close();
//    }
//    else std::cout << "Unable to open file, exiting" << std::endl;
//}


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

//    std::size_t startPos = 0;
//    std::size_t nextTokenPos;
//    std::string subString;

//    // Gets description
//    t.description = entry.substr(0, nextTokenPos = entry.find("|"));
//    startPos = nextTokenPos + 1;


//    // Gets amount
//    subString = entry.substr(startPos, nextTokenPos = entry.find("|"));
//    t.amount = std::stof(subString);
//    startPos = nextTokenPos + 1;

//    // Gets tender type
//    subString = entry.substr(startPos, nextTokenPos = entry.find("\n"));
//    t.tenderType = std::stoi(subString);

//    return t;

    // NEW STUFF

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


std::string chooseProfile() {
    bool querySuccess = false;
    std::string profileName;
    std::cout << "Welcome to " << PROGRAM::NAME    << std::endl
              << "Version: "   << PROGRAM::VERSION << std::endl;

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
                if ( !(std::any_of( profileName.begin(), profileName.end(), ::isalpha))) {
                    std::cout << "Profile name can only contain alphabet characters!" << std::endl;
                    continue;
                }
                else querySuccess = true;
            }
        } while (!querySuccess);


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
    }

    std::cout << "Something went wrong, Default profile loaded, please exit the program normally." << std::endl;
    return "Default";
}

bool menuLoop(Profile &currentProfile) {

    char selection;

    std::cout << "Please make a selection"  << std::endl
              << "A: Add a transaction"     << std::endl
              << "D: Delete a transaction"  << std::endl
              << "L: View transaction list" << std::endl
              << "B: View account balances" << std::endl
              << "Q: Quit the program"      << std::endl;
    printPrompt();
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

    case 'B' :
    case 'b' : {
        std::string selection;
        int type;
        std::cout << "What balance would you like to view?" << std::endl
                  << "(Cash, Debit, Credit" << std::endl;
        printPrompt();
        getline(std::cin, selection);

        type = currentProfile.convertStringToEnum(selection, 1);
        std::cout << selection << ": " << currentProfile.getBalance(type) << std::endl;
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


bool queryCreateNewProfile(std::string profileName, std::string fileName) {
    char selection;
    bool profileCreated = false;

    do {

        std::cout << "Profile " << profileName << " does not exist, create?" << std::endl
                  << "(y/n)"    << std::endl;
        printPrompt();
        std::cin >> selection;
        std::cin.ignore();
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


void printPrompt() {
    std::cout << "> ";
}

void printPrompt(Profile *profile) {
    std::cout << profile->getFileName() << "> ";
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
