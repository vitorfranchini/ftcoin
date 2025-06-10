#ifndef SERVER_DB_CONNECTION_HPP
#define SERVER_DB_CONNECTION_HPP

#include <mariadb/conncpp.hpp>
#include <memory>
#include <string>


class ServerDBConnection
{
private:
    static const std::string DB_HOST;
    static const std::string DB_USER;
    static const std::string DB_PASSWORD;
    static const std::string DB_NAME;
    static const int DB_PORT;

    std::shared_ptr<sql::Connection> conn;
	
public:
    ServerDBConnection();
    ~ServerDBConnection();
    std::shared_ptr<sql::Connection> getConnection();
};

#endif