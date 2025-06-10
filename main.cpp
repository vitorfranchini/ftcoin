

#include <stdexcept>
#include <mariadb/conncpp.hpp>
#include "ServerDBconnection.hpp"
#include "Wallet.hpp"
#include "WalletDao.hpp"
#include "Oracle.hpp"
#include "OracleDap.hpp"
#include <iostream>

int main(){
	WalletDao walletDao;
	Wallet * wallet = new Wallet(2,"Troca", "232");
	Wallet * teste =  walletDao.getWalletById(1);
	std::cout << "nome: " << teste->getHolderName() << std::endl;

	Oracle* oracle = new Oracle();
	std::cout << oracle->getExchange() << std::endl;
	OracleDao oracleDao;
	oracleDao.getOracle(oracle->getDate());

    return 0;
  
}
