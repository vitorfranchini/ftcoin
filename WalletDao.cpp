

#include <mariadb/conncpp.hpp>
#include "WalletDao.hpp"
#include "Wallet.hpp"
#include "ServerDBConnection.hpp"
#include <sstream>



WalletDao::WalletDao()
{

}

WalletDao::~WalletDao() 
{

}

void WalletDao::addWallet(Wallet* wallet) 
{
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
        std::cerr << "Erro no banco de dados " << e.what() << std::endl;
    }
}

void WalletDao::UpadteWallet(Wallet* wallet) 
{
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
        std::cerr << "Erro no banco de dados " << e.what() << std::endl;
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
        std::cerr << "Erro no banco de dados " << e.what() << std::endl;
    }
}
Wallet* WalletDao::getWalletById(int id) {
      
    try {
        std::shared_ptr<sql::Connection> conn = WalletDao::db.getConnection();

        if (!conn || !conn->isValid()) {
            std::cerr << "Erro: Conexão com o banco de dados não está válida." << std::endl;
            return nullptr;
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
        std::cerr << "Erro no banco de dados " << e.what() << std::endl;
    }

}