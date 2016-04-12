#include "core.h"
#include "main.h"

#include <iostream>
#include <limits>

Core::Core() {
    this->initialize();
    this->menuLoop();
}

Core::~Core() {}


void Core::initialize() {
    // God I wish std::filesystem was standard...easiest solution for now
    int fSuccess = system("mkdir profiles");
}


void Core::menuLoop() {

    // Choose account
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
            loadedProfile.addTransaction();
            break;

        case 'D' :
        case 'd' :
            loadedProfile.addTransaction();
            break;

        case 'B' :
        case 'b' : {
            // This options is only present for testing
            std::cout << selection << ": " << loadedProfile.getBalance(chooseWallet()) << std::endl;
            continue;
        }

        case 'L' :
        case 'l' :
            loadedProfile.printTransactionList();
            continue;

        case 'S' :
        case 's' : {
            int chosenWallet = chooseWallet();
            int chosenAmount = chooseAmount();

            std::cout << "The chosen wallet balance" << " is now " << loadedProfile.setBalance(chosenAmount, chosenWallet);
            continue;
        }

        case 'Q' :
        case 'q' :
            break;

        default:
            continue;
        }
    }
}
