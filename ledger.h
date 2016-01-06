#ifndef LEDGER_H
#define LEDGER_H
#include <string>
#include <vector>

// Program info
namespace PROGRAM {
const std::string NAME          ("SAD-ASK-Ledger");
const std::string VERSION       ("0.0.1");
}


/* Transaction data type
 * See TODO for ideas regarding more information to be implemented for each transaction
 */
struct Transaction {
    std::string description = "Transaction";
    float amount = 0;
};


// Profile class
class Profile {
public:
    Profile();

    /* void addTransaction
     * Adds a transaction to the vector
     */
    void addTransaction(std::string description, float amount);


    // void printTransactionList
    /* prints all the transactions currently stored
     * formatting is a necessity and filters will be added later? most likely in a separate function
     * FIX: Avoid initializing struct just to add values to vector
     */
    void printTransactionList();
private:
    std::string _profileName;
    std::vector<Transaction> _transList;
    float _balance;
};

/* Old global transaction list
 * std::vector<Transaction> transList;
 */


// std::string chooseProfile
/* Prompts user for Profile name and returns it
 * Very simple method of getting Profile name, does not handle file IO
 * Note: Profile name is used for filename and class object name!
 */
std::string chooseProfile();


// bool menuLoop
/* Starts the main loop after an account has been chosen
 * Accepts reference to active profile object
 */
bool menuLoop(Profile *currentProfile);

#endif // LEDGER_H

