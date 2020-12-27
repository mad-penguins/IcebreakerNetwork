#ifndef ANTARCLICA_UTILS_HPP
#define ANTARCLICA_UTILS_HPP


#include <iostream>
#include <utility>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>

#include "entities/Status.hpp"
#include "utils/ResponseUtils.hpp"

using namespace std;
using json = nlohmann::json;

class Utils {
public:
    enum NoFormResponse {
        GET, DELETE
    };
    enum FormResponse {
        POST, PUT
    };

    static json executeNoFormRequest(NoFormResponse kind, const string &req) {
        json val;

        cpr::Response r;
        switch (kind) {
            case GET:
                r = cpr::Get(cpr::Url{"http://127.0.0.1:8080/api/" + req});
                break;
            case DELETE:
                r = cpr::Delete(cpr::Url{"http://127.0.0.1:8080/api/" + req});
                break;
        }
        val = json::parse(r.text);
        ResponseUtils::checkObject(val);
        return val;
    }

    static json executeFormRequest(FormResponse kind, const string &req, const cpr::Multipart &params) {
        json val;

        cpr::Response r;
        switch (kind) {
            case POST:
                r = cpr::Post(cpr::Url{"http://127.0.0.1:8080/api/" + req}, params);
                break;
            case PUT:
                r = cpr::Put(cpr::Url{"http://127.0.0.1:8080/api/" + req}, params);
                break;
        }
        val = json::parse(r.text);
        ResponseUtils::checkObject(val);
        return val;
    }
};


#endif //ANTARCLICA_UTILS_HPP
