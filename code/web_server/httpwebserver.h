#ifndef HTTPWEBSERVER_H
#define HTTPWEBSERVER_H

#include "Poco/Net/HTTPServer.h"
#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPRequestHandlerFactory.h"
#include "Poco/Net/HTTPServerParams.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/Net/HTTPServerParams.h"
#include "Poco/Net/ServerSocket.h"
#include "Poco/Timestamp.h"
#include "Poco/DateTimeFormatter.h"
#include "Poco/DateTimeFormat.h"
#include "Poco/Exception.h"
#include "Poco/ThreadPool.h"
#include "Poco/Util/ServerApplication.h"
#include "Poco/Util/Option.h"
#include "Poco/Util/OptionSet.h"
#include "Poco/Util/HelpFormatter.h"
#include <iostream>

#define UNUSED(value) (void)value

using Poco::DateTimeFormat;
using Poco::DateTimeFormatter;
using Poco::ThreadPool;
using Poco::Timestamp;
using Poco::Net::HTTPRequestHandler;
using Poco::Net::HTTPRequestHandlerFactory;
using Poco::Net::HTTPServer;
using Poco::Net::HTTPServerParams;
using Poco::Net::HTTPServerRequest;
using Poco::Net::HTTPServerResponse;
using Poco::Net::ServerSocket;
using Poco::Util::Application;
using Poco::Util::HelpFormatter;
using Poco::Util::Option;
using Poco::Util::OptionCallback;
using Poco::Util::OptionSet;
using Poco::Util::ServerApplication;

#include "httprequestfactory.h"
#include "config.h"
#include "../database/friends.h"
#include "../database/person.h"
//#include "../database/chat.h"

class HTTPWebServer : public Poco::Util::ServerApplication
{
public:
    HTTPWebServer() : _helpRequested(false)
    {
    }

    ~HTTPWebServer()
    {
    }

protected:
    void initialize(Application &self)
    {
        loadConfiguration();
        ServerApplication::initialize(self);
    }

    void uninitialize()
    {
        ServerApplication::uninitialize();
    }

    void defineOptions(OptionSet &options)
    {
        ServerApplication::defineOptions(options);

        options.addOption(
            Option("help", "h", "display argument help information")
                .required(false)
                .repeatable(false)
                .callback(OptionCallback<HTTPWebServer>(this, &HTTPWebServer::handleHelp)));
       options.addOption(
            Option("read", "r", "set ip address for read requests")
                .required(false)
                .repeatable(false)
                .argument("value")
                .callback(OptionCallback<HTTPWebServer>(this, &HTTPWebServer::handleReadIP)));
       options.addOption(
            Option("write", "w", "set ip address for write requests")
                .required(false)
                .repeatable(false)
                .argument("value")
                .callback(OptionCallback<HTTPWebServer>(this, &HTTPWebServer::handleWriteIP)));
       options.addOption(
            Option("init_db", "db", "create database tables")
                .required(false)
                .repeatable(false)
                .callback(OptionCallback<HTTPWebServer>(this, &HTTPWebServer::handleInitDB)));    
    }

    void handleInitDB(const std::string &name,
                    const std::string &value)
    {
        database::Person::init();
        database::Friends::init();
        //database::Chat::init();

        UNUSED(name);
        UNUSED(value);
    }

    void handleReadIP(const std::string &name,
                    const std::string &value)
    {
        std::cout << name << "=" << value << std::endl;
        Config::get().read_request_ip()=value;
        UNUSED(name);
        UNUSED(value);
    }

    void handleWriteIP(const std::string &name,
                    const std::string &value)
    {
        std::cout << name << "=" << value << std::endl;
        Config::get().write_request_ip()=value;
        UNUSED(name);
        UNUSED(value);
    }
 
    void handleHelp(const std::string &name,
                    const std::string &value)
    {
        HelpFormatter helpFormatter(options());
        helpFormatter.setCommand(commandName());
        helpFormatter.setUsage("OPTIONS");
        helpFormatter.setHeader(
            "A web server that serves the current date and time.");
        helpFormatter.format(std::cout);
        stopOptionsProcessing();
        _helpRequested = true;

        UNUSED(name);
        UNUSED(value);
    }

    int main(const std::vector<std::string> &args)
    {
        if (!_helpRequested)
        {
            unsigned short port = (unsigned short)
                                      config()
                                          .getInt("HTTPWebServer.port", 1234);
            std::string format(
                config().getString("HTTPWebServer.format",
                                   DateTimeFormat::SORTABLE_FORMAT));

            ServerSocket svs(Poco::Net::SocketAddress("0.0.0.0", port));
            HTTPServer srv(new HTTPRequestFactory(format),
                           svs, new HTTPServerParams);
            std::cout << "starting server ..." << std::endl;
            srv.start();
            waitForTerminationRequest();
            srv.stop();
        }
        UNUSED(args);
        return Application::EXIT_OK;
    }

private:
    bool _helpRequested;
};
#endif // !HTTPWEBSERVER
