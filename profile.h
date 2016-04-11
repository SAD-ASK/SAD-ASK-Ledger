#ifndef PROFILE_H
#define PROFILE_H

#include <string>
#include <vector>
#include "globals.h"


// Profile class
class Profile {
public:
    // Calls chooseProfile to load profile
    Profile();
    ~Profile();

    // Calls queryCreateNewProfile if necessary
    std::string chooseProfile();

    bool queryCreateNewProfile(std::string profileName, std::string fileName);

    /* void addTransaction
     * Adds a transaction to the vector
     */
    void addTransaction();

    // Unimplemented
    void withdrawl();


    void printTransactionList();


    /* void deleteTransaction
     * Deletes a transaction from the vector by matchind description
     */
    void deleteTransaction();


    /* void saveToFile(struct Transaction)
     * Saves new transaction to file
     */
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

    void setProfileName(std::string newFilename) {
      this->_fileName = newFilename;
      
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





#endif // PROFILE_H

