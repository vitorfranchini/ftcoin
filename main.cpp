

#include <stdexcept>
#include <mariadb/conncpp.hpp>
#include <ctime>
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
	/*
	WalletDao walletDao;
	Wallet * wallet = new Wallet(1,"Troca", "231");
	walletDao.addWallet(wallet);
	 Wallet * wallet2 = walletDao.getWalletById(2);

	std::cout << "nome: " << wallet2->getHolderName() << std::endl;
	
	
	Oracle* oracle = new Oracle();
	std::cout << oracle->getExchange() << std::endl;
	OracleDao oracleDao;
	oracleDao.getOracle(oracle->getDate());
	*/
	
	TransactionDao transactionDao;
	tm date = {};
	date.tm_year = 2024 - 1900; // Ano desde 1900 (2024 - 1900 = 124)
	date.tm_mon = 5 - 1;        // Mês (0 = janeiro, então maio = 4)
	date.tm_mday = 10;          // Dia do mês
	
	Transaction* transaction = new Transaction(2,2,date,'V',13);
	transactionDao.addTransaction(transaction);
	Transaction* transaction2 = transactionDao.getTransactionById(3);
	std::cout << transaction2->getAmountMoved();


	
	std::vector<Transaction*> transactions = transactionDao.getAllTransaction();

	for (Transaction* t : transactions) {
		std::cout << t->getOperationType() << std::endl;
	}
	



    return 0;
  
}
