#ifndef TRANSACTION_DAO_HPP
#define TRANSACTION_DAO_HPP


#include "AbstractTransactionDao.hpp"
#include "ServerDBConnection.hpp"
 


class TransactionDao final : public AbstractTransactionDao
{
public:
	TransactionDao();
	virtual ~TransactionDao();
	virtual void addTransaction(Transaction* transaction);
	virtual void UpadteTransaction(Transaction* transaction);
	virtual void deleteTransaction(int id);
	virtual Transaction* getTransactionById(int id);
	virtual std::vector<Transaction*> getAllTransaction();

private:
	ServerDBConnection db;
};






#endif