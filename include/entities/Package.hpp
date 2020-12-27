#ifndef ANTARCLICA_PACKAGE_HPP
#define ANTARCLICA_PACKAGE_HPP


#include "APIEntity.hpp"
#include "Machine.hpp"
#include "Repository.hpp"

class Package : public APIEntity {
public:
    class PackageData : public APIEntity {
    public:
        string name;

        explicit PackageData(const json &val) : APIEntity(val) {
            JsonUtils::checkJsonTypes(val, {{"name", json::value_t::string},});
            name = val["name"];
        }
    };

    shared_ptr<Machine> machine;
    shared_ptr<PackageData> data;
    shared_ptr<Repository> repository;

    explicit Package(const json &val) : APIEntity(val) {
        JsonUtils::checkJsonTypes(val, {
                {"machine",    json::value_t::object},
                {"data",       json::value_t::object},
                {"repository", json::value_t::object}
        });

        machine = make_shared<Machine>(val["machine"]);
        data = make_shared<PackageData>(val["data"]);
        repository = make_shared<Repository>(val["repository"]);
    }

};

#endif //ANTARCLICA_PACKAGE_HPP
