#ifndef CHAT_H
#define CHAT_H

#include "Poco/JSON/Object.h"
#include <string>
#include <vector>
#include "database_mysql.h"

namespace database{
    struct Chat{
            long        id;
            std::string time;
            std::string source_login;
            std::string destination_login;
            std::string message;


            Poco::JSON::Object::Ptr toJSON() const{
                Poco::JSON::Object::Ptr root = new Poco::JSON::Object();
                root->set("id",id);
                root->set("time",time);
                root->set("source_login",source_login);
                root->set("destination_login",destination_login);
                root->set("message",message);
                return root;
            }

            static void init(){
                try{
                    std::cout << "initializing chat ..." << std::endl;
                    std::string query = "CREATE TABLE `chat` (`id` INT NOT NULL AUTO_INCREMENT,`time` DATETIME NOT NULL, `source_login` VARCHAR(256) NOT NULL,`destination_login` VARCHAR(256) NOT NULL,`message` VARCHAR(1024) NULL,PRIMARY KEY (`id`),KEY `source` (`source_login`),KEY `destination` (`destination_login`));";
                    database::Database_MySQL::get().execute(query);
                    std::cout << "initializing person ... done" << std::endl;
                }catch(...){
                    std::cout << "initializing person ... fail" << std::endl;
                }

            }


            static std::vector<Person> get_chat(const std::string &login){
                std::vector<Chat> result;
                Chat chat;

                std::string query="SELECT id, 'time', source_login,destination_login,message FROM chat WHERE source_login='";
                query += login;
                query += "' OR destination_login='";
                query += login;
                query += "';";
                database::Database_MySQL::get().query(query,[&](int ,int column,std::string value)
                {
                        switch(column){
                            case 0: chat.id = atoi(value.c_str()); break;
                            case 1: chat.time= value;break;
                            case 2: chat.source_login=value;break;
                            case 3: chat.destination_login=value;break;
                            case 4: chat.message=value;break;
                        }
                    
                },[&](int){
                    result.push_back(chat);
                });
                

                return result;
            }

            /*

            void insert(){
                std::string query="INSERT INTO person VALUES(";
                query+="'"+login+"',";
                query+="'"+password_hash+"',";
                query+="'"+first_name+"',";
                query+="'"+last_name+"',";
                query+="'"+std::to_string(age)+"',";
                query+="'"+hobby+"',";
                query+="'"+city+"'";
                query+=")";
                database::Database_MySQL::get().execute(query);
            }*/
    };
}
#endif