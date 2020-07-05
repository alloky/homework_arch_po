#ifndef PERSON_H
#define PERSON_H

#include "Poco/JSON/Object.h"
#include <string>
#include <vector>
#include "database.h"

namespace database{
    struct Person{
            std::string login;
            std::string password_hash;

            std::string first_name;
            std::string last_name;
            int         age;
            std::string hobby;
            std::string city;

            Poco::JSON::Object::Ptr toJSON() const{
                Poco::JSON::Object::Ptr root = new Poco::JSON::Object();

                root->set("login",login);
                root->set("password_hash",password_hash);
                root->set("first_name",first_name);
                root->set("last_name",last_name);
                root->set("age",age);
                root->set("hobby",hobby);
                root->set("city",city);
                return root;
            }

            static bool   check_exist(std::string & login){
                int count{};
                Statement select(Database::get().get_session());
                select << "SELECT count(*) FROM hl.person WHERE login=?",
                    into(count),
                    use(login),
                    range(0, 1);

                while (!select.done())
                {
                    select.execute();
                    if(select.rowsExtracted()>0)
                                        return count>0;
                                        else throw std::logic_error("Not found");
                }

                throw std::logic_error("Not found");
            }

            static Person get_person(std::string & match){
                Person person;

                Statement select(Database::get().get_session());
                select << "SELECT login, password_hash, first_name,last_name,age,hobby,city FROM hl.person WHERE login=?",
                    into(person.login),
                    into(person.password_hash),
                    into(person.first_name),
                    into(person.last_name),
                    into(person.age),
                    into(person.hobby),
                    into(person.city),
                    use(match),
                    range(0, 1); //  iterate over result set one row at a time

                while (!select.done())
                {
                    select.execute();
                    if(select.rowsExtracted()>0)
                                        return person;
                                        else throw std::logic_error("Not found");
                }

                throw std::logic_error("Not found");
            }

            static std::vector<Person> get_persons(){
                std::vector<Person> result;
                Person person;

                Statement select(Database::get().get_session());
                select << "SELECT login, password_hash, first_name,last_name,age,hobby,city FROM hl.person",
                    into(person.login),
                    into(person.password_hash),
                    into(person.first_name),
                    into(person.last_name),
                    into(person.age),
                    into(person.hobby),
                    into(person.city),
                    range(0, 1); //  iterate over result set one row at a time

                while (!select.done())
                {
                    select.execute();
                    std::cout << person.login << " " << person.password_hash << std::endl;
                    result.push_back(person);
                }

                return result;
            }

            void insert(){
                Statement insert(Database::get().get_session());

                insert << "INSERT INTO hl.person VALUES(?,?,?,?,?,?,?)",
                    use(login),
                    use(password_hash),
                    use(first_name),
                    use(last_name),
                    use(age),
                    use(hobby),
                    use(city);
                insert.execute();
            }
    };
}
#endif