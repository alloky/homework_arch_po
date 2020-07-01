#ifndef DATABASE_H
#define DATABASE_H

#include <memory>
#include <mutex>
#include <utility>
#include <map>
#include <set>
#include <vector>

#include "../sqlite/sqlite3.h"
#include "../types/types.h"

namespace database{
    

    

    class Database{
        private:
            sqlite3*              handle;
            std::mutex            mtx;
            std::set<std::string> inited_tables;
            Database();

            types::database_result_t read_value(sqlite3_stmt *res,size_t index,types::database_result_t field_type);
            std::string            to_database_type(types::database_result_t t);
            std::string            to_database_value(types::database_result_t t);
            void                  init(const std::string & name,
                                       const std::string & key_name,  
                                       std::map<std::string,types::database_result_t> & columns);
            void create_table(const std::string & name,
                              const std::string & key_name,
                              std::map<std::string,types::database_result_t> & columns);
            public:
            static Database& get_instance();
            std::vector<std::map<std::string,types::database_result_t>> select_all(const std::string & name,
                                                                                   const std::string & key_name,  
                                                                                   std::map<std::string,types::database_result_t> & columns);
            std::map<std::string,types::database_result_t> find(const std::string & name, 
                                                                const std::string & key, 
                                                                const std::string & key_value, 
                                                                std::map<std::string,types::database_result_t> & columns);

             void insert(const std::string & name,const std::string & key_name, 
                         std::map<std::string,types::database_result_t> & values);
             void update(const std::string & name,const std::string &key_name, 
                         std::map<std::string,types::database_result_t> & values);
            ~Database();
            
    };
}

#endif