#include <iostream>
#include <algorithm>
#include <fstream>
#include "ledger.h"
#include "times.h"

void initialize() {
    // mkdir seems to be standard for windows AND *nixes...so...
    int fSuccess = system("mkdir profiles");
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

        else {
            querySuccess = queryCreateNewProfile(profileName, fileName);
            if (querySuccess)
                return profileName;
        }
    }

    std::cout << "Something went wrong, Default profile loaded, please exit the program normally." << std::endl;
    return "Default";
}

bool menuLoop() {

    // Choose account
    Profile currentProfile(chooseProfile());
    char selection;

    while (true) {
        std::cout << "Please make a selection"  << std::endl
                  << "A: Add a transaction"     << std::endl
                  << "D: Delete a transaction"  << std::endl
                  << "L: View transaction list" << std::endl
                  << "B: View account balances" << std::endl
                  << "S: Set account balances"  << std::endl
                  << "Q: Quit the program"      << std::endl;
        printPrompt();
        std::cin >> selection;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

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
            std::cout << selection << ": " << currentProfile.getBalance(chooseWallet()) << std::endl;
            break;
        }

        case 'L' :
        case 'l' :
            currentProfile.printTransactionList();
            break;

        case 'S' :
        case 's' : {
            int chosenWallet = chooseWallet();
            int chosenAmount = chooseAmount();

            std::cout << "The chosen wallet balance" << " is now " << currentProfile.setBalance(chosenAmount, chosenWallet);
        }

        case 'Q' :
        case 'q' :
            return false;

        default:
            return true;
        }
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


void printPrompt() {
    std::cout << promptTimeFetch() << "> ";
}

int convertStringToEnum(std::string attribute, int conversionType) {
    std::transform( attribute.begin(), attribute.end(), attribute.begin(), ::tolower);
    if (conversionType == 1) {
        if ( attribute == "cash" )
            return 0;
        if ( attribute == "credit" )
            return 1;
        if ( attribute == "debit" )
            return 2;
        else return (-1);
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
        else return (-1);
    }
    return 0;
}


std::string convertEnumToString(int enumToConvert, int conversionType) {

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


int chooseWallet() {
    std::string selection;

    std::cout << "Which wallet are you using?"
              << "(Cash, Credit, Debit)" << std::endl;
    printPrompt();

    while (getline(std::cin, selection)) {
        if (std::cin.fail()) {
            std::cin.clear();
            std::cout << "Incorrect input, please try again" << std::endl;
            printPrompt();
            continue;
        }
        std::transform(selection.begin(), selection.end(), selection.begin(), ::tolower);

        int walletEnum = convertStringToEnum(selection, 1);

        if (walletEnum == (-1)) {
            std::cout << "Text entered did not match the available wallets, please try again." << std::endl;
            printPrompt();
            continue;
        } else {
            return walletEnum;
        }
    }

    std::cout << "Error: Choosing wallet failed. Cash chosen as default. Please try again from the menu" << std::endl;
    return 0;
}

int chooseAttribute() {
    std::string selection;

    std::cout << "How would you like to label this transaction?"
              << "(Novelty,Food,Restaurant,Clothing,Gas,Bill,Vice,Home)" << std::endl;
    printPrompt();

    while (getline(std::cin, selection)) {
        if (std::cin.fail()) {
            std::cin.clear();
            std::cout << "Incorrect input, please try again" << std::endl;
            printPrompt();
            continue;
        }
        std::transform(selection.begin(), selection.end(), selection.begin(), ::tolower);

        int walletEnum = convertStringToEnum(selection, 2);

        if (walletEnum == (-1)) {
            std::cout << "Text entered did not match the available attributes, please try again." << std::endl;
            printPrompt();
            continue;
        } else {
            return walletEnum;
        }
    }

    std::cout << "Error: Choosing wallet failed. Cash chosen as default. Please try again from the menu" << std::endl;
    return 0;
}

float chooseAmount() {

    std::string selection;

    std::cout << "What amount would you like to enter?" << std::endl;
    printPrompt();
    while (getline(std::cin, selection)) {
        if (std::cin.fail()) {
            std::cin.clear();
            std::cout << "Input failed, please try again." << std::endl;
            printPrompt();
            continue;
        }

        for (auto& i : selection) {
            if (!(isdigit(i)))
                continue;
            else return std::stof(selection);
        }
    }
    std::cout << "Error: Defaulted to 0. Please try again from the menu" << std::endl;
    return 0;
}

std::string chooseDescription() {
    std::string selection;
    std::cout << "What is the transaction description?" << std::endl;
    printPrompt();
    getline(std::cin, selection);

    while (true) {
        if (std::cin.fail()) {
            std::cin.clear();
            std::cout << "Input failed, please try again." << std::endl;
            printPrompt();
            continue;
        }
        else if (std::any_of( selection.begin(), selection.end(), ::isspace) ) {
            std::cout << "Profile name must not contain spaces" << std::endl;
            continue;
        }
        else if ( !(std::all_of( selection.begin(), selection.end(), ::isalpha))) {
            std::cout << "Profile name can only contain alphabet characters!" << std::endl;
            continue;
        } else {
            return selection;
        }
    }
    std::cout << "Error: Defaulted to 'null'. Please try again from the menu" << std::endl;
    return "null";
}

int main( ) {

    // Initialize settings and stuff
    initialize();

    // Read profile file
    bool isDone = true;

    do {
        isDone = menuLoop();
    } while (isDone);

    return 0;
}
