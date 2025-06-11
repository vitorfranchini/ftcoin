#ifndef ORACLE_DAO_HPP
#define ORACLE_DAO_HPP

#include "ServerDBConnection.hpp"
#include "AbstractOracleDao.hpp"
#include "Oracle.hpp"

class OracleDao final : public AbstractOracleDao
{
public:
	OracleDao();
	virtual ~OracleDao();
	virtual void addOracle(Oracle * oracle);
	virtual void UpadteOracle(Oracle* oracle);
	virtual void deleteOracle(tm date);
	virtual Oracle* getOracleByDate(tm date);

private:
	ServerDBConnection db;

};



#endif // ORACLE_DAO_HPP
