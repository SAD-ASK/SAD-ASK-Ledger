#include "core.h"
#include "input.h"
#include "help.h"

#include <iostream>
#include <limits>

Core::Core() {
    this->initialize();
    this->menuLoop();
}

Core::~Core() {
    std::cout << "Goodbye!" << std::endl;
}



void Core::initialize() {
    int fSuccess = system("mkdir profiles");
}


void Core::menuLoop() {

    // Choose account
    char selection;
    std::cout << "Welcome to " << Globals::NAME    << std::endl
              << "Version: "   << Globals::VERSION << std::endl;

    while (true) {
        std::cout << "Please make a selection"  << std::endl
                  << "A: Add a transaction"     << std::endl
                  << "D: Delete a transaction"  << std::endl
                  << "L: View transaction list" << std::endl
                  << "S: View stats screen"     << std::endl
                  << "B: Set account balances"  << std::endl
                  << "R: Debug regex"           << std::endl
                  << "H: View help"             << std::endl
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
            loadedProfile.deleteTransaction();
            break;

        case 'L' :
        case 'l' :
            loadedProfile.printTransactionList();
            continue;

        case 'S' :
        case 's' :
            loadedProfile.printStats();
            continue;


        case 'B' :
        case 'b' : {
            int chosenWallet = chooseWallet();
            int chosenAmount = chooseAmount();

            std::cout << "The chosen wallet balance" << " is now " << loadedProfile.setBalance(chosenAmount, chosenWallet);
            continue;
        }

        case 'R' :
        case 'r' : {
          int whocares = chooseTimestamp();
          break;
        }

        case 'H' :
        case 'h' :
            printHelpMenu();
            continue;

        case 'Q' :
        case 'q' :
            return;

        default:
            continue;
        }
    }
}
