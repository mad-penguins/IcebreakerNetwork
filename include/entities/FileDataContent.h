#ifndef ANTARCLICA_FILEDATACONTENT_H
#define ANTARCLICA_FILEDATACONTENT_H

#include "APIEntity.hpp"

class FileDataContent : public APIEntity {
public:
    vector<char> bytes{};

    explicit FileDataContent(const json &val) : APIEntity(val) {
        JsonUtils::checkJsonTypes(val, {{"content", json::value_t::string}});
        bytes = move(vector<char>(string(val["content"]).begin(), string(val["content"]).end()));
    }
};

#endif //ANTARCLICA_FILEDATACONTENT_H
