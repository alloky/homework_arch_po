#ifndef DATABASEMYSQL_H
#define DATABASEMYSQL_H


#include <mysql/mysql.h>
#include <string>
#include <functional>

using callback_t = std::function<void(int,int,const std::string)>;
using callback_row_t = std::function<void(int)>;

namespace database{
    class Database_MySQL{
            private:
                Database_MySQL();

                MYSQL *_con;
            public:
                bool query(const std::string& query,callback_t callback,callback_row_t callback_row);
                void execute(std::string& query);
                static Database_MySQL& get();
                static std::string get_version();
                ~Database_MySQL();
    };
}

#endif