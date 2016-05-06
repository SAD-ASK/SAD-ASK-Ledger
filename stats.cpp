#include "globals.h"
#include "profile.h"
#include "input.h"

#include <iostream>


float Profile::getTotalsByAttribute(int attribute) {
    float total = 0;
    for (auto &i : this->_transList) {
        if (i.attribute == attribute) {
            total += i.amount;
        }
    }
    return total;
}

void Profile::printStats() {
    std::cout << "User: AJ" << std::endl;
    for (auto i = 0; i != Globals::WALLET_TYPE::NUM_OF_WALLETS; i++) {
        //std::cout << convertEnumToString(i, Globals::CONVERT::WALLET)
        std::cout << Globals::walletList[i]
                  << " "
                  << this->getBalance(i)
                  << std::endl;
    }
}
