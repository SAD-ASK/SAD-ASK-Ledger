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
    int id;
};


///* bool deletionPredicate(const Transaction& trans, int idToDelete)
// * function to return predicate for deleteTransaction
// */
//bool deletionPredicate(const Transaction& trans, int idToDelete);



/* void initialize()
 * Initializes stuff. Only checks profile folder status atm
 */
void initialize();


// Profile class
class Profile {
public:
    Profile();
    Profile(std::string profileName);

    /* void addTransaction
     * Adds a transaction to the vector
     */
    void addTransaction(std::string description, float amount);


    /* void printTransactionList
     * prints all the transactions currently stored
     */
    void printTransactionList();



    /* void deleteTransaction
     * Deletes a transaction from the vector by matchind description
     * numInList: optional parameter for determining which occurance of description to delete
     */
    void deleteTransaction();


    /* void saveToFile(struct Transaction)
     * Saves new transaction to file
     */
    void saveToFile(struct Transaction transaction);


    /* void loadFile
     * Loads the profile's data file during object construction
     */
    void loadFile();


    /* struct Transaction convertEntryToTransaction
     * Helper function that converts Entry string in loadFile() to a Transaction data structure for loading
     */
    struct Transaction convertEntryToTransaction(std::string entry);



private:
    std::string _profileName;
    std::vector<Transaction> _transList;
    float _balance = 0;
    std::string _fileName;
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

