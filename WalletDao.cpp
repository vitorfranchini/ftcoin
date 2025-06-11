

#include <mariadb/conncpp.hpp>
#include "WalletDao.hpp"
#include "Wallet.hpp"
#include "ServerDBConnection.hpp"
#include <sstream>

bool validateField(const std::string& fieldValue, const std::string& fieldName, int maxLength) {
    if (fieldValue.empty()) {
        std::cerr << "Erro de validação: O campo '" << fieldName << "' não pode ser vazio." << std::endl;
        return false;
    }
    if (fieldValue.length() > maxLength) {
        std::cerr << "Erro de validação: O campo '" << fieldName << "' excede o limite de " << maxLength << " caracteres." << std::endl;
        return false;
    }
    return true;
}

bool walletValidation( Wallet* wallet) {

    if (!wallet) {
        std::cerr << "Erro de validação: Objeto Wallet é nulo." << std::endl;
        return false;
    }


    if (!validateField(wallet->getHolderName(), "Nome do Titular", 90)) {
        return false;
    }

    if (!validateField(wallet->getBrokerageName(), "Nome da Corretora", 90)) {
        return false;
    }

    return true;
}

WalletDao::WalletDao() {

}

WalletDao::~WalletDao() {

}

void WalletDao::addWallet(Wallet* wallet) {
  
    if (!walletValidation(wallet)) {
        throw std::invalid_argument("Dados da carteira são inválidos.");
    }

    try {
        std::shared_ptr<sql::Connection> conn = WalletDao::db.getConnection(); 

        if (!conn || !conn->isValid()) {
            std::cerr << "Erro: Conexão com o banco de dados não está válida." << std::endl;
            return;
        }

        std::string holderName = wallet->getHolderName();
        std::string brokerageName = wallet->getBrokerageName();

        std::string sql = "INSERT INTO wallet (name, brokerage) VALUES (?, ?)";
        std::unique_ptr<sql::PreparedStatement> pstmt(conn->prepareStatement(sql));

        pstmt->setString(1, holderName);    
        pstmt->setString(2, brokerageName);

        int rowsAffected = pstmt->executeUpdate();
        std::cout << "Carteira inserida com sucesso! Linhas afetadas: " << rowsAffected << std::endl;
    }
    catch (const sql::SQLException& e) {
        throw std::runtime_error("Erro no banco de dados ao inserir carteira: " + std::string(e.what()));
    }
}

void WalletDao::UpadteWallet(Wallet* wallet) {

    if (!walletValidation(wallet)) {
        throw std::invalid_argument("Dados da carteira são inválidos.");
    }
   
    try {
        std::shared_ptr<sql::Connection> conn = WalletDao::db.getConnection();

        if (!conn || !conn->isValid()) {
            std::cerr << "Erro: Conexão com o banco de dados não está válida." << std::endl;
            return;
        }

        std::string holderName = wallet->getHolderName();
        std::string brokerageName = wallet->getBrokerageName();

        std::string sql = "UPDATE wallet SET name = ?, brokerage = ? WHERE id = ?";
        std::unique_ptr<sql::PreparedStatement> pstmt(conn->prepareStatement(sql));

        pstmt->setString(1, holderName); 
        pstmt->setString(2, brokerageName); 
        pstmt->setInt(3, wallet->getId());  

        int rowsAffected = pstmt->executeUpdate(); // Retorna o número de linhas atualizadas
        std::cout << "Carteira atualizada com sucesso! Linhas afetadas: " << rowsAffected << std::endl;
    }
    catch (const sql::SQLException& e) {
        throw std::runtime_error("Erro no banco de dados ao inserir carteira: " + std::string(e.what()));
    }
}
void WalletDao::deleteWallet(int id) {
   
    try {
        std::shared_ptr<sql::Connection> conn = WalletDao::db.getConnection();
       
        if (!conn || !conn->isValid()) {
            std::cerr << "Erro: Conexão com o banco de dados não está válida." << std::endl;
            return;
        }
        
        std::string sql = "DELETE FROM wallet WHERE id = ?";
        std::unique_ptr<sql::PreparedStatement> pstmt(conn->prepareStatement(sql));
        
        pstmt->setInt(1, id); 

        int rowsAffected = pstmt->executeUpdate();
        std::cout << "Carteira deletada com sucesso! Linhas afetadas: " << rowsAffected << std::endl;
    }
    catch (const sql::SQLException& e) {
        throw std::runtime_error("Erro no banco de dados ao inserir carteira: " + std::string(e.what()));
    }
}
Wallet* WalletDao::getWalletById(int id) {
      
    try {
        std::shared_ptr<sql::Connection> conn = WalletDao::db.getConnection();

        if (!conn || !conn->isValid()) {
            std::cerr << "Erro: Conexão com o banco de dados não está válida." << std::endl;
            return;
        }

        std::string sql = "SELECT * FROM wallet WHERE id = ?";
        std::unique_ptr<sql::PreparedStatement> pstmt(conn->prepareStatement(sql));
        
        pstmt->setInt(1, id);
        
        std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());
    
        if (res->next()) {

            int wallet_id = res->getInt("id");
            std::string corretora = res->getString("brokerage").c_str();   
            std::string nome = res->getString("name").c_str();

            Wallet* wallet = new Wallet(wallet_id, nome, corretora);
            return wallet;
        }
        else {
            std::cerr << "Nenhuma carteira encontrada com ID " << id << std::endl;
            return nullptr;
        }
    }
    catch (const sql::SQLException& e) {
        throw std::runtime_error("Erro no banco de dados ao inserir carteira: " + std::string(e.what()));
    }

}