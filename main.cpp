#include <iostream>
#include <string>

#include "web_server/httpwebserver.h"
#include "database/database.h"


auto main(int argc,char* argv[]) -> int{
    HTTPWebServer app;

    database::Database::get();
    return app.run(argc, argv);

}