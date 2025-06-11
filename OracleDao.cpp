
#include "OracleDap.hpp"
#include "Oracle.hpp"
#include <iomanip> 
#include <sstream> 

OracleDao::OracleDao() 
{

}

OracleDao::~OracleDao() 
{

}

void OracleDao::addOracle(Oracle * oracle) 
{
    try {
        std::shared_ptr<sql::Connection> conn = OracleDao::db.getConnection(); // Obtém a conexão

        // Verifica se a conexão é válida
        if (!conn || !conn->isValid()) {
            std::cerr << "Erro: Conexão com o banco de dados não está válida ao tentar adicionar carteira." << std::endl;
            return;
        }

        tm date = oracle->getDate();
        double exchange = oracle->getExchange();

        char buffer[80];
        std::strftime(buffer, sizeof(buffer), "%Y-%m-%d", &date);
        std::string dateSqlFormat(buffer); 

        std::string sql = "INSERT INTO oraculo (date, exchange) VALUES (?, ?)";
        std::unique_ptr<sql::PreparedStatement> pstmt(conn->prepareStatement(sql));

        pstmt->setDateTime(1, dateSqlFormat);
        pstmt->setFloat(2, exchange); 

        int rowsAffected = pstmt->executeUpdate(); 
        std::cout << "Carteira inserida com sucesso! Linhas afetadas: " << rowsAffected << std::endl;
    }
    catch (const sql::SQLException& e) {
        std::cerr << "Erro no banco de dados " << e.what() << std::endl;
    }
}

void OracleDao::UpadteOracle(Oracle* oracle) 
{
    tm date = oracle->getDate();
    double exchange = oracle->getExchange();

    try {
        std::shared_ptr<sql::Connection> conn = OracleDao::db.getConnection(); 


        if (!conn || !conn->isValid()) {
            std::cerr << "Erro: Conexão com o banco de dados não está válida ao tentar adicionar carteira." << std::endl;
            return;
        }
        char buffer[80]; 
       
        std::strftime(buffer, sizeof(buffer), "%Y-%m-%d", &date);
        std::string date_sql_format(buffer); 


        std::string sql = "UPDATE oraculo SET cotacao = ? WHERE data = ?";

     
        std::unique_ptr<sql::PreparedStatement> pstmt(conn->prepareStatement(sql));
        pstmt->setFloat(1, exchange);
        pstmt->setDateTime(2, date_sql_format);



    
        int rowsAffected = pstmt->executeUpdate(); 
        std::cout << "Carteira inserida com sucesso! Linhas afetadas: " << rowsAffected << std::endl;
    }
    catch (const sql::SQLException& e) {
        std::cerr << "Erro SQL ao inserir carteira: " << e.what() << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Erro geral ao inserir carteira: " << e.what() << std::endl;
    }

}

void OracleDao::deleteOracle(tm date) {
    try {
        std::shared_ptr<sql::Connection> conn = OracleDao::db.getConnection();

        if (!conn || !conn->isValid()) {
            std::cerr << "Erro: Conexão com o banco de dados não está válida ao tentar deletar oráculo." << std::endl;
            return;
        }

        char buffer[80];
        std::strftime(buffer, sizeof(buffer), "%Y-%m-%d", &date);
        std::string date_sql_format(buffer);

        std::string sql = "DELETE FROM oraculo WHERE data = ?";

        std::unique_ptr<sql::PreparedStatement> pstmt(conn->prepareStatement(sql));
        pstmt->setDateTime(1, date_sql_format);

        int rowsAffected = pstmt->executeUpdate();
        std::cout << "Oráculo deletado com sucesso! Linhas afetadas: " << rowsAffected << std::endl;
    }
    catch (const sql::SQLException& e) {
        std::cerr << "Erro SQL ao deletar oráculo: " << e.what() << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Erro geral ao deletar oráculo: " << e.what() << std::endl;
    }
}

Oracle* OracleDao::getOracle(tm date) {


    try {
        std::shared_ptr<sql::Connection> conn = OracleDao::db.getConnection();

        if (!conn || !conn->isValid()) {
            std::cerr << "Erro: Conexao com o banco de dados não está válida." << std::endl;
        }

        char buffer[80];
        std::strftime(buffer, sizeof(buffer), "%Y-%m-%d", &date);
        std::string date_sql_format(buffer);
        
        std::string sql = "SELECT * FROM oraculo WHERE data = ?";
        std::unique_ptr<sql::PreparedStatement> pstmt(conn->prepareStatement(sql));
        pstmt->setDateTime(1, date_sql_format);

        std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());
        tm dateNew;
        if (res->next()) {
            std::string dateStr = res->getString(1).c_str(); // Use getString to retrieve the date as a string  
            std::istringstream ss(dateStr);
            ss >> std::get_time(&dateNew, "%Y-%m-%d"); // Parse the string into a tm structure  
            double exchange = res->getDouble(2);

            Oracle* oracle = new Oracle();
            return oracle;
        }
        else {
            std::cerr << "Nenhuma oraculo encontrada com data " << date_sql_format << std::endl;
            return nullptr;
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Erro inesperado: " << e.what() << std::endl;
    }
    Oracle * oracle = new Oracle();
    return oracle;
}