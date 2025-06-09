
#include <cstdint>     // Inclua antes
#include <string>
#include <stdexcept>
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/statement.h>
#include <cppconn/resultset.h>
#include "ServerDBConnection.hpp"
#include <iostream>
#include <stdexcept>

ServerDBConnection::ServerDBConnection(){
    try
    {
        ServerDBConnection::driver = sql::mysql::get_mysql_driver_instance();
        ServerDBConnection::conn = ServerDBConnection::driver->connect("tcp://127.0.0.1:3306", "root", "");
        ServerDBConnection::conn->setSchema("ftcoin");
    }
    catch(std::exception& e)
    {
        std::cerr << "Erro de conexao: " << e.what() << '\n';
    }
    
    
}

ServerDBConnection::~ServerDBConnection(){
    delete ServerDBConnection::conn;

}

void ServerDBConnection::teste(){
    try
    {
        sql::Statement* stmt = ServerDBConnection::conn->createStatement();
        sql::ResultSet* res = stmt->executeQuery("SELECT * FROM wallet")

        while (res->next()){
            std::cout << "Linha: " << res->getString(1) << std::endl;
        }
        delete res;
        delete stmt;
    }
    catch(const std::exception& e)
    {
        std::cerr << "Erro de consulta: " << e.what() << '\n';
    }
    

}