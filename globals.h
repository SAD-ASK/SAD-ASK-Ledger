#ifndef GLOBALS
#define GLOBALS

// Program info
namespace PROGRAM {
const std::string NAME          ("SAD-ASK-Ledger");
const std::string VERSION       ("0.0.4");
}


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
#endif // GLOBALS

