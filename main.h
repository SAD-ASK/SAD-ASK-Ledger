#ifndef MAIN_H
#define MAIN_H
#include <string>

/* Header used for general functions and datatypes not belonging to a class
 * For the moment will serve as a globals header as options/globals are at a minumum
 */




/* Transaction data type
 */
struct Transaction {
    std::string description = "Transaction";
    float amount = 0;
    int id;
    int attribute;
    int tenderType;
    unsigned int transactionTimestamp;
};


/* void initialize()
 * Initializes stuff. Only checks profile folder status atm
 */
void initialize();


/* std::string chooseProfile
 * Prompts user for Profile name and returns it
 */
std::string chooseProfile();


/* bool menuLoop
 * Accepts reference to active profile object
 * Returns false when user has opted to quit
 */
bool menuLoop();


/* bool queryCreateNewProfile(std::string)
 * Handles creating new profile if selected one doesn't exist
 * Returns true if new profile created, false if not
 */
bool queryCreateNewProfile(std::string profileName, std::string fileName);



/* void printPrompt
 * Prints a consistent prompt before user input
 * Overloaded version uses profile name
 */
//void printPrompt();
void printPrompt();



/* int convertStringToEnum
     * Helper function that converts string to appropriate enum structure
     */
int convertStringToEnum(std::string attribute, int conversionType);


/* std::string convertEnumToString
     * Helper function that returns enum label as a string
     */
std::string convertEnumToString(int enumToConvert, int conversionType);

/* int chooseWallet
 * Prompts user for "wallet" during transaction entry
 */
int chooseWallet();

/* int chooseAttribute
 * Prompts user for attribute during transaction entry
 */
int chooseAttribute();

/* bool isFloat
 * Predicate function for determining if a string entered is a valid float
 */
bool isFloat(int character);

/* float chooseAmount
 * Prompts user for amount during transaction entry
 */
float chooseAmount();

/* std::string chooseDescription
 * Prompts user for description during transaction entry
 */
std::string chooseDescription();

/* int chooseID
 * Prompts user for id during transaction deletion
 */
int chooseID();



#endif // MAIN_H

