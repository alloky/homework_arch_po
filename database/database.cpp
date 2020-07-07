#include <exception>
#include <iostream>
#include <iomanip>
#include <string>
#include "database.h"

#define  DATABASE_NAME "host=127.0.0.1;user=root;password=3.14Oneer;"
//#define  DATABASE_NAME "Server=127.0.0.1;Database=hl;Uid=root;Pwd=3.14Oneer;"
namespace database
{

Database::Database() : _session(Poco::Data::SessionFactory::instance().create(Poco::Data::MySQL::Connector::KEY, DATABASE_NAME) )
{
 
}

Database &Database::get()
{
    Poco::Data::MySQL::Connector::registerConnector();
    try{
            static Database instance;
            return instance;
    }
    catch (Poco::Data::MySQL::ConnectionException& e)
    {
        std::cout << e.what() << std::endl;
        throw "unable to connect to datbase";
    }
    catch(Poco::Data::MySQL::StatementException& e)
    {
        std::cout << e.what() << std::endl;
        throw "unable to connect to datbase";
    }    
}

 Poco::Data::Session &Database::get_session(){
     return _session;
 }

} // namespace database
