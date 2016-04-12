#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include "globals.h"
#include "core.h"
#include "main.h"

// for printPrompt
#include "times.h"



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
    //printPrompt();

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

    std::cout << "Error: Choosing attribute failed. Novelty chosen as default. Please try again from the menu." << std::endl;
    return 0;
}


bool isFloat(int character) {
    if ((character == '.') || (isdigit(character))) {
        return true;
    } else return false;
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

        if (!(std::all_of(selection.begin(), selection.end(), ::isFloat))) {
            std::cout << "Input contained non-numeric characters. Please try again." << std::endl;
            printPrompt();
            continue;
        } else return std::stof(selection);
    }
    std::cout << "Error: Defaulted to 0. Please try again from the menu" << std::endl;
    return 0;
}


std::string chooseDescription() {
    std::string selection;
    std::cout << "What is the transaction description?" << std::endl;
    printPrompt();

    while (getline(std::cin, selection)) {
        if (std::cin.fail()) {
            std::cin.clear();
            std::cout << "Input failed, please try again." << std::endl;
            printPrompt();
            continue;
        }
        if (!(std::all_of(selection.begin(), selection.end(), ::isalpha))) {
            std::cout << "Profile name can only contain alphabetic characters!" << std::endl;
            printPrompt();
            continue;
        } else return selection;

    }
    std::cout << "Error: Defaulted to 'null'. Please try again from the menu" << std::endl;
    return "null";
}


int chooseID() {
    std::string selection;
    std::cout << "Enter a transaction ID" << std::endl;
    printPrompt();

    while (getline(std::cin, selection)) {
        if (std::cin.fail()) {
            std::cin.clear();
            std::cout << "Input error. Please try again." << std::endl;
            printPrompt();
            continue;
        }

        if (!(std::all_of(selection.begin(), selection.end(), ::isdigit))) {
            std::cout << "ID entered contains non-numeric characters. Please try again" << std::endl;
            printPrompt();
            continue;
        } else return std::stoi(selection);
    }

    std::cout << "Error: Please try again from menu" << std::endl;
    return (-1);
}


int main(int argc, char* argv[]) {

    Core core;

    return 0;
}
