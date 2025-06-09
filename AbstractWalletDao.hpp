#ifndef ABSTRACT_WALLET_DAO
#define ABSTRACT_WALLET_DAO


class AbstractWalletDao
{
private:
    /* data */
public:
    AbstractWalletDao(/* args */);
    virtual ~AbstractWalletDao();
    
    void virtual addWallet() = 0;
    void virtual UpadteWallet() = 0;
    void virtual deleteWallet() = 0;

};

AbstractWalletDao::AbstractWalletDao(/* args */)
{
}

AbstractWalletDao::~AbstractWalletDao()
{
}

#endif