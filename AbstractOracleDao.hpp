#ifndef ABSTRACT_ORACLE_DAO
#define ABSTRACT_ORACLE_DAO


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