        #ifndef PERSONHANDLER_H
        #define PERSONHANDLER_H

        #include "Poco/Net/HTTPServer.h"
        #include "Poco/Net/HTTPRequestHandler.h"
        #include "Poco/Net/HTTPRequestHandlerFactory.h"
        #include "Poco/Net/HTTPServerParams.h"
        #include "Poco/Net/HTTPServerRequest.h"
        #include "Poco/Net/HTTPServerResponse.h"
        #include "Poco/Net/HTTPServerParams.h"
        #include "Poco/Net/HTMLForm.h"
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
        #include "Poco/URI.h"

        #include <iostream>
        #include <iostream>
        #include <fstream>

        using Poco::Net::ServerSocket;
        using Poco::Net::HTTPRequestHandler;
        using Poco::Net::HTTPRequestHandlerFactory;
        using Poco::Net::HTTPServer;
        using Poco::Net::HTTPServerRequest;
        using Poco::Net::HTTPServerResponse;
        using Poco::Net::HTTPServerParams;
        using Poco::Timestamp;
        using Poco::DateTimeFormatter;
        using Poco::DateTimeFormat;
        using Poco::ThreadPool;
        using Poco::Util::ServerApplication;
        using Poco::Util::Application;
        using Poco::Util::Option;
        using Poco::Util::OptionSet;
        using Poco::Util::OptionCallback;
        using Poco::Util::HelpFormatter;
        using Poco::Net::NameValueCollection;
        using Poco::Net::HTMLForm;

        #include "../../database/person.h"
        #include "../session/session.h"

        #include <map>

        class PersonHandler: public HTTPRequestHandler
        {
        public:
            PersonHandler(const std::string& format): _format(format)
            {
            }

            void handleRequest(HTTPServerRequest& request,
                            HTTPServerResponse& response)
            {
                //Application& app = Application::instance();
                //app.logger().information("Person Request from " + request.clientAddress().toString());


                HTMLForm form(request, request.stream());
                response.setChunkedTransferEncoding(true);
                response.setContentType("application/json");
                std::ostream& ostr = response.send();
                if(form.has("session_id")){
                    std::string session_str=form.get("session_id"); 
                    
                    long  session_id = stol(session_str);

                    if(webserver::Session::get().is_correct(session_id)){
                        try{
                            std::string login = webserver::Session::get().get_login(session_id);
                            database::Person person = database::Person::get_person(login);           
                            Poco::JSON::Stringifier::stringify(person.toJSON(),ostr);
                        }catch(...){
                            std::cout << "person query exception session_id:" << session_id << std::endl;
                        }
                    } 
                } else {
                    std::cout << "here" <<  std::endl;
                    auto reqMethod = request.getMethod();
                    if (reqMethod == "GET") {
                        if (form.size() == 1) {
                            if (!form.has("login")) {
                                response.setStatus(Poco::Net::HTTPResponse::HTTPStatus::HTTP_BAD_REQUEST);
                            }
                            try{
                                std::string login = form.get("login");
                                database::Person person = database::Person::get_person(login);           
                                Poco::JSON::Stringifier::stringify(person.toJSON(),ostr);
                            }catch(...){
                                // std::cout << "p << session_id << std::endl;
                                Poco::JSON::Stringifier::stringify("{}",ostr);
                            }
                        } 
                        if (form.size() == 2) {
                            std::string first_name, last_name;
                            if (form.has("first_name") && form.has("last_name")){
                                first_name = form.get("first_name") ;
                                last_name = form.get("last_name") ;
                            } else {
                                response.setStatus(Poco::Net::HTTPResponse::HTTPStatus::HTTP_BAD_REQUEST);
                                return;
                            }
                            try{
                                auto persons = database::Person::search(first_name, last_name);
                                Poco::JSON::Array result;
                                for (auto& per : persons)
                                    result.add(per.toJSON());
                                Poco::JSON::Stringifier::stringify(result, ostr);
                                    
                            }catch(...){
                                // std::cout << "p << session_id << std::endl;
                                Poco::JSON::Stringifier::stringify("{}",ostr);
                            }
                        }
                    } else if (reqMethod == "POST") {
                        std::string login, first_name, last_name;
                        long age;
                        try {
                            login=form.get("login"); 
                            first_name=form.get("first_name"); 
                            last_name=form.get("last_name");
                            age=stol(form.get("age"));
                        }
                        catch(...) {
                            response.setStatus(Poco::Net::HTTPResponse::HTTPStatus::HTTP_BAD_REQUEST);
                            return;
                        }
                        database::Person person;
                        
                        person.login = login;
                        person.password_hash = login;
                        person.first_name = first_name;
                        person.last_name = last_name;
                        person.age = age;

                        try{
                            person.insert();
                        }catch(...){
                            std::cout << "person query exception" << std::endl;
                        }
                        
                    } else {
                        response.setStatus(Poco::Net::HTTPResponse::HTTPStatus::HTTP_BAD_REQUEST);
                    }
                }
                response.setStatus(Poco::Net::HTTPResponse::HTTPStatus::HTTP_INTERNAL_SERVER_ERROR);
            }

        private:
            std::string _format;
        };
        #endif // !PERSONHANDLER_H