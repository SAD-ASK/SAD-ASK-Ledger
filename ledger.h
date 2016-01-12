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
 */
struct Transaction {
    std::string description = "Transaction";
    float amount = 0;
};


/* void initialize()
 * Initializes stuff. Only checks profile folder status atm
 */
void initialize();


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
     */
    void printTransactionList();
private:
    std::string _profileName;
    std::vector<Transaction> _transList;
    float _balance = 0;
};


/* std::string chooseProfile
 * Prompts user for Profile name and returns it
 */
std::string chooseProfile();


/* bool menuLoop
 * Accepts reference to active profile object
 * Returns false when user has opted to quit
 */
bool menuLoop(Profile *currentProfile);


/* bool queryCreateNewProfile(std::string)
 * Handles creating new profile if selected one doesn't exist
 * Returns true if new profile created, false if not
 */
bool queryCreateNewProfile(std::string profileName, std::string fileName);

#endif // LEDGER_H

