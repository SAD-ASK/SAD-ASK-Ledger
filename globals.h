#ifndef GLOBALS
#define GLOBALS
#include <string>

namespace Globals {

// Program Information
static std::string NAME("SAD-ASK-Ledger");
static std::string VERSION("0.1.0");

// Enums
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

// Transaction data type
struct Transaction {
    std::string description = "Transaction";
    float amount = 0;
    int id;
    int attribute;
    int tenderType;
    unsigned int transactionTimestamp;
};
}; // End Namespace


#endif // GLOBALS

