#ifndef GLOBALS
#define GLOBALS
#include <string>
#include <array>

namespace Globals {

// Program Information
static std::string NAME("SAD-ASK-Ledger");
static std::string VERSION("0.1.0");

// Enums
enum CONVERT {
    WALLET = 1,
    ATTRIBUTE,
    TOTAL,
};

enum WALLET_TYPE {
    CASH,
    CHECKING,
    SAVINGS,
    CREDIT,
    NUM_OF_WALLETS
};
const static std::array<std::string,WALLET_TYPE::NUM_OF_WALLETS> walletList = {
    "Cash",
    "Checking",
    "Savings",
    "Credit"
};


enum TRANS_ATTRIBUTE {
    UNSET = -1,
    AUTO = 0,
    BILL,
    CHARITY,
    CLOTHES,
    COMPUTER,
    DINING,
    EDUCATION,
    ENTERTAINMENT,
    GIFT,
    GROCERIES,
    HOBBIES,
    HOME,
    LAUNDRY,
    MEDICAL,
    NOVELTY,
    PHONE,
    TRANSPORTATION,
    VICE,
    NUM_OF_ATTRS
};
const static std::array<std::string, TRANS_ATTRIBUTE::NUM_OF_ATTRS> attributeList = {
    "Auto",
    "Bill",
    "Charity",
    "Clothes",
    "Computer",
    "Dining",
    "Education",
    "Entertainment",
    "Gift",
    "Groceries",
    "Hobbies",
    "Home",
    "Laundry",
    "Medical",
    "Novelty",
    "Phone",
    "Transportation",
    "Vice"
};

// Transaction data type
struct Transaction {
    std::string description;
    float amount;
    int id;
    int attribute;
    int walletType;
    unsigned int transactionTimestamp;
    Transaction() :
        description("Default"),
        amount(0),
        id(-1),
        attribute(Globals::TRANS_ATTRIBUTE::UNSET),
        walletType(Globals::WALLET_TYPE::CASH),
        transactionTimestamp(0)
    {}
};
}; // End Namespace


#endif // GLOBALS

