#ifndef PERSON_H
#define PERSON_H

#include <string>
namespace Database{
    struct Person{
            std::string login;
            std::string password_hash;

            std::string first_name;
            std::string last_name;
            int         age;
            std::string hobby;
            std::string city;
    };
}
#endif