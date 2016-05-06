#include "input.h"
#include "times.h"

#include <algorithm>
#include <iostream>

void printPrompt() {
    std::cout << promptTimeFetch() << "> ";
}


int convertStringToEnum(std::string attribute, int conversionType) {
    std::transform( attribute.begin(), attribute.end(), attribute.begin(), ::tolower);
    if (conversionType == 1) {
        if ( attribute == "cash" )
            return 0;
        if ( attribute == "checking" )
            return 1;
        if ( attribute == "savings" )
            return 2;
        if ( attribute == "credit" )
            return 3;

        else return (-1);
    }
    if (conversionType == 2) {

        if ( attribute == "auto" )
            return 0;
        if ( attribute == "bill" )
            return 1;
        if ( attribute == "charity" )
            return 2;
        if ( attribute == "clothes" )
            return 3;
        if ( attribute == "computer" )
            return 4;
        if ( attribute == "dining" )
            return 5;
        if ( attribute == "education" )
            return 6;
        if ( attribute == "entertainment" )
            return 7;
        if ( attribute == "gift" )
            return 8;
        if ( attribute == "groceries" )
            return 9;
        if ( attribute == "hobbies" )
            return 10;
        if ( attribute == "home" )
            return 11;
        if ( attribute == "laundry" )
            return 12;
        if ( attribute == "medical" )
            return 13;
        if ( attribute == "novelty" )
            return 14;
        if ( attribute == "phone" )
            return 15;
        if ( attribute == "transportation" )
            return 16;
        if ( attribute == "vice" )
            return 17;

        else return (-1);
    }
    return 0;
}


//std::string convertEnumToString(int enumToConvert, int conversionType) {

//    if (conversionType == 1) {
//        switch (enumToConvert) {
//        case 0 :
//            return "Cash";
//        case 1 :
//            return "Checking";
//        case 2 :
//            return "Savings";
//        case 3 :
//            return "Credit";
//        default:
//            return "null";
//        }
//    }

//    if (conversionType == 2) {
//        switch (enumToConvert) {
//        case 0 :
//            return "Novelty";
//        case 1 :
//            return "Food";
//        case 2 :
//            return "Restaurant";
//        case 3 :
//            return "Clothing";
//        case 4 :
//            return "Gas";
//        case 5 :
//            return "Bill";
//        case 6 :
//            return "Vice";
//        case 7 :
//            return "Home";
//        default :
//            return "null";
//        }
//    }
//    else return "null";
//}


int chooseWallet() {
    std::string selection;

    std::cout << "Which wallet are you using?" << std::endl;
    printPrompt();

    while (getline(std::cin, selection)) {
        if (std::cin.fail()) {
            std::cin.clear();
            std::cout << "Incorrect input, please try again" << std::endl;
            printPrompt();
            continue;
        }
        std::transform(selection.begin(), selection.end(), selection.begin(), ::tolower);

        int walletEnum = convertStringToEnum(selection, Globals::CONVERT::WALLET);

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

    std::cout << "How would you like to label this transaction?" << std::endl;
    printPrompt();

    while (getline(std::cin, selection)) {
        if (std::cin.fail()) {
            std::cin.clear();
            std::cout << "Incorrect input, please try again" << std::endl;
            printPrompt();
            continue;
        }
        std::transform(selection.begin(), selection.end(), selection.begin(), ::tolower);

        int attributeEnum = convertStringToEnum(selection, Globals::CONVERT::ATTRIBUTE);

        if (attributeEnum == (-1)) {
            std::cout << "Text entered did not match the available attributes, please try again." << std::endl;
            printPrompt();
            continue;
        } else {
            return attributeEnum;
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

unsigned int chooseTimestamp() {
  std::string selection;

  std::cout << "Choose a date" << std::endl;
  getline(std::cin, selection);

  convertDateToTimestamp(selection);

  return createTimestamp();
}
