#ifndef ANTARCLICA_REPOSITORY_HPP
#define ANTARCLICA_REPOSITORY_HPP


#include "APIEntity.hpp"
#include "Machine.hpp"

class Repository : public APIEntity {
public:
    class RepositoryData : public APIEntity {
    public:
        string name;
        string URL;
        string manager;

        explicit RepositoryData(const json &val) : APIEntity(val) {
            JsonUtils::checkJsonTypes(val, {
                    {"name",    json::value_t::string},
                    {"url",     json::value_t::string},
                    {"manager", json::value_t::string}
            });

            name = val["name"];
            URL = val["url"];
            manager = val["manager"];
        }
    };

    shared_ptr<Machine> machine;
    shared_ptr<RepositoryData> data;

    explicit Repository(const json &val) : APIEntity(val) {
        JsonUtils::checkJsonTypes(val, {
                {"machine", json::value_t::object},
                {"data",    json::value_t::object},
        });

        machine = make_shared<Machine>(val["machine"]);
        data = make_shared<RepositoryData>(val["data"]);
    }

};

#endif //ANTARCLICA_REPOSITORY_HPP
