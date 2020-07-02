#include <iostream>
#include <string>

#include "web_server/httpwebserver.h"
#include "database/database.h"

#include "Poco/HMACEngine.h"
#include "Poco/SHA1Engine.h"

using Poco::DigestEngine;
using Poco::SHA1Engine;
using Poco::HMACEngine;

auto main(int argc,char* argv[]) -> int{
    std::string message("guest");
    HMACEngine<SHA1Engine> hmac(message); // we'll compute a HMAC-SHA1
    const DigestEngine::Digest& digest = hmac.digest();
    std::string digestString(DigestEngine::digestToHex(digest));    
    std::cout << digestString <<std::endl;

    HTTPWebServer app;

    database::Database::get();
    return app.run(argc, argv);

}