#include "sections/Section.hpp"
#include "utils/MultipartHelpers.hpp"
#include "entities/FileDataContent.h"

template<> string Wrapper::Section<File>::sectionSlug = "file";

template<>
void Wrapper::Section<File>::upload(unsigned machine, const shared_ptr<File> &obj) {
    auto response = Utils::executeFormRequest(
            Utils::FormResponse::POST,
            "/user/" + to_string(user.id) + "/machine/" + to_string(machine) + "/files/" +
            user.accessToken,
            MultipartHelpers::generateFormFile(obj)
    );
    assert(response.is_object());
}

template<>
void Wrapper::Section<File>::update(unsigned int machine, const shared_ptr<File> &obj, bool rewrite) {
    auto response = Utils::executeFormRequest(
            Utils::FormResponse::PUT,
            "/user/" + to_string(user.id) + "/machine/" + to_string(machine) + "/file/" +
            to_string(obj->id) + "/" + (rewrite ? "rew" : "clone") + "/" + user.accessToken,
            MultipartHelpers::generateFormFile(obj)
    );
    assert(response.is_object());
}

vector<char> Wrapper::Files::getContent(unsigned int machine, unsigned int id) {
    auto obj = Utils::executeNoFormRequest(
            Utils::NoFormResponse::GET,
            "/user/" + to_string(user.id) + "/machine/" + to_string(machine) + "/file/" +
            to_string(id) + "/content/" + user.accessToken
    ).at("obj");

    return move(FileDataContent(obj).bytes);
}

template
class Wrapper::Section<File>;
