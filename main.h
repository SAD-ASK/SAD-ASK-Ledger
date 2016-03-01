#ifndef MAIN_H
#define MAIN_H


/* Header used for general functions and datatypes not belonging to a class
 * For the moment will serve as a globals header as options/globals are at a minumum
 */

// Program info
namespace PROGRAM {
const std::string NAME          ("SAD-ASK-Ledger");
const std::string VERSION       ("0.0.4");
}


enum TENDER_TYPE {
    CASH,
    CREDIT,
    DEBIT,
    NUM_OF_TENDER
};


enum TRANS_ATTRIBUTE {
    NOVELTY,
    FOOD,
    RESTAURANT,
    CLOTHING,
    GAS,
    BILL,
    VICE,
    HOME,
    NUM_OF_ATTRS
};


/* Transaction data type
 */
struct Transaction {
    std::string description = "Transaction";
    float amount = 0;
    int id;
    int attribute;
    int tenderType;
    unsigned int creationTimestamp;
    unsigned int lastModifiedTimestamp;
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


#endif // MAIN_H

