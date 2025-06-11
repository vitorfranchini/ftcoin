#ifndef ABSTRACT_TRANSACTION_DAO_HPP
#define ABSTRACT_TRANSACTION_DAO_HPP

#include "Transaction.hpp"
#include <vector>

class AbstractTransactionDao
{
private:
    /* data */
public:
    AbstractTransactionDao();
    virtual ~AbstractTransactionDao();
    
    virtual void addTransaction(Transaction * transaction) = 0;
    virtual void UpadteTransaction(Transaction * transaction) = 0;
    virtual void deleteTransaction(int id) = 0;
    virtual Transaction* getTransactionById(int id) = 0;
    virtual std::vector<Transaction*> getAllTransaction() = 0;

};

#endif