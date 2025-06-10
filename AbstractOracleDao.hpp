#ifndef ABSTRACT_ORACLE_DAO_HPP
#define ABSTRACT_ORACLE_DAO_HPP


class AbstractOracleDao
{
private:
    /* data */
public:
    AbstractOracleDao(/* args */);
    virtual ~AbstractOracleDao();
    
    void virtual addOracle();
    void virtual UpadteOracle();
    void virtual deleteOracle();

};

AbstractOracleDao::AbstractOracleDao(/* args */)
{
}

AbstractOracleDao::~AbstractOracleDao()
{
}

#endif