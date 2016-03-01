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
                      << "(Cash, Debit, Credit)" << std::endl;
            printPrompt();
            getline(std::cin, selection);

            type = convertStringToEnum(selection, 1);
            std::cout << selection << ": " << currentProfile.getBalance(type) << std::endl;
            break;
        }

        case 'L' :
        case 'l' :
            currentProfile.printTransactionList();
            break;

        case 'S' :
        case 's' : {
            std::string selection;
            float amount = 0;
            int type;
            std::cout << "What balance would you like to set?" << std::endl
                      << "(Cash, Debit, Credit)" << std::endl;
            printPrompt();
            getline(std::cin, selection);
            std::cout << "What would you like to set the balance to?" << std::endl;
            printPrompt();
            std::cin >> amount;

            type = convertStringToEnum(selection, 1);
            std::cout << selection << " is now " << currentProfile.setBalance(amount, type);
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
    return 0;
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
