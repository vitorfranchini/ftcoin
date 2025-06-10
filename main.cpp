

#include <stdexcept>
#include <mariadb/conncpp.hpp>
#include "ServerDBconnection.hpp"
#include "Wallet.hpp"
#include "WalletDao.hpp"
#include <iostream>

int main(){
	WalletDao walletDao;
	Wallet * wallet = new Wallet(2,"Troca", "upadate");
	Wallet * teste =  walletDao.getWalletById(2);
	std::cout << "nome: " << teste->getHolderName() << std::endl;


    return 0;
  
}
