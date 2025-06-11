#ifndef TRANSACTION_HPP
#define TRANSACTION_HPP

#include <iostream>
#include <string>
#include <ctime>
#include "date.hpp"

class Transaction {
private:
    int walletId;
    int movementId;
    tm date;
    char operationType; 
    double amountMoved;

public:
    Transaction();
    Transaction(int walletId, tm date, char operationType, double amountMoved);
    Transaction(int walletId, int movementId, tm date, char operationType, double amountMoved);

    int getWalletId() const;
    int getMovementId() const;
    tm getDate() const;
    char getOperationType() const;
    double getAmountMoved() const;

    void setWalletId(int walletId);
    void setMovementId(int movementId);
    void setDate(tm date);
    void setOperationType(char operationType);
    void setAmountMoved(double amountMoved);

    void print() const;
};

#endif