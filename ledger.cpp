#include <iostream>
#include <fstream>
#include <iomanip>
#include "ledger.h"
<<<<<<< HEAD
#include <string.h>
//void addTransaction(std::string description, float amount) {
//    Transaction t;
//    t.description = description;
//    t.amount = amount;
//    transList.push_back(t);
//}


=======

// Never to see the light of day...
>>>>>>> 25e0da81948c91dda0cec778b44eb908d184a1fa
Profile::Profile() :
  _profileName("Default"),
  _transList(),
  _balance(0)
{}


<<<<<<< HEAD


=======
>>>>>>> 25e0da81948c91dda0cec778b44eb908d184a1fa
void Profile::addTransaction(std::string description, float amount) {
  Transaction t;
  t.description = description;
  t.amount = amount;
  this->_transList.push_back(t);
  this->_balance += amount;
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


std::string chooseProfile() {
    std::string profileName;
    std::cout << "Welcome to " << PROGRAM::NAME    << std::endl
              << "Version: "   << PROGRAM::VERSION << std::endl;

    std::cout << "Please enter the profile name you wish to use" << std::endl
              << "(if entered profile name does not exist, you will be prompted to create it)" << std::endl
              << ": ";
    getline(std::cin, profileName);
    // Error checking

    return profileName;
}


bool menuLoop(Profile &currentProfile) {
  char selection;
  bool innerFlag = true;
  do{
    std::cout << "Please make a selection" << std::endl
<<<<<<< HEAD
	      << "A: Add a transaction" << std::endl
	      << "B: View transaction list" << std::endl
	      << "C: Quit the program" << std::endl;
=======
              << "A: Add a transaction" << std::endl
              << "L: View transaction list" << std::endl
              << "Q: Quit the program" << std::endl;
>>>>>>> 25e0da81948c91dda0cec778b44eb908d184a1fa
    std::cout << "Selection: ";
    std::cin >> selection;
    std::cin.ignore();
  }while(strlen(&selection)>1 && !innerFlag);

  switch (selection) {
  case 'A' :
  case 'a' : {
    std::string description;
    float amount;

    std::cout << "What do you want to call the transaction?" << std::endl << ": ";
    getline(std::cin, description);

    std::cout << "How much was this transaction for? (+ for gaining $, - for spending)" << std::endl << ": ";
    std::cin >> amount;

    currentProfile.addTransaction(description, amount);
    break;
  }

<<<<<<< HEAD
  case 'B' :
  case 'b' :
    currentProfile.printTransactionList();
    break;
  case 'C' :
  case 'c' :
=======
    case 'L' :
    case 'l' :
        currentProfile.printTransactionList();
        break;
    case 'Q' :
    case 'q' :
        return false;
>>>>>>> 25e0da81948c91dda0cec778b44eb908d184a1fa

    return false;

  default: innerFlag = false;
    return true ;
  }
  return true;
}



int main( ) {

  // Choose account
  std::string profileName = chooseProfile();
  Profile currentProfile;
  bool isDone = true;

  do {

    isDone = menuLoop(currentProfile);
    
  } while (isDone);

  return 0;
}
