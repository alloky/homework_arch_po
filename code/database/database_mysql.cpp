#include "database_mysql.h"
#include <exception>
#include <iostream>
#include <thread>

#include "../web_server/config.h"
database::Database_MySQL::Database_MySQL()
{
}

database::Connection database::Database_MySQL::acquire(ConnectionType ct)
{
    MYSQL *_con;
    std::string server_ip = "db";

    switch (ct)
    {
    case ConnectionType::READ:
        server_ip = Config::get().get_read_request_ip();
        break;
    case ConnectionType::WRITE:
        server_ip = Config::get().get_write_request_ip();
        break;
    };
    _con = mysql_init(nullptr);
    if (_con == nullptr)
        throw std::logic_error("unable to create connection object for mysql");
    int ret = 0;
    if (mysql_real_connect(_con, server_ip.c_str(), "root", "3.14Oneer",
                           "hl", 
                           3306 /* port */,  NULL, 0) == NULL)
    {
        std::cout << "Failed to connect to database: Error: " << mysql_error(_con) << std::endl;
        mysql_close(_con);
        throw std::logic_error(mysql_error(_con));
    }
    return Connection(_con);

    throw std::logic_error("Unable to get mysql connection");
}

void database::Database_MySQL::release(database::Connection &connection)
{
    mysql_close(connection._con);
}

bool database::Database_MySQL::query(const std::string &query, callback_t callback, callback_row_t callback_row)
{

    database::Connection con = acquire(ConnectionType::READ);

    try
    {
        if (mysql_query(con._con, query.c_str()))
            throw std::logic_error(query);
        MYSQL_RES *result = mysql_store_result(con._con);
        if (result == NULL)
            throw std::logic_error(query);
        int num_fields = mysql_num_fields(result);
        MYSQL_ROW row;
        int row_num{};
        while ((row = mysql_fetch_row(result)))
        {
            for (int i = 0; i < num_fields; i++)
            {
                callback(row_num, i, std::string(row[i]));
            }
            callback_row(row_num);
            ++row_num;
        }
        mysql_free_result(result);
    }
    catch (...)
    {
        release(con);
        throw;
    }

    release(con);
    return true;
}

void database::Database_MySQL::execute(std::string &query)
{

    database::Connection con = acquire(ConnectionType::WRITE);

    try
    {
        if (mysql_query(con._con, query.c_str()))
            throw std::logic_error(query);
    }
    catch (...)
    {
        release(con);
        throw;
    }

    release(con);
}

database::Database_MySQL::~Database_MySQL()
{
    for (auto c : _pool)
        mysql_close(c._con);
}

database::Database_MySQL &database::Database_MySQL::get()
{
    static Database_MySQL instance;
    return instance;
}

std::string database::Database_MySQL::get_version()
{
    return std::string(mysql_get_client_info());
}