#ifndef ANTARCLICA_MACHINE_HPP
#define ANTARCLICA_MACHINE_HPP


#include "APIEntity.hpp"

class Machine : public APIEntity {
public:
    string name;

    explicit Machine(const json &val) : APIEntity(val) {
        JsonUtils::checkJsonTypes(val, {{"name", json::value_t::string}});
        name = val["name"];
    }

};


#endif //ANTARCLICA_MACHINE_HPP
