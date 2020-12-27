#ifndef ANTARCLICA_USER_HPP
#define ANTARCLICA_USER_HPP


#include <string>

#include "APIEntity.hpp"

using namespace std;

class User : public APIEntity {
public:
    string login;
    string displayName;
    string accessToken;

    User() : APIEntity() {};

    explicit User(const json &val) : APIEntity(val) {
        login = val["login"];
        displayName = val["name"];
        accessToken = val["token"];
    }
};


#endif //ANTARCLICA_USER_HPP
