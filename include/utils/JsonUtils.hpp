#ifndef ANTARCLICA_JSONUTILS_HPP
#define ANTARCLICA_JSONUTILS_HPP

#include <string>
#include <nlohmann/json.hpp>

#include "entities/Code.h"

using namespace std;
using json = nlohmann::json;

class JsonUtils {
public:
    static string typeName(json::value_t type) noexcept {
        using nlohmann::detail::value_t;
        switch (type) {
            case value_t::null:
                return "null";
            case value_t::object:
                return "object";
            case value_t::array:
                return "array";
            case value_t::string:
                return "string";
            case value_t::boolean:
                return "boolean";
            case value_t::discarded:
                return "discarded";
            default:
                return "number";
        }
    }

    class JsonTypeException : public exception {
        string key{};
        json::value_t expected{};
        json::value_t got{};
    public:
        JsonTypeException(const string &key, const json::value_t &expected, const json::value_t &got) {
            this->key = key;
            this->expected = expected;
            this->got = got;
        }

        string message() {
            return "value \'" + key + "\' has wrong type \'" + typeName(got) + "\', but expected \'" +
                   typeName(expected) + "\''";
        }
    };


    static bool checkJsonTypes(const json &val, const map<string, json::value_t> &values) {
        using nlohmann::detail::value_t;
        for (const auto &[key, expectedType] : values) {
            if (val.contains(key)) {
                if (val[key].type() != expectedType) {
                    throw JsonTypeException(key, expectedType, val[key].type());
                }
            } else throw out_of_range("key \'" + key + "\' does not exist!");
        }
        return true;
    }

};

#endif //ANTARCLICA_JSONUTILS_HPP
