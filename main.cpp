#include <iostream>
#include <string>

#include "web_server/httpwebserver.h"

auto main(int argc, char *argv[]) -> int{
    HTTPWebServer app;
    return app.run(argc, argv);

}