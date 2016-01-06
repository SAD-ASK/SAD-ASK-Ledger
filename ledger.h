#ifndef LEDGER_H
#define LEDGER_H
#include <string>
#include <vector>

/* Transaction data type
 * As of now I believe it should be a POD as an "account" will be the class
 * that offers functions to operate on them
 * See TODO for ideas regarding more information to be implemented for each transaction
 */
struct Transaction {
    std::string description = "Transaction";
    float amount = 0;
};

// Global transaction list
// Support for multiple "accounts" wrapped in a class to be added later

std::vector<Transaction> transList;

// Transaction functions
/* void addTransaction
 * Adds a transaction to the vector
 * Will be extended as the transaction struct supports more info
 * Will possibly return transaction value for dynamic prompt later?
 */
void addTransaction(std::string description, float amount);

// void printTransactionList
/* prints all the transactions currently stored
 * formatting is a necessity and filters will be added later? most likely in a separate function
 * FIX: Avoid initializing struct just to add values to vector
 */
void printTransactionList();

// bool menuLoop
/* Starts the main program loop
 * Uses a loopcounter to display a welcome message on first iteration (replace with bool?)
 */
bool menuLoop(int loopCounter);

#endif // LEDGER_H

