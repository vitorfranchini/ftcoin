
#include "TransactionDao.hpp"
#include "Transaction.hpp"
#include <mariadb/conncpp.hpp>
#include <vector>
#include "Date.hpp"
#include <iomanip>
#include <ctime>
#include <sstream> 


TransactionDao::TransactionDao() 
{

}

TransactionDao::~TransactionDao() 
{

}


void TransactionDao::addTransaction(Transaction* transaction)
{
	try {
		std::shared_ptr<sql::Connection> conn = TransactionDao::db.getConnection();
		
		if (!conn || !conn->isValid()) {
			std::cerr << "Erro: Conexão com o banco de dados não está valida." << std::endl;
			return;
		}

		int walletId = transaction->getWalletId();
		int movimentId = transaction->getMovementId();
		tm date = transaction->getDate();
		char operationType = transaction->getOperationType();
		double amountMoved = transaction->getAmountMoved();
		
		std::string sql = "INSERT INTO transaction (walletid,operationDate,operationType,amountMoved) VALUES (?,?,?,?)";
		std::unique_ptr <sql::PreparedStatement> pstmt(conn->prepareStatement(sql));

		pstmt->setInt(1, walletId);

		char buffer[90];
		std::strftime(buffer, sizeof(buffer), "%Y-%m-%d", &date);
		std::string dateSqlFormat(buffer);
		pstmt->setDateTime(2, dateSqlFormat);
		
		std::string operationTypeStr(1, operationType);
		pstmt->setString(3, operationTypeStr);
		pstmt->setFloat(4, amountMoved);

		int rownsAffected = pstmt->executeUpdate();
		std::cout << "Transaction inserida com sucesso! linhas afetadas:" << rownsAffected << std::endl;

	}
	catch (const sql::SQLException& e) {
		std::cerr << "Erro no banco de dados " << e.what() << std::endl;
	}
}


void TransactionDao::UpadteTransaction(Transaction* transaction) 
{
	try {
		std::shared_ptr<sql::Connection> conn = TransactionDao::db.getConnection();

		if (!conn || !conn->isValid()) {
			std::cerr << "Erro: Conexão com o banco de dados não está valida." << std::endl;
			return;
		}

		int walletId = transaction->getWalletId();
		int movimentId = transaction->getMovementId();
		tm date = transaction->getDate();
		char operationType = transaction->getOperationType();
		double amountMoved = transaction->getAmountMoved();

		std::string sql = "UPDATE transaction SET walletid = ?, operationDate = ?, operationType = ?, amountMoved = ? WHERE id = ?";
		std::unique_ptr<sql::PreparedStatement> pstmt(conn->prepareStatement(sql));

		pstmt->setInt(1,walletId);
		
		char buffer[90];
		std::strftime(buffer, sizeof(buffer), "%Y-%m-%d", &date);
		std::string dateSqlFormat(buffer);
		pstmt->setDateTime(2, dateSqlFormat);

		std::string operationTypeStr(1, operationType);
		pstmt->setString(3, operationTypeStr);

		pstmt->setFloat(4, amountMoved);
		pstmt->setInt(5, movimentId);

		int rowsAffected = pstmt->executeUpdate();
		std::cout << "Transacao atualizada com sucesso! Linhas afetadas: " << rowsAffected << std::endl;
	}
	catch (const sql::SQLException& e) {
		std::cerr << "Erro no banco de dados " << e.what() << std::endl;
	}
}


void TransactionDao::deleteTransaction(int id) 
{
	try {
		std::shared_ptr<sql::Connection> conn = TransactionDao::db.getConnection();
		
		if (!conn || !conn->isValid()) {
			std::cerr << "Erro: Conexão com o banco de dados não está valida." << std::endl;
			return;
		}
		
		std::string sql = "DELETE FROM transaction WHERE id=?";
		std::unique_ptr<sql::PreparedStatement> pstmt(conn->prepareStatement(sql));
		
		pstmt->setInt(1, id);

		int rowsAffected = pstmt->executeUpdate();
		std::cout << "Transacao deletada com sucesso! Linhas afetadas " << rowsAffected << std::endl;
	}
	catch (const sql::SQLException& e) {
		std::cerr << "Erro no banco de dados " << e.what() << std::endl;
	}
}

Transaction* TransactionDao::getTransactionById(int id) 
{
	try {
		std::shared_ptr<sql::Connection> conn = TransactionDao::db.getConnection();

		if (!conn || !conn->isValid()) {
			std::cerr << "Erro: Conexão com o banco de dados não está valida." << std::endl;
			return nullptr;
		}

		std::string sql = "SELECT * FROM transaction WHERE id = ?";
		std::unique_ptr<sql::PreparedStatement> pstmt(conn->prepareStatement(sql));
		
		pstmt->setInt(1, id);

		std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());

		if (res->next()) {
			int movimentId = res->getInt("id");
			int walletId = res->getInt("walletId");
			
			tm date;
			std::string dateStr = res->getString("operationDate").c_str();
			std::istringstream ss(dateStr);
			ss >> std::get_time(&date, "%Y-%m-%d"); // Parse the string into a tm structure  
			
			std::string operationTypeStr = res->getString("operationType").c_str();
            char operationType = operationTypeStr.empty() ? '\0' : operationTypeStr[0];
            
			double amountMoved = res->getFloat("amountMoved");

			Transaction* transaction = new Transaction( walletId, movimentId, date,operationType, amountMoved);
			
			return transaction;
		}
	}
	catch (const sql::SQLException& e) {
		std::cerr << "Erro no banco de dados " << e.what() << std::endl;
	}
}

std::vector<Transaction*> TransactionDao::getAllTransaction() 
{
	std::vector<Transaction*> transactions;
	try {

		std::shared_ptr<sql::Connection> conn = TransactionDao::db.getConnection();

		if (!conn || !conn->isValid()) {
			std::cerr << "Erro: Conexão com o banco de dados não está valida." << std::endl;
			return {};
		}

		std::string sql = "SELECT * FROM transaction";	
		std::unique_ptr<sql::PreparedStatement> pstmt(conn->prepareStatement(sql));
		std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());

		while (res->next()) {
			
			int movimentId = res->getInt("id");
			int walletId = res->getInt("walletId");

			tm date;
			std::string dateStr = res->getString("operationDate").c_str();
			std::istringstream ss(dateStr);
			ss >> std::get_time(&date, "%Y-%m-%d"); // Parse the string into a tm structure  

			std::string operationTypeStr = res->getString("operationType").c_str();
			char operationType = operationTypeStr.empty() ? '\0' : operationTypeStr[0];

			double amountMoved = res->getFloat("amountMoved");

			Transaction* transaction = new Transaction( walletId, movimentId, date,operationType, amountMoved);
			transactions.push_back(transaction);

		}
	}
	catch (const sql::SQLException& e) {
		std::cerr << "Erro no banco de dados " << e.what() << std::endl;
	}

	return transactions;
}