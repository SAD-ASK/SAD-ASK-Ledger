#ifndef LEDGER_H
#define LEDGER_H
#include <string>
#include <vector>
#include "main.h"



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

    /* int convertStringToEnum
     * Helper function that converts string to appropriate enum structure
     */
    int convertStringToEnum(std::string attribute, int conversionType);


    /* std::string convertEnumToString
     * Helper function that returns enum label as a string
     */
    std::string convertEnumToString(int enumToConvert, int conversionType);


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

private:
    std::string _profileName;
    std::vector<Transaction> _transList;
    float _balance[NUM_OF_TENDER] = {0};
    std::string _fileName;
    bool _unsavedEdits = false;
};





#endif // LEDGER_H

