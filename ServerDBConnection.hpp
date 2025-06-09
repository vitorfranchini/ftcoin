#ifndef SERVER_DB_CONNECTION
#define SERVER_DB_CONNECTION
#include <cstdint>     // Inclua antes
#include <string>
#include <stdexcept>
#include <mysql_driver.h>
#include <mysql_connection.h>



class ServerDBConnection
{
private:
    sql::mysql::MySQL_Driver* driver;
    sql::Connection* conn;
public:
    ServerDBConnection();
    ~ServerDBConnection();
    void teste();
};

#endif