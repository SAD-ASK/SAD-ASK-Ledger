#ifndef INPUT_H
#define INPUT_H

#include "globals.h"

#include <string>

/* This header is all input checkers
 * While it implements error checking, it does segregate the majority of input to it's own file
 */


// Enum Helpers

/* int convertStringToEnum
 * Helper function that converts string to appropriate enum structure
 */
int convertStringToEnum( std::string attribute, int conversionType );

/* std::string convertEnumToString
 * Helper function that returns enum label as a string
 */
std::string convertEnumToString( int enumToConvert, int conversionType );


// Input handlers/checkers

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
bool isFloat( int character );

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

/* chooseTimestamp
 * Prompts user to choose timestamp
 */
unsigned int chooseTimestamp();


// Prints prior to input, calls current time
void printPrompt();

#endif // INPUT_H
