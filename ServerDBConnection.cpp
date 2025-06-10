
#include <mariadb/conncpp.hpp>
#include "ServerDBConnection.hpp"
#include <iostream>
#include <stdexcept>

const std::string ServerDBConnection::DB_HOST = "localhost";
const std::string ServerDBConnection::DB_USER = "root";
const std::string ServerDBConnection::DB_PASSWORD = "";
const std::string ServerDBConnection::DB_NAME = "ftcoin";
const int ServerDBConnection::DB_PORT = 3306;

ServerDBConnection::ServerDBConnection() {
    try {
   
        // Configurar os parâmetros da conexão
        std::string urlString = "jdbc:mariadb://" + DB_HOST + ":" + std::to_string(DB_PORT) + "/" + DB_NAME;
        sql::SQLString url(urlString); 
        sql::Properties properties({
            {"user", DB_USER},
            {"password", DB_PASSWORD}  
            });

        sql::Driver* driver = sql::mariadb::get_driver_instance();
        conn = std::shared_ptr<sql::Connection>(driver->connect(url, properties));
 
    }
    catch (const sql::SQLException& e) {
        std::cout << "Erro de SQL: " << e.what() << std::endl;
       
    }

}

ServerDBConnection::~ServerDBConnection() {
    
}

std::shared_ptr<sql::Connection> ServerDBConnection::getConnection() {
    return conn;
}
