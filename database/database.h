#ifndef DATABASE_H
#define DATABASE_H

#include "Poco/Data/Session.h"
#include "Poco/Data/MySQL/Connector.h"
#include "Poco/Data/SessionFactory.h"
#include "Poco/Data/MySQL/MySQLException.h"
#include <mutex>
#include <vector>

using namespace Poco::Data::Keywords;
using Poco::Data::Session;
using Poco::Data::Statement;


namespace database{
    class Database{
        private:
            Poco::Data::Session _session;
            Database();
        public:
            static Database& get();
            Poco::Data::Session &get_session();

    };
}

#endif