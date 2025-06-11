#ifndef TRANSACTION_HPP
#define TRANSACTION_HPP

#include <iostream>
#include <string>
#include "date.hpp"

class Transaction {
private:
    int walletId;
    int movementId;
    Date date;
    char operationType; 
    double amountMoved;

public:
    Transaction();
    Transaction(int walletId, const Date& date, char operationType, double amountMoved);
    Transaction(int walletId, int movementId, const Date& date, char operationType, double amountMoved);

    int getWalletId() const;
    int getMovementId() const;
    Date getDate() const;
    char getOperationType() const;
    double getAmountMoved() const;

    void setWalletId(int walletId);
    void setMovementId(int movementId);
    void setDate(const Date& date);
    void setOperationType(char operationType);
    void setAmountMoved(double amountMoved);

    void print() const;
};

#endif