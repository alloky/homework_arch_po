#include "database_mysql.h"
#include <exception>
#include <iostream>

database::Database_MySQL::Database_MySQL(){
    std::cout << "connecting to mysql ... " << std::endl;
    _con = mysql_init(nullptr);
    if(_con == nullptr) throw std::logic_error("unable to create connection object for mysql");
    if (mysql_real_connect(_con, "localhost", "root", "3.14Oneer",
          "hl", 0, NULL, 0) == NULL) {
      std::cout << "connecting to mysql ... fail" << std::endl;
      mysql_close(_con);
      throw std::logic_error(mysql_error(_con));
  }
}

bool database::Database_MySQL::query(const std::string& query,callback_t callback,callback_row_t callback_row){
    if (mysql_query(_con, query.c_str()))  throw std::logic_error(query);
    MYSQL_RES *result = mysql_store_result(_con);
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
    return true;
}

void database::Database_MySQL::execute(std::string& query){
    if (mysql_query(_con, query.c_str()))  throw std::logic_error(query);
}

database::Database_MySQL::~Database_MySQL(){
    mysql_close(_con);
}

database::Database_MySQL& database::Database_MySQL::get(){
    static Database_MySQL instance;
    return instance;
}

std::string database::Database_MySQL::get_version(){
    return std::string(mysql_get_client_info());
}