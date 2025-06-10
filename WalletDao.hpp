#ifndef WALLET_DAO_HPP  
#define WALLET_DAO_HPP  

#include "AbstractWalletDao.hpp"
#include "Wallet.hpp" // Corrigido o caminho relativo para incluir o arquivo Wallet.hpp  

class WalletDao final : public AbstractWalletDao
{
public:
	WalletDao();
	virtual ~WalletDao();

	virtual void addWallet(Wallet* wallet) override;
	virtual void UpadteWallet(Wallet* wallet) override;
	virtual void deleteWallet(int id) override;
	virtual Wallet* getWalletById(int id) override;

private:
	// Adicione membros privados, se necessário  
};

#endif // !WALLET_DAO_HPP
