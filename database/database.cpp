#include <exception>
#include <iostream>
#include <iomanip>
#include <string>
#include "database.h"

#define  DATABASE_NAME "hello_conference.sqlite"

namespace database
{



void TraceDatabase(std::string &query){
    std::cout << "QUERY: " << query << std::endl;
}

Database::Database()
{
    std::lock_guard<std::mutex> lock(mtx);
    handle = nullptr;

    // open database
    if (sqlite3_open(DATABASE_NAME, &handle))
    {
        std::string error{"sqlite3_open failed!"};
        error += sqlite3_errmsg(handle);
        throw std::logic_error(error);
    }
}

Database &Database::get_instance()
{
    static Database instance;
    return instance;
}

std::string Database::to_database_value(types::database_result_t t)
{
    std::string res;
    switch (t.index())
    {
    case int(types::database_type::DOUBLE):
    case int(types::database_type::FLOAT):
    case int(types::database_type::INT64_T):
    case int(types::database_type::UINT64_T):
    case int(types::database_type::INT32_T):
    case int(types::database_type::UINT32_T):
    case int(types::database_type::BOOL):
        std::visit([&](auto &&val){
                        res = std::to_string(val);
                    },t);
        
        break;
    case int(types::database_type::STRING):
        res = "'";
        res += std::get<std::string>(t);
        res += "'";
        break;

    case int(types::database_type::BLOB):
        res += "?";
        break;
    }
    return res;
}
std::string Database::to_database_type(types::database_result_t t)
{
    switch (t.index())
    {
    case int(types::database_type::DOUBLE):
    case int(types::database_type::FLOAT):
        return "REAL";
    case int(types::database_type::INT64_T):
    case int(types::database_type::UINT64_T):
    case int(types::database_type::INT32_T):
    case int(types::database_type::UINT32_T):
    case int(types::database_type::BOOL):
        return "INTEGER";
    case int(types::database_type::STRING):
        return "VARCHAR(4096)";
    case int(types::database_type::BLOB):
        return "BLOB";
    }

    throw std::logic_error("wrong type");
}

void Database::init(const std::string &name,
                    const std::string &key_name,
                    std::map<std::string, types::database_result_t> &columns)
{
    if (inited_tables.find(name) == std::end(inited_tables))
    {

        create_table(name, key_name, columns);
        inited_tables.insert(name);
    }
}

void Database::create_table(const std::string &name,
                            const std::string &key_name,
                            std::map<std::string, types::database_result_t> &columns)
{

    char *errMsg = nullptr;

    if (columns.find(key_name) == std::end(columns))
        throw std::logic_error("no type for ckey column");

    std::string query = "CREATE TABLE IF NOT EXISTS ";
    query += name;
    query += "(";
    query += key_name;
    query += " ";
    query += to_database_type(columns[key_name]);
    query += " NOT NULL";
    for (auto [n, t] : columns)
    {
        if (n != key_name)
        {
            query += ", ";
            query += n;
            query += " ";
            query += to_database_type(t);
        }
    }
    query += ", PRIMARY KEY(";
    query += key_name;
    query += "));";

    TraceDatabase(query);
    if (sqlite3_exec(handle, query.c_str(), nullptr, nullptr, &errMsg))
    {
        std::string error{"sqlite3_exec with query failed!"};
        error += errMsg;
        sqlite3_free(errMsg);
        throw std::logic_error(error);
    }

    query = "CREATE UNIQUE INDEX IF NOT EXISTS index_";
    query += name;
    query += " ON ";
    query += name;
    query += "(";
    query += key_name;
    query += ");";
    if (sqlite3_exec(handle, query.c_str(), nullptr, nullptr, &errMsg))
    {
        std::string error{"sqlite3_exec with createIndexA failed!"};
        error += errMsg;
        sqlite3_free(errMsg);
        throw std::logic_error(error);
    }
}

types::database_result_t Database::read_value(sqlite3_stmt *res, size_t index, types::database_result_t field_type)
{
    switch (field_type.index())
    {
    case int(types::database_type::DOUBLE):{
        float val = sqlite3_column_double(res, index);
        return val;}
    case int(types::database_type::FLOAT):{
        double val =sqlite3_column_double(res, index);
        return val;}
    case int(types::database_type::INT64_T):{
        int64_t val = sqlite3_column_int64(res, index);
        return val;}
    case int(types::database_type::UINT64_T):{
        uint64_t val= sqlite3_column_int64(res, index);
        return val;}
    case int(types::database_type::INT32_T):{
        int32_t val = sqlite3_column_int(res, index);
        return val;}
    case int(types::database_type::UINT32_T):{
        uint32_t val = sqlite3_column_int(res, index);
        return val;}
    case int(types::database_type::BOOL):{
        bool val = sqlite3_column_int(res, index);
        return val;}
    case int(types::database_type::STRING):{
        std::string val{(const char *)sqlite3_column_text(res, index)};
        return val;}
    case int(types::database_type::BLOB):
    {
        types::BLOB blob;
        size_t length = sqlite3_column_bytes(res, index);
        if (length > 0)
        {
            const char *buffer = (const char *)sqlite3_column_blob(res, index);
            for (size_t i = 0; i < length; ++i)
                blob.buffer.push_back(buffer[i]);
        }
        return blob;
    }
    }

    throw std::logic_error("unknown type reading from database");
}

std::vector<std::map<std::string, types::database_result_t>> Database::select_all(const std::string &name, const std::string &key_name, std::map<std::string, types::database_result_t> &columns)
{
    std::lock_guard<std::mutex> lock(mtx);
    std::string query;
    std::vector<std::map<std::string, types::database_result_t>> result;

    init(name, key_name, columns);

    query = "SELECT ";
    auto it = std::begin(columns);
    while (it != std::end(columns))
    {
        query += it->first;
        ++it;
        if (it != std::end(columns))
            query += ',';
        else
            query += ' ';
    }

    query += "FROM ";
    query += name;

    sqlite3_stmt *res;
    const char *tail;

    TraceDatabase(query);
    if (sqlite3_prepare(handle, query.c_str(), query.length(), &res, &tail) != SQLITE_OK)
    {
        std::string error{sqlite3_errmsg(handle)};
        throw std::logic_error(error);
    }
    while (sqlite3_step(res) == SQLITE_ROW)
    {
        std::map<std::string, types::database_result_t> row;
        auto it = std::begin(columns);
        for (size_t i = 0; i < columns.size(); ++i, ++it)
            row[it->first] = read_value(res, i, it->second);
        result.push_back(row);
    }

    return result;
}

std::map<std::string, types::database_result_t> Database::find(const std::string &name, const std::string &key_name, const std::string &key_value, std::map<std::string, types::database_result_t> &columns)
{
    std::lock_guard<std::mutex> lock(mtx);
    std::string query;
    std::map<std::string, types::database_result_t> result;

    init(name, key_name, columns);

    query = "SELECT ";
    auto it = std::begin(columns);
    while (it != std::end(columns))
    {
        query += it->first;
        ++it;
        if (it != std::end(columns))
            query += ',';
        else
            query += ' ';
    }
    query += "FROM ";
    query += name;
    query += " WHERE ";
    query += key_name;
    query += "='";
    query += key_value;
    query += "'";

    sqlite3_stmt *res;
    const char *tail;

    TraceDatabase(query);
    if (sqlite3_prepare(handle, query.c_str(), query.length(), &res, &tail) != SQLITE_OK)
    {
        std::string error{sqlite3_errmsg(handle)};
        throw std::logic_error(error);
    }

    if (sqlite3_step(res) == SQLITE_ROW)
    {
        auto it = std::begin(columns);
        for (size_t i = 0; i < columns.size(); ++i, ++it)
            result[it->first] = read_value(res, i, it->second);
    }
    else
        throw types::NotFoundException();
    return result;
}

void Database::insert(const std::string &name, const std::string &key_name, std::map<std::string, types::database_result_t> &values)
{
    std::lock_guard<std::mutex> lock(mtx);
    std::string query;
    init(name, key_name, values);

    query = "INSERT INTO ";
    query += name;
    query += " (";
    size_t i{};
    for (auto [n, v] : values)
    {
        query += n;
        ++i;
        if (i < values.size())
            query += ',';
        else
            query += ')';
    }
    query += " VALUES (";
    i = 0;
    for (auto [n, v] : values)
    {
        ++i;
        query += to_database_value(v);
        if (i < values.size())
            query += ',';
        else
            query += ')';
    }

    sqlite3_stmt *res;

    TraceDatabase(query);
    if (sqlite3_prepare_v2(handle, query.c_str(), query.length(), &res, NULL) != SQLITE_OK)
    {
        std::string error{sqlite3_errmsg(handle)};
        throw std::logic_error(error);
    }

    size_t index = 1;
    for (auto [n, v] : values)
    {
        if (v.index() == int(types::database_type::BLOB))
        {
            types::BLOB &blob = std::get<types::BLOB>(v);
            if (sqlite3_bind_blob(res, index, blob.buffer.c_str(), blob.buffer.size(), SQLITE_TRANSIENT) != SQLITE_OK)
            {
                std::string error{sqlite3_errmsg(handle)};
                throw std::logic_error(error);
            }
            ++index;
        }
    }

    if(sqlite3_step(res)!=SQLITE_DONE) throw types::AlreadyExistException();
      
}

void Database::update(const std::string &name, const std::string &key_name, std::map<std::string, types::database_result_t> &values)
{
    std::lock_guard<std::mutex> lock(mtx);
    std::string query;

    init(name, key_name, values);

    query = "UPDATE ";
    query += name;
    query += " SET ";
    size_t i{};
    for (auto [n, v] : values)
    {
        query += n;
        query += '=';
        query += to_database_value(v);
        ++i;
        if (i < values.size())
            query += ',';
    }
    query += " WHERE ";
    query += key_name;
    query += '=';
    auto key_value = values[key_name];

    query += to_database_value(key_value);

    sqlite3_stmt *res;

    TraceDatabase(query);
    if (sqlite3_prepare_v2(handle, query.c_str(), query.length(), &res, NULL) != SQLITE_OK)
    {
        std::string error{sqlite3_errmsg(handle)};
        throw std::logic_error(error);
    }

    size_t index = 1;
    for (auto [n, v] : values)
    {
        if (v.index() == int(types::database_type::BLOB))
        {
            types::BLOB &blob = std::get<types::BLOB>(v);
            if (sqlite3_bind_blob(res, index, blob.buffer.c_str(), blob.buffer.size(), SQLITE_TRANSIENT) != SQLITE_OK)
            {
                std::string error{sqlite3_errmsg(handle)};
                throw std::logic_error(error);
            }
            ++index;
        }
    }

    sqlite3_step(res);
}

Database::~Database()
{
    sqlite3_close(handle);
}
} // namespace database
