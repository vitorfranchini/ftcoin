#ifndef WALLET_DAO_HPP  
#define WALLET_DAO_HPP  

#include "ServerDBConnection.hpp"
#include "AbstractWalletDao.hpp"
#include "Wallet.hpp" // Corrigido o caminho relativo para incluir o arquivo Wallet.hpp  

class WalletDao final : public AbstractWalletDao
{
public:
	WalletDao();
	virtual ~WalletDao() override;

	virtual void addWallet(Wallet* wallet);
	virtual void UpadteWallet(Wallet* wallet);
	virtual void deleteWallet(int id);
	virtual Wallet* getWalletById(int id);

private:
	ServerDBConnection db; 
	
};

#endif // !WALLET_DAO_HPP
