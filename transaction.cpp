#include "transaction.hpp"
#include <iostream>
#include "wallet.hpp"

Transaction::Transaction()
    : walletId(0), movementId(0), date(), operationType('C'), amountMoved(0.0) {}

Transaction::Transaction(int walletId, int movementId, const Date& date, char operationType, double amountMoved)
    : walletId(walletId), movementId(movementId), date(date), operationType(operationType), amountMoved(amountMoved) {}

int Transaction::getWalletId() const {
    return walletId;
}

int Transaction::getMovementId() const {
    return movementId;
}

Date Transaction::getDate() const {
    return date;
}

char Transaction::getOperationType() const {
    return operationType;
}

double Transaction::getAmountMoved() const {
    return amountMoved;
}

void Transaction::setWalletId(int walletId) {
    this->walletId = walletId;
}

void Transaction::setMovementId(int movementId) {
    this->movementId = movementId;
}

void Transaction::setDate(const Date& date) {
    this->date = date;
}

void Transaction::setOperationType(char operationType) {
    if (operationType == 'C' || operationType == 'V') {
        this->operationType = operationType;
    } else {
        std::cerr << "Invalid operation.\n";
    }
}

void Transaction::setAmountMoved(double amountMoved) {
    if (amountMoved >= 0.0) {
        this->amountMoved = amountMoved;
    } else {
        std::cerr << "The quantity must not be a negative value.\n";
    }
}