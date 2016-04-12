#include "globals.h"
#include "profile.h"

float Profile::getTotalsByAttribute(int attribute) {
    float total = 0;
    for (auto &i : this->_transList) {
        if (i.attribute == attribute) {
            total += i.amount;
        }
    }
    return total;
}
