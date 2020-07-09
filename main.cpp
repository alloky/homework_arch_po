#include <iostream>
#include <string>

#include "web_server/httpwebserver.h"

#include "database/friends.h"
#include "database/person.h"

auto main(int argc, char *argv[]) -> int{

    std::cout << "MySQL version:" << database::Database_MySQL::get_version() << std::endl;
    database::Database_MySQL::get();
    database::Person::init();
    database::Friends::init();

    HTTPWebServer app;
    return app.run(argc, argv);

}