

#include <mariadb/conncpp.hpp>
#include "WalletDao.hpp"
#include "Wallet.hpp"
#include "ServerDBConnection.hpp"
#include <sstream>


bool walletValidation(Wallet * wallet) {
    if (!wallet) {
        std::cerr << "Erro de validação: Objeto Wallet é nulo." << std::endl;
        return false; // Sai da função se o objeto for nulo
    }

    std::string holderName = wallet->getHolderName();
    std::string brokerageName = wallet->getBrokerageName();

    if (holderName.empty()) {
        std::cerr << "Erro de validação: O nome do titular (holderName) não pode ser vazio." << std::endl;
        return false;
    }

    if (brokerageName.empty()) {
        std::cerr << "Erro de validação: O nome da corretora (brokerageName) não pode ser vazio." << std::endl;
        return false;
    }

    if (holderName.length() > 90) {
        std::cerr << "Erro de validação: O nome do titular (holderName) excede o limite de 90 caracteres." << std::endl;
        return false;
    }

    if (brokerageName.length() > 90) {
        std::cerr << "Erro de validação: O nome da corretora (brokerageName) excede o limite de 90 caracteres." << std::endl;
        return false;
    }
}


WalletDao::WalletDao() {

}

WalletDao::~WalletDao() {

}

ServerDBConnection db; // Cria uma instância da conexão com o banco de dados


void WalletDao::addWallet(Wallet* wallet) {
  
    if(!walletValidation(wallet)) {
        return; 
	}

    std::string holderName = wallet->getHolderName();
    std::string brokerageName = wallet->getBrokerageName();

    try {
        std::shared_ptr<sql::Connection> conn = db.getConnection(); // Obtém a conexão

        // Verifica se a conexão é válida
        if (!conn || !conn->isValid()) {
            std::cerr << "Erro: Conexão com o banco de dados não está válida ao tentar adicionar carteira." << std::endl;
            return;
        }

        std::string sql = "INSERT INTO wallet (nome, corretora) VALUES (?, ?)";

        // Criar o PreparedStatement a partir da conexão
        std::unique_ptr<sql::PreparedStatement> pstmt(conn->prepareStatement(sql));
        pstmt->setString(1, holderName);    // Primeiro '?' recebe o nome do titular validado
        pstmt->setString(2, brokerageName); // Segundo '?' recebe o nome da corretora validado

        // Executar o INSERT
        int rowsAffected = pstmt->executeUpdate(); // Retorna o número de linhas inseridas
        std::cout << "Carteira inserida com sucesso! Linhas afetadas: " << rowsAffected << std::endl;
    }
    catch (const sql::SQLException& e) {
        std::cerr << "Erro SQL ao inserir carteira: " << e.what() << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Erro geral ao inserir carteira: " << e.what() << std::endl;
    }
}

void WalletDao::UpadteWallet(Wallet* wallet) {

    if(!walletValidation(wallet)) {
        return; 
    }
    std::string holderName = wallet->getHolderName();
    std::string brokerageName = wallet->getBrokerageName();
    try {
        std::shared_ptr<sql::Connection> conn = db.getConnection(); // Obtém a conexão
        // Verifica se a conexão é válida
        if (!conn || !conn->isValid()) {
            std::cerr << "Erro: Conexão com o banco de dados não está válida ao tentar atualizar carteira." << std::endl;
            return;
        }
        std::string sql = "UPDATE wallet SET nome = ?, corretora = ? WHERE id = ?";
        // Criar o PreparedStatement a partir da conexão
        std::unique_ptr<sql::PreparedStatement> pstmt(conn->prepareStatement(sql));
        pstmt->setString(1, holderName);    // Primeiro '?' recebe o nome do titular validado
        pstmt->setString(2, brokerageName); // Segundo '?' recebe o nome da corretora validado
        pstmt->setInt(3, wallet->getId());  // Terceiro '?' recebe o ID da carteira
        // Executar o UPDATE
        int rowsAffected = pstmt->executeUpdate(); // Retorna o número de linhas atualizadas
        std::cout << "Carteira atualizada com sucesso! Linhas afetadas: " << rowsAffected << std::endl;
    }
    catch (const sql::SQLException& e) {
        std::cerr << "Erro SQL ao atualizar carteira: " << e.what() << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Erro geral ao atualizar carteira: " << e.what() << std::endl;
	}
}
void WalletDao::deleteWallet(int id) {
   
    try {
        std::shared_ptr<sql::Connection> conn = db.getConnection(); // Obtém a conexão
        // Verifica se a conexão é válida
        if (!conn || !conn->isValid()) {
            std::cerr << "Erro: Conexão com o banco de dados não está válida ao tentar deletar carteira." << std::endl;
            return;
        }
        std::string sql = "DELETE FROM wallet WHERE id = ?";
        // Criar o PreparedStatement a partir da conexão
        std::unique_ptr<sql::PreparedStatement> pstmt(conn->prepareStatement(sql));
        pstmt->setInt(1, id); // Define o ID da carteira a ser deletada
        // Executar o DELETE
        int rowsAffected = pstmt->executeUpdate(); // Retorna o número de linhas deletadas
        std::cout << "Carteira deletada com sucesso! Linhas afetadas: " << rowsAffected << std::endl;
    }
    catch (const sql::SQLException& e) {
        std::cerr << "Erro SQL ao deletar carteira: " << e.what() << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Erro geral ao deletar carteira: " << e.what() << std::endl;
	}
}
Wallet* WalletDao::getWalletById(int id) {
      
    try {
        std::shared_ptr<sql::Connection> conn = db.getConnection();

        if (!conn || !conn->isValid()) {
            std::cerr << "Erro: Conexao com o banco de dados não está válida." << std::endl;
        }
        std::string sql = "SELECT * FROM wallet WHERE id = ?";
        std::unique_ptr<sql::PreparedStatement> pstmt(conn->prepareStatement(sql));
        pstmt->setInt(1, id);
        
        std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());
    
        if (res->next()) {
            int wallet_id = res->getInt("id");
            std::string corretora = res->getString("corretora").c_str();
           
            std::string nome = res->getString("nome").c_str();
        

            Wallet* wallet = new Wallet(wallet_id, nome, corretora);
            return wallet;
        }
        else {
            std::cerr << "Nenhuma carteira encontrada com ID " << id << std::endl;
            return nullptr;
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Erro inesperado: " << e.what() << std::endl;
    }

}