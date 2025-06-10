#ifndef ABSTRACT_ORACLE_DAO_HPP
#define ABSTRACT_ORACLE_DAO_HPP

#include "Oracle.hpp"


class AbstractOracleDao
{
private:
    /* data */
public:
    AbstractOracleDao();
    virtual ~AbstractOracleDao();
    
    virtual void addOracle(Oracle * oracle) = 0;
    virtual void UpadteOracle(Oracle * oracle) = 0;
    virtual void deleteOracle(tm date) = 0; // Substitui 'Date' por 'tm'
    virtual Oracle * getOracle(tm date) = 0;
};

#endif