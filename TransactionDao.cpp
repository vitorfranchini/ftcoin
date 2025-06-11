
#include "TransactionDao.hpp"
#include "Transaction.hpp"
#include <mariadb/conncpp.hpp>
#include <vector>
#include "Date.hpp"
#include <iomanip>
#include <sstream> 


TransactionDao::TransactionDao() 
{

}

TransactionDao::~TransactionDao() 
{

}


void TransactionDao::addTransaction(Transaction* transaction)
{
	int walletId = transaction->getWalletId();
	int movimentId = transaction->getMovementId();
	Date date = transaction->getDate();
	char operationType = transaction->getOperationType();
	double amountMoved = transaction->getAmountMoved();

	try {
		std::shared_ptr<sql::Connection> conn = TransactionDao::db.getConnection();
		
		if (!conn || !conn->isValid()) {
			std::cerr << "Erro: Conexão com o banco de dados não está valida." << std::endl;
		}
		
		std::string sql = "INSERT INTO transaction (walletid,dataOperacao,tipoOperacao,qtdMovimentado) VALUES (?,?,?,?)";

		std::unique_ptr <sql::PreparedStatement> pstmt(conn->prepareStatement(sql));
		pstmt->setInt(1, walletId);

		std::ostringstream oss;
		oss << std::setw(4) << std::setfill('0') << date.getYear() << "-"
			<< std::setw(2) << std::setfill('0') << date.getMonth() << "-"
			<< std::setw(2) << std::setfill('0') << date.getDay();

		std::string sql_format_date = oss.str();
		pstmt->setDateTime(2, sql_format_date);

		std::string operationTypeStr(1, operationType);
		pstmt->setString(3, operationTypeStr);
		pstmt->setFloat(4, amountMoved);

		int rownsAffected = pstmt->executeUpdate();
		std::cout << "Transaction inserida com sucesso! linhas afetadas:" << rownsAffected << std::endl;

	}
	catch (sql::SQLException& e) {
		std::cerr << "Erro SQL ao inserir transaction" << e.what() << std::endl;
	}
	catch (std::exception& e) {
		std::cerr << "Erro geral ao inserir transaction" << e.what() << std::endl;
	}



}


void TransactionDao::UpadteTransaction(Transaction* transaction) {
	int walletId = transaction->getWalletId();
	int movimentId = transaction->getMovementId();
	Date date = transaction->getDate();
	char operationType = transaction->getOperationType();
	double amountMoved = transaction->getAmountMoved();

	try {
		std::shared_ptr<sql::Connection> conn = TransactionDao::db.getConnection();

		if (!conn || !conn->isValid()) {
			std::cerr << "Erro ao tentar conecar ao banco";
		}

		std::string sql = "UPDATE transaction SET walletid = ?, dataOperacao = ?, tipoOperacao = ?, qtdMovimentado = ? WHERE id = ?";
		std::unique_ptr<sql::PreparedStatement> pstmt(conn->prepareStatement(sql));

		pstmt->setInt(1,walletId);
		std::ostringstream oss;
		oss << std::setw(4) << std::setfill('0') << date.getYear() << "-"
			<< std::setw(2) << std::setfill('0') << date.getMonth() << "-"
			<< std::setw(2) << std::setfill('0') << date.getDay();

		std::string sql_format_date = oss.str();
		pstmt->setDateTime(2,sql_format_date);

		std::string operationTypeStr(1, operationType);
		pstmt->setString(3, operationTypeStr);

		pstmt->setFloat(4, amountMoved);
		pstmt->setInt(5, movimentId);

		int rowsAffected = pstmt->executeUpdate();
		std::cout << "Transacao atualizada com sucesso! Linhas afetadas: " << rowsAffected << std::endl;
	}catch (std::exception& e) {

		std::cerr << "Erro ao ao tentar atualizar transaction : " << e.what() << std::endl;
	}
}


void TransactionDao::deleteTransaction(int id) {

	try {
		std::shared_ptr<sql::Connection> conn = TransactionDao::db.getConnection();

		std::string sql = "DELETE FROM transaction WHERE id=?";

		std::unique_ptr<sql::PreparedStatement> pstmt(conn->prepareStatement(sql));
		pstmt->setInt(1, id);

		int rowsAffected = pstmt->executeUpdate();
		std::cout << "Transacao deletada com sucesso! Linhas afetadas " << rowsAffected << std::endl;
	}
	catch (std::exception& e) {
		std::cerr << "Erro ao tentar deletar transaction: " << e.what() << std::endl;

	}

}

Transaction* TransactionDao::getTransactionById(int id) {
	try {
		std::shared_ptr<sql::Connection> conn = TransactionDao::db.getConnection();

		if (!conn || !conn->isValid()) {
			std::cerr << "Erro: Conexao com o banco nao esta valida";
		}
		std::string sql = "SELECT * FROM transaction WHERE id = ?";
		std::unique_ptr<sql::PreparedStatement> pstmt(conn->prepareStatement(sql));
		pstmt->setInt(1, id);

		std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());

		
		if (res->next()) {
			int movimentId = res->getInt("id");
			int walletId = res->getInt("walletId");
			std::string dateStr = res->getString("dataOperacao").c_str();
			
			int ano, mes, dia; char sep1, sep2;
			std::istringstream iss(dateStr);
			iss >> ano >> sep1 >> mes >> sep2 >> dia;
			Date date(dia,mes,ano);
			
			std::string operationTypeStr = res->getString("tipoOperacao").c_str();
            char operationType = operationTypeStr.empty() ? '\0' : operationTypeStr[0];
            
			double amountMoved = res->getFloat("qtdMovimentado");

			Transaction* transaction = new Transaction( walletId, movimentId, date,operationType, amountMoved);
			
			return transaction;
		}
	}
	catch (std::exception& e) {
		std::cerr << "Erro ao tentar buscar transacao: " << e.what() << std::endl;
	}
	
}

std::vector<Transaction*> TransactionDao::getAllTransaction() {
	std::vector<Transaction*> transactions;
	try {
		std::shared_ptr<sql::Connection> conn = TransactionDao::db.getConnection();
		std::string sql = "SELECT * FROM transaction";
		std::unique_ptr<sql::PreparedStatement> pstmt(conn->prepareStatement(sql));
		
		std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());

		while (res->next()) {
			int movimentId = res->getInt("id");
			int walletId = res->getInt("walletId");
			std::string dateStr = res->getString("dataOperacao").c_str();

			int ano, mes, dia; char sep1, sep2;
			std::istringstream iss(dateStr);
			iss >> ano >> sep1 >> mes >> sep2 >> dia;
			Date date(dia, mes, ano);

			std::string operationTypeStr = res->getString("tipoOperacao").c_str();
			char operationType = operationTypeStr.empty() ? '\0' : operationTypeStr[0];

			double amountMoved = res->getFloat("qtdMovimentado");

			Transaction* transaction = new Transaction(walletId, movimentId, date, operationType, amountMoved);
			transactions.push_back(transaction);
		}
	}
	catch (std::exception& e) {
		std::cerr << "Erro ao tentar busca todos as trasacos" << e.what() << std::endl;

	}

	return transactions;
}