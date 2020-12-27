#ifndef ANTARCLICA_STATUS_HPP
#define ANTARCLICA_STATUS_HPP


#include <string>
#include <nlohmann/json.hpp>

#include "utils/JsonUtils.hpp"

using namespace std;
using json = nlohmann::json;

class Status {
public:
    string str;
    Code code;

    explicit Status(const json &val) {
        JsonUtils::checkJsonTypes(val, {
                {"code",   json::value_t::number_unsigned},
                {"string", json::value_t::string},
        });

        code = static_cast<Code>(val["code"]);
        str = val["string"];
    }
};

#endif //ANTARCLICA_STATUS_HPP
