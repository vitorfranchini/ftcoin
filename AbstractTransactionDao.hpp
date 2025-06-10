#ifndef ABSTRACT_TRANSACTION_DAO_HPP
#define ABSTRACT_TRANSACTION_DAO_HPP

class AbstractTrasactionDao
{
private:
    /* data */
public:
    AbstractTrasactionDao(/* args */);
    virtual ~AbstractTrasactionDao();
    
    void virtual addTrasaction() = 0;
    void virtual UpadteTrasaction() = 0;
    void virtual deleteTrasaction() = 0;

};

AbstractTrasactionDao::AbstractTrasactionDao(/* args */)
{
}

AbstractTrasactionDao::~AbstractTrasactionDao()
{
}

#endif