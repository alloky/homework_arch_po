#include "database_mysql.h"
#include <exception>
#include <iostream>
#include <thread>

database::Database_MySQL::Database_MySQL(){
    /*
    static const int POOL_SIZE = 120;

    for(int i = 0; i<POOL_SIZE;++i){
         MYSQL *_con;
        _con = mysql_init(nullptr);
        if(_con == nullptr) throw std::logic_error("unable to create connection object for mysql");
        if (mysql_real_connect(_con, "localhost", "root", "3.14Oneer",
          "hl", 0, NULL, 0) == NULL) {
            mysql_close(_con);
            throw std::logic_error(mysql_error(_con));
        }
        _pool.push_back(database::Connection(_con));
    }

    std::cout << "MySQL connection pool inited:" << POOL_SIZE << std::endl;
    //*/
}

database::Connection database::Database_MySQL::acquire(){
 //*
    MYSQL *_con;
    _con = mysql_init(nullptr);
    if(_con == nullptr) throw std::logic_error("unable to create connection object for mysql");
    if (mysql_real_connect(_con, "localhost", "root", "3.14Oneer",
          "hl", 0, NULL, 0) == NULL) {
            mysql_close(_con);
            throw std::logic_error(mysql_error(_con));
        }
    return Connection(_con);
    /*/    
    while(true){
         std::lock_guard<std::mutex> lck(_pool_mutex);
         if(!_pool.empty()) {
             database::Connection result = _pool.back();
             _pool.pop_back();
             return result;
         } else std::this_thread::yield();

    }
    //*/
    throw std::logic_error("Unable to get mysql connection");

}

void       database::Database_MySQL::release(database::Connection& connection){
   //*
    mysql_close(connection._con);
    /*/
    std::lock_guard<std::mutex> lck(_pool_mutex);
    _pool.push_back(connection);
    //*/
}

bool database::Database_MySQL::query(const std::string& query,callback_t callback,callback_row_t callback_row){
   
    database::Connection con = acquire();

    try{
        if (mysql_query(con._con, query.c_str()))  throw std::logic_error(query);
        MYSQL_RES *result = mysql_store_result(con._con);
        if (result == NULL)  throw std::logic_error(query);
        int num_fields = mysql_num_fields(result);
        MYSQL_ROW row;
        int row_num{};
        while ((row = mysql_fetch_row(result))) { 
            for(int i = 0; i < num_fields; i++) { 
                callback(row_num,i,std::string(row[i]));
            } 
            callback_row(row_num);
            ++row_num;
        }
        mysql_free_result(result);
    }catch(...){
        release(con);
        throw;
    }

    release(con);
    return true;
}

void database::Database_MySQL::execute(std::string& query){

    database::Connection con = acquire();
    
    try{
            if (mysql_query(con._con, query.c_str()))  throw std::logic_error(query);
     }catch(...){
        release(con);
        throw;
    }

    release(con);

}

database::Database_MySQL::~Database_MySQL(){
    for(auto c: _pool)
        mysql_close(c._con);
}

database::Database_MySQL& database::Database_MySQL::get(){
    static Database_MySQL instance;
    return instance;
}

std::string database::Database_MySQL::get_version(){
    return std::string(mysql_get_client_info());
}