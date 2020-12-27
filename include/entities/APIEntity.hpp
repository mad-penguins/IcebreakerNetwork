#ifndef ANTARCLICA_APIENTITY_HPP
#define ANTARCLICA_APIENTITY_HPP


#include <utility>
#include <nlohmann/json.hpp>
#include "utils/Utils.hpp"

using namespace std;
using json = nlohmann::json;

template<class Type, class EntityBaseClass>
concept IsEntity = std::is_base_of<EntityBaseClass, Type>::value;

class APIEntity {
public:
    unsigned id;

    explicit APIEntity(const json &val) {
        JsonUtils::checkJsonTypes(val, {{"id", json::value_t::number_unsigned}});
        id = val["id"];
    }

    APIEntity() = default;
};

template<class TemplateEntity> requires IsEntity<TemplateEntity, APIEntity>
class EntityList {
public:
    vector<shared_ptr<TemplateEntity>> objs;

    explicit EntityList(const json &val) {
        assert(val.is_array());
        for (const auto &item : val) {
            objs.emplace_back(make_shared<TemplateEntity>(item));
        }
    }

    typename vector<shared_ptr<TemplateEntity>>::iterator begin() {
        return objs.begin();
    }

    typename vector<shared_ptr<TemplateEntity>>::iterator end() {
        return objs.end();
    }
};

#endif //ANTARCLICA_APIENTITY_HPP
