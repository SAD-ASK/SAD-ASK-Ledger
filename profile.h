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

    bool queryCreateNewProfile( std::string profileName, std::string fileName );

    /* void addTransaction
     * Adds a transaction to the vector
     */
    void addTransaction();


    /* void printTransactionList
     * Does what you think it does
     * Uses calculated values from helper functions to determine necessary column sizes
     */
    void printTransactionList();


    /* void deleteTransaction
     * Deletes a transaction from the vector by matchind description
     */
    void deleteTransaction();


    /* void saveToFile(struct Transaction)
     * Saves new transaction to file
     */
    void saveToFile();


    /* void loadFile
     * Loads the profile's data file during object construction
     */
    void loadFile();


    /* struct Transaction convertEntryToTransaction
     * Helper function that converts Entry string in loadFile() to a Transaction data structure for loading
     */
    // NEEDS WORK
    struct Globals::Transaction convertEntryToTransaction( std::string entry );


    /* float getBalance
     * Returns wallet balance
     */
    float getBalance( int tenderType ) {
        return this->_balance[tenderType];
    }


    /* void setBalance
     * Set wallet balance
     */
    float setBalance( float amount, int tenderType ) {
        return this->_balance[tenderType] = amount;
    }


    /* std::string getProfileName
     */
    std::string getProfileName() {
        return this->_profileName;
    }

    void setProfileName( std::string newFilename ) {
        this->_fileName = newFilename;

    }

    // Stats section

    /* float getTotalsByAttribute
     * Returns totals of all transactions containing attribute
     */
    float getTotalsByAttribute( int attribute );


    /* void printStats
     * Experimental menu of common/useful stats
     */
    void printStats();

private:
    std::string _profileName;
    std::vector<Globals::Transaction> _transList;
    float _balance[Globals::WALLET_TYPE::NUM_OF_WALLETS] = {0};
    std::string _fileName;
    bool _unsavedEdits;
};





#endif // PROFILE_H

