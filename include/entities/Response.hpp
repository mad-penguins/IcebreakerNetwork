#ifndef ANTARCLICA_RESPONSE_HPP
#define ANTARCLICA_RESPONSE_HPP


#include <utility>

#include "Status.hpp"


class Response {
public:
    shared_ptr<Status> status;

    explicit Response(const json &val) {
        JsonUtils::checkJsonTypes(val, {{"status", json::value_t::object}});
        status = make_shared<Status>(val["status"]);
    }
};


#endif //ANTARCLICA_RESPONSE_HPP
