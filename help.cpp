#include "globals.h"
#include "help.h"
#include "input.h"

#include <iostream>

void printHelpAttributes() {
    std::cout << "Here's the list of valid attributes implemented" << std::endl;
    for (unsigned int i = 0; i != Globals::attributeList.size(); i++) {
        std::cout << Globals::attributeList[i] << std::endl;
    }
    std::cout << std::endl;
}


void printHelpMenu() {
    char selection;
    while (true) {
        std::cout << "Help Menu: "             << std::endl
                  << "A: List of Attributes"   << std::endl
                  << "Q: Go back to Main Menu" << std::endl;
        printPrompt();
        while (std::cin >> selection) {
            if (std::cin.fail()) {
                std::cin.clear();
                std::cout << "Error, please try again" << std::endl;
                continue;
            }
            else break;
        }

        switch (selection) {
        case 'A' :
        case 'a' :
            printHelpAttributes();
            continue;

        case 'Q' :
        case 'q' :
            return;

        default:
            continue;
        }
    }
}
