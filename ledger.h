#ifndef LEDGER_H
#define LEDGER_H
#include <string>
#include <vector>
#include "globals.h"


// Profile class
class Profile {
public:
    Profile();
    Profile(std::string profileName);
    ~Profile();

    /* void addTransaction
     * Adds a transaction to the vector
     */
    void addTransaction();

    /* void withdrawl
     */
    void withdrawl();


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
    //void saveToFile(struct Transaction transaction);
    void saveToFile();

    /* void reindexID
     * Reindexes ID #'s after a deletion
     */
    void reindexID();

    /* void loadFile
     * Loads the profile's data file during object construction
     */
    void loadFile();


    /* struct Transaction convertEntryToTransaction
     * Helper function that converts Entry string in loadFile() to a Transaction data structure for loading
     */
    struct Transaction convertEntryToTransaction(std::string entry);


    /* float getBalance
     * Returns wallet balance
     */
    float getBalance(int tenderType) {
        return this->_balance[tenderType];
    }


    /* void setBalance
     * Set wallet balance
     */
    float setBalance(float amount, int tenderType) {
        return this->_balance[tenderType] = amount;
    }


    /* std::string getProfileName
     */
    std::string getProfileName() {
        return this->_profileName;
    }

    // Stats section

    /* float getTotalsByAttribute
     * Returns totals of all transactions containing attribute
     */
    float getTotalsByAttribute(int attribute);

private:
    std::string _profileName;
    std::vector<Transaction> _transList;
    float _balance[NUM_OF_TENDER] = {0};
    std::string _fileName;
    bool _unsavedEdits = false;
};





#endif // LEDGER_H

