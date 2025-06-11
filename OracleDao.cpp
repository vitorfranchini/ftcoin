
#include "OracleDao.hpp"
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
        std::shared_ptr<sql::Connection> conn = OracleDao::db.getConnection();
        
        if (!conn || !conn->isValid()) {
            std::cerr << "Erro: Conexão com o banco de dados não está valida." << std::endl;
            return;
        }

        tm date = oracle->getDate();
        double exchange = oracle->getExchange();

        

        std::string sql = "INSERT INTO oraculo (date, exchange) VALUES (?, ?)";
        std::unique_ptr<sql::PreparedStatement> pstmt(conn->prepareStatement(sql));
        
        char buffer[80];
        std::strftime(buffer, sizeof(buffer), "%Y-%m-%d", &date);
        std::string dateSqlFormat(buffer);
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
    try {
        std::shared_ptr<sql::Connection> conn = OracleDao::db.getConnection(); 

        if (!conn || !conn->isValid()) {
            std::cerr << "Erro: Conexão com o banco de dados não está valida." << std::endl;
            return;
        }
        
        tm date = oracle->getDate();
        double exchange = oracle->getExchange();
      
        std::string sql = "UPDATE oraculo SET exchange = ? WHERE date = ?";     
        std::unique_ptr<sql::PreparedStatement> pstmt(conn->prepareStatement(sql));

        pstmt->setFloat(1, exchange);
        
        char buffer[80];
        std::strftime(buffer, sizeof(buffer), "%Y-%m-%d", &date);
        std::string dateSqlFormat(buffer);
        pstmt->setDateTime(2, dateSqlFormat);

        int rowsAffected = pstmt->executeUpdate(); 
        std::cout << "Carteira inserida com sucesso! Linhas afetadas: " << rowsAffected << std::endl;
    }
    catch (const sql::SQLException& e) {
        std::cerr << "Erro no banco de dados " << e.what() << std::endl;
    }
}

void OracleDao::deleteOracle(tm date) {
    try {
        std::shared_ptr<sql::Connection> conn = OracleDao::db.getConnection();

        if (!conn || !conn->isValid()) {
            std::cerr << "Erro: Conexão com o banco de dados não está valida." << std::endl;
            return;
        }

        
        std::string sql = "DELETE FROM oraculo WHERE date = ?";
        std::unique_ptr<sql::PreparedStatement> pstmt(conn->prepareStatement(sql));

        char buffer[80];
        std::strftime(buffer, sizeof(buffer), "%Y-%m-%d", &date);
        std::string dateSqlFormat(buffer);
        pstmt->setDateTime(1, dateSqlFormat);

        int rowsAffected = pstmt->executeUpdate();
        std::cout << "Oráculo deletado com sucesso! Linhas afetadas: " << rowsAffected << std::endl;
    }
    catch (const sql::SQLException& e) {
        std::cerr << "Erro no banco de dados " << e.what() << std::endl;
    }
}

Oracle* OracleDao::getOracleByDate(tm date) {
    try {
        std::shared_ptr<sql::Connection> conn = OracleDao::db.getConnection();

        if (!conn || !conn->isValid()) {
            std::cerr << "Erro: Conexão com o banco de dados não está valida." << std::endl;
            return nullptr;
        }

        std::string sql = "SELECT * FROM oraculo WHERE date = ?";
        std::unique_ptr<sql::PreparedStatement> pstmt(conn->prepareStatement(sql));

        char buffer[80];
        std::strftime(buffer, sizeof(buffer), "%Y-%m-%d", &date);
        std::string dateSqlFormat(buffer);
        pstmt->setDateTime(1, dateSqlFormat);

        std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());
        tm date;
        if (res->next()) {
            std::string dateStr = res->getString(1).c_str(); // Use getString to retrieve the date as a string  
            std::istringstream ss(dateStr);
            ss >> std::get_time(&date, "%Y-%m-%d"); // Parse the string into a tm structure  
            double exchange = res->getDouble(2);

            Oracle* oracle = new Oracle(date, exchange);
            return oracle;
        }
        else {
            std::cerr << "Nenhuma oraculo encontrada com data " << dateSqlFormat << std::endl;
            return nullptr;
        }
    }
    catch (const sql::SQLException& e) {
        std::cerr << "Erro no banco de dados " << e.what() << std::endl;
        return nullptr;
    }
   
}