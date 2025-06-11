

#include <stdexcept>
#include <mariadb/conncpp.hpp>
#include "ServerDBconnection.hpp"
#include "Wallet.hpp"
#include "WalletDao.hpp"
#include "Oracle.hpp"
#include "OracleDap.hpp"
#include "Transaction.hpp"
#include "TransactionDao.hpp"
#include "Date.hpp"
#include <iostream>

int main(){
	/*WalletDao walletDao;
	Wallet * wallet = new Wallet(2,"Troca", "232");
	Wallet * teste =  walletDao.getWalletById(1);
	std::cout << "nome: " << teste->getHolderName() << std::endl;

	Oracle* oracle = new Oracle();
	std::cout << oracle->getExchange() << std::endl;
	OracleDao oracleDao;
	oracleDao.getOracle(oracle->getDate());

	*/
	TransactionDao transactionDao;
	Date date(10, 10, 2024);
	Transaction* transaction = new Transaction(1,date,'V',13);
	transactionDao.addTransaction(transaction);
	std::vector<Transaction*> transactions = transactionDao.getAllTransaction();

	for (Transaction* t : transactions) {
		std::cout << t->getAmountMoved() << std::endl;
	}




    return 0;
  
}
