#ifndef ABSTRACT_WALLET_DAO_HPP
#define ABSTRACT_WALLET_DAO_HPP

#include "Wallet.hpp"

class AbstractWalletDao
{
private:
    /* data */
public:
    AbstractWalletDao(/* args */);
    virtual ~AbstractWalletDao();
    
    virtual void addWallet(Wallet * wallet) = 0;
    virtual void UpadteWallet(Wallet * wallet) = 0;
    virtual void deleteWallet(int id) = 0;
	virtual Wallet * getWalletById(int id) = 0;

};

#endif